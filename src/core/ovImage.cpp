#include "ovImage.h"

#ifndef _WIN32
    #include <linux/dma-heap.h>
    #include <sys/ioctl.h>
    #include <sys/mman.h>
    #include <filesystem>
    #include <unistd.h>
    #include <fcntl.h>
#endif

class ov::ImagePrivate
{
    OPENV_DECLARE_PUBLIC(Image)
public:
    explicit ImagePrivate(std::byte *bits, int handle, int width, int height, Layout layout, int bytesPerLine, int sizeInBytes, long timestamp, std::function<void(void *)> cleaner, void *opaque)
        : bits(bits), handle(handle), width(width), height(height), layout(layout), bytesPerLine(bytesPerLine), sizeInBytes(sizeInBytes), timestamp(timestamp), cleaner(cleaner), opaque(opaque) {}

private:
    int width;

    int height;

    int handle;

    Layout layout;

    int64_t timestamp;

    size_t sizeInBytes;

    std::byte* bits;

    int bytesPerLine;

    void* opaque;

    std::function<void(void*)> cleaner;
};

std::shared_ptr<ov::Image> ov::Image::gen(int width, int height, Layout layout, int64_t timestamp, std::function<void(void *)> cleaner, void *opaque)
{
    return std::shared_ptr<Image>(new Image(nullptr, 0, width, height, layout, 0, 0, timestamp, cleaner, opaque));
}

std::shared_ptr<ov::Image> ov::Image::gen(std::byte *bits, int width, int height, Layout layout, int bytesPerLine, size_t sizeInBytes, int64_t timestamp, std::function<void(void *)> cleaner, void *opaque)
{
    return std::shared_ptr<Image>(new Image(bits, 0, width, height, layout, bytesPerLine, sizeInBytes, timestamp, cleaner, opaque));
}

std::shared_ptr<ov::Image> ov::Image::gen(std::byte *bits, int handle, int width, int height, Layout layout, int bytesPerLine, size_t sizeInBytes, int64_t timestamp, std::function<void(void *)> cleaner, void *opaque)
{
    return std::shared_ptr<Image>(new Image(bits, handle, width, height, layout, bytesPerLine, sizeInBytes, timestamp, cleaner, opaque));
}

ov::Image::~Image()
{
    OPENV_D(Image);
    if(d->cleaner) { 
        d->cleaner(d->opaque);
    }
}

std::optional<int> ov::Image::handle() const
{
    OPENV_D(const Image);
    if(d->handle <= 0) {
        return {};
    }

    return d->handle;
}

std::byte *ov::Image::bits()
{
    OPENV_D(Image);
    return d->bits;
}

const std::byte *ov::Image::bits() const
{
    OPENV_D(const Image);
    return d->bits;
}

ov::Layout ov::Image::layout() const
{
    OPENV_D(const Image);
    return d->layout;
}

int ov::Image::width() const
{
    OPENV_D(const Image);
    return d->width;
}

int ov::Image::height() const
{
    OPENV_D(const Image);
    return d->height;
}

bool ov::Image::empty() const
{
    OPENV_D(const Image);
    return (d->bits == nullptr) || (d->width <= 0) || (d->height <= 0) || (d->bytesPerLine <= 0) || (d->sizeInBytes <= 0) || (d->layout == Layout::NONE);
}

int64_t ov::Image::timestamp() const
{
    OPENV_D(const Image);
    return d->timestamp;
}

size_t ov::Image::sizeInBytes() const
{
    OPENV_D(const Image);
    return d->sizeInBytes;
}

int ov::Image::bytesPerLine() const
{
    OPENV_D(const Image);
    return d->bytesPerLine;
}

ov::Image::Image(std::byte *bits, int handle, int width, int height, Layout layout, int bytesPerLine, size_t sizeInBytes, int64_t timestamp, std::function<void(void *)> cleaner, void *opaque)
    : dptr(std::make_unique<ImagePrivate>(bits, handle, width, height, layout, bytesPerLine, sizeInBytes, timestamp, cleaner, opaque))
{
    OPENV_D(Image);
    if((d->bits == nullptr) && (d->handle <= 0) && (d->width > 0) && (d->height > 0) && (d->layout != Layout::NONE)) {
        int count = 0;
        int depth = 0;

        switch(d->layout) {
        #define CREATE_ENUM(a, b, c)    case ov::Layout::a : count = c; break;
            OPENV_DECLARE_LAYOUT_TOKENS(CREATE_ENUM)
        #undef  CREATE_ENUM
        }

        switch(d->layout) {
        #define CREATE_ENUM(a, b, c)    case ov::Layout::a : depth = b; break;
            OPENV_DECLARE_LAYOUT_TOKENS(CREATE_ENUM)
        #undef  CREATE_ENUM
        }

        int stride  = depth * OPENV_ALIGN(width, 64) / 8;
        int length  = count * OPENV_ALIGN(width, 64) * OPENV_ALIGN(height, 64) / 8;
        if(stride <= 0 || length <= 0) {
            return;
        }
        
#ifndef _WIN32
        int fd = -1;
        do {
            std::error_code error = {};
            auto path = "/dev/dma_heap/system-uncached-dma32";
            if(!std::filesystem::exists(path, error)) {
                path = "/dev/dma_heap/system-uncached";
            }

            if(!std::filesystem::exists(path, error)) {
                path = "/dev/dma_heap/system";
            }

            if(!std::filesystem::exists(path, error)) {
                break;
            }

            fd = open(path, O_RDWR | O_CLOEXEC);
            if(fd < 0) {
                break;
            }

            dma_heap_allocation_data allocation = {};

            allocation.len      = length;
            allocation.fd_flags = O_RDWR | O_CLOEXEC;
            if(ioctl(fd, DMA_HEAP_IOCTL_ALLOC, &allocation) < 0) {
                break;
            }

            void* va = mmap(nullptr, allocation.len, PROT_READ | PROT_WRITE, MAP_SHARED, allocation.fd, 0);
            if(va == MAP_FAILED) {
                close(allocation.fd);
                break;
            }
             
            d->sizeInBytes  = length;
            d->bytesPerLine = stride;

            d->bits    = static_cast<std::byte*>(va);
            d->handle  = allocation.fd;
            d->cleaner = [this](void*) { munmap(d_func()->bits, d_func()->sizeInBytes); close(d_func()->handle); };

            close(fd);
            return;
        } while(0);

        if(fd >= 0) {
            close(fd);
        }
#endif
        try {
            d->bits    = new std::byte[length];
            d->cleaner = [this](void*) { delete [] d_func()->bits; };

            d->sizeInBytes  = length;
            d->bytesPerLine = stride;
        } catch(...) {
            d->bits         = nullptr;
            d->cleaner      = {};

            d->sizeInBytes  = 0;
            d->bytesPerLine = 0;
        }
    }
}