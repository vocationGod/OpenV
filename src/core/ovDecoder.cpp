#include "ovDecoder.h"
#include "ovElement_p.h"
#include "ovEnvironment.h"
#include "ovPluginLoader.h"
#include "ovFragment.h"
#include "ovImage.h"
#include "ovDir.h"

class ov::DecoderPrivate : public ElementPrivate
{
    OPENV_DECLARE_PUBLIC(Decoder)
public:
    explicit DecoderPrivate(int width, int height, Media media, int capacity)
        : width(width), height(height), media(media), capacity(capacity) {}

public:
    int width;

    int height;
    
    Media media;

    int capacity;
};

std::shared_ptr<ov::Decoder> ov::Decoder::gen(int width, int height, Media media, int capacity, const std::string &dir)
{
    if((capacity < 2) || (width <= 0) || (height <= 0)|| (media == Media::NONE)) {
        return {};
    }

    std::string directory = Environment::value("OPENV_DECODER_PLUGIN_DIR");
    if(directory.empty()) {
        directory = Environment::value("OPENV_PLUGIN_DIR");
    }

    if(directory.empty()) {
        directory = dir;
    }

    if(directory.empty()) {
        return {};
    }

    auto pathList = Dir::scan(directory, {".so", ".dll"});
    if(pathList.empty()) {
        return {};
    }

    for(const auto& path : pathList) {
        auto loader = PluginLoader::gen(path);
        if(!loader || (!loader->isLoaded() && !loader->load())) {
            continue;
        }

        auto ins = loader->instantiate();
        if(!ins) {
            continue;
        }

        if(!ins->query<Decoder>()) {
            continue;
        }

        auto decoder = std::static_pointer_cast<Decoder>(ins);

        decoder->d_func()->media     =   media;
        decoder->d_func()->width     =   width;
        decoder->d_func()->height    =   height;
        decoder->d_func()->capacity  =   capacity;

        return decoder;
    }

    return {};
}

ov::Decoder::~Decoder()
{
}

int ov::Decoder::width() const
{
    OPENV_D(const Decoder);
    return d->width;
}

int ov::Decoder::height() const
{
    OPENV_D(const Decoder);
    return d->height;
}

int ov::Decoder::capacity() const
{
    OPENV_D(const Decoder);
    return d->capacity;
}

ov::Media ov::Decoder::media() const
{
    OPENV_D(const Decoder);
    return d->media;
}

std::optional<int> ov::Decoder::descriptor() const
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

std::shared_ptr<ov::Image> ov::Decoder::acquire(int timeout)
{
    if(!isRunning()) {
        return {};
    }

    auto image = receive(timeout);
    if(!image || image->empty()) {
        return {};
    }

    return image;
}

bool ov::Decoder::submit(const std::shared_ptr<ov::Fragment> &fragment, int timeout)
{
    if(!isRunning()) {
        return false;
    }

    if(!fragment || fragment->empty()) {
        return false;
    }

    return transmit(fragment, timeout);
}

ov::Decoder::Decoder() : Element(std::make_unique<DecoderPrivate>(0, 0, Media::NONE, 0))
{
}
