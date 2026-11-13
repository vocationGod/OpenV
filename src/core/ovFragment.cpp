#include "ovFragment.h"

class ov::FragmentPrivate
{
    OPENV_DECLARE_PUBLIC(Fragment)
public:
    explicit FragmentPrivate(std::byte *bits, size_t sizeInBytes, Media media, Fragment::Type type, int64_t timestamp, std::function<void(void *)> cleaner, void *opaque)
        : bits(bits), sizeInBytes(sizeInBytes), media(media), type(type), timestamp(timestamp), cleaner(cleaner), opaque(opaque) {}

private:
    Media media;

    int64_t timestamp;

    size_t sizeInBytes;

    std::byte* bits;

    Fragment::Type type;

    void* opaque;

    std::function<void(void*)> cleaner;
};

std::shared_ptr<ov::Fragment> ov::Fragment::gen(size_t sizeInBytes, Media media, Type type, int64_t timestamp, std::function<void(void *)> cleaner, void *opaque)
{
    return std::shared_ptr<ov::Fragment>(new Fragment(nullptr, sizeInBytes, media, type, timestamp, cleaner, opaque));
}

std::shared_ptr<ov::Fragment> ov::Fragment::gen(std::byte *bits, size_t sizeInBytes, Media media, Type type, int64_t timestamp, std::function<void(void *)> cleaner, void *opaque)
{
    return std::shared_ptr<ov::Fragment>(new Fragment(bits, sizeInBytes, media, type, timestamp, cleaner, opaque));
}

ov::Fragment::~Fragment()
{
    OPENV_D(Fragment);
    if(d->cleaner) {
        d->cleaner(d->opaque);
    }
}

ov::Fragment::Type ov::Fragment::type() const
{
    OPENV_D(const Fragment);
    return d->type;
}

std::byte *ov::Fragment::bits()
{
    OPENV_D(Fragment);
    return d->bits;
}

const std::byte *ov::Fragment::bits() const
{
    OPENV_D(const Fragment);
    return d->bits;
}

ov::Media ov::Fragment::media() const
{
    OPENV_D(const Fragment);
    return d->media;
}

bool ov::Fragment::empty() const
{
    OPENV_D(const Fragment);
    return (d->bits == nullptr) || (d->sizeInBytes <= 0);
}

int64_t ov::Fragment::timestamp() const
{
    OPENV_D(const Fragment);
    return d->timestamp;
}

size_t ov::Fragment::sizeInBytes() const
{
    OPENV_D(const Fragment);
    return d->sizeInBytes;
}

ov::Fragment::Fragment(std::byte *bits, size_t sizeInBytes, Media media, Type type, int64_t timestamp, std::function<void(void *)> cleaner, void *opaque)
    : dptr(std::make_unique<FragmentPrivate>(bits, sizeInBytes, media, type, timestamp, cleaner, opaque))
{    
    OPENV_D(Fragment);
    if((d->bits == nullptr) && (d->sizeInBytes > 0)) {
        try {
            d->bits     = new std::byte[d->sizeInBytes];
            d->cleaner  = [this](void*) { delete [] d_func()->bits; };
        } catch(...) {
            d->bits         = nullptr;
            d->cleaner      = {};
            d->sizeInBytes = 0;
        }  
    }
}