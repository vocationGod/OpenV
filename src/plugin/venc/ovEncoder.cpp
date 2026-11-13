#include "ovEncoder.h"
#include "ovEnvironment.h"
#include "ovPluginLoader.h"
#include "ovFragment.h"
#include "ovImage.h"
#include "ovDir.h"

class ov::EncoderPrivate
{
    OPENV_DECLARE_PUBLIC(Encoder);
public:
    explicit EncoderPrivate(int width, int height, Layout layout, Media media, int capacity)
        : width(width), height(height), layout(layout), media(media), capacity(capacity) {}

private:
    int width;

    int height;

    Media media;

    int capacity;

    Layout layout;
};

std::shared_ptr<ov::Encoder> ov::Encoder::gen(int width, int height, Layout layout, Media media, int capacity, const std::string &dir)
{
    if((capacity < 2) || (width <= 0) || (height <= 0)|| (layout == Layout::NONE) || (media == Media::NONE)) {
        return {};
    }

    return openv_plugin_factory<ov::Encoder>("OPENV_ENCODER_PLUGIN_DIR", OPENV_VENC_MODULE, dir, 
        [&](Encoder* encoder) {                 
            encoder->d_func()->media      =   media;
            encoder->d_func()->width      =   width;
            encoder->d_func()->height     =   height;
            encoder->d_func()->layout     =   layout;
            encoder->d_func()->capacity   =   capacity;
    });
}

ov::Encoder::~Encoder()
{
}

int ov::Encoder::width() const
{
    OPENV_D(const Encoder);
    return d->width;
}

int ov::Encoder::height() const
{
    OPENV_D(const Encoder);
    return d->height;
}

int ov::Encoder::capacity() const
{
    OPENV_D(const Encoder);
    return d->capacity;
}

ov::Media ov::Encoder::media() const
{
    OPENV_D(const Encoder);
    return d->media;
}

ov::Layout ov::Encoder::layout() const
{
    OPENV_D(const Encoder);
    return d->layout;
}

std::optional<int> ov::Encoder::descriptor() const
{
    if(!isRunning()) {
        return {};
    }

    auto fd = notifier();
    if(fd < 0) {
        return {};
    }

    return fd;
}

std::shared_ptr<ov::Fragment> ov::Encoder::acquire(int timeout)
{
    if(!isRunning()) {
        return {};
    }

    auto fragment = receive(timeout);
    if(!fragment || fragment->empty()) {
        return {};
    }

    return fragment;
}

bool ov::Encoder::submit(const std::shared_ptr<ov::Image> &image, int timeout)
{
    if(!isRunning()) {
        return false;
    }

    if(!image || image->empty()) {
        return false;
    }

    return transmit(image, timeout);
}

ov::Encoder::Encoder() : dptr(std::make_unique<EncoderPrivate>(0, 0, Layout::NONE, Media::NONE, 0))
{
}
