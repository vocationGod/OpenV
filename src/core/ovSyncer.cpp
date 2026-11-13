#include "ovSyncer.h"
#include "ovImage.h"

#ifndef _WIN32
    #include <linux/dma-buf.h>
    #include <sys/ioctl.h>
#endif

class ov::SyncerPrivate
{
    OPENV_DECLARE_PUBLIC(Syncer)
public:
    explicit SyncerPrivate(const std::shared_ptr<Image> &image) : image(image) {}

private:
    std::shared_ptr<Image> image;
};

ov::Syncer::Syncer(const std::shared_ptr<Image> &image): dptr(std::make_unique<SyncerPrivate>(image))
{
    OPENV_D(const Syncer);
#ifndef _WIN32
    if(!d->image || d->image->empty() || !d->image->handle()) {
        return;
    }

    struct dma_buf_sync sync = {0};
    auto fd = d->image->handle().value();

    sync.flags = DMA_BUF_SYNC_START | DMA_BUF_SYNC_WRITE;
    ioctl(fd, DMA_BUF_IOCTL_SYNC, &sync);
#endif
}

ov::Syncer::~Syncer()
{
    OPENV_D(const Syncer);
#ifndef _WIN32
    if(!d->image || d->image->empty() || !d->image->handle()) {
        return;
    }

    struct dma_buf_sync sync = {0};
    auto fd = d->image->handle().value();

    sync.flags = DMA_BUF_SYNC_END | DMA_BUF_SYNC_WRITE;
    ioctl(fd, DMA_BUF_IOCTL_SYNC, &sync);
#endif
}