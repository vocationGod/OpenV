#include "ovProcessor.h"
#include "ovEnvironment.h"
#include "ovPluginLoader.h"
#include "ovImage.h"
#include "ovDir.h"

class ov::ProcessorPrivate
{
    OPENV_DECLARE_PUBLIC(Processor)
public:
    explicit ProcessorPrivate(ov::Processor::Ports ports, int width, int height, Layout layout, int capacity)
        : ports(ports), width(width), height(height), layout(layout), capacity(capacity) {}

private:
    int width;

    int height;
    
    int capacity;

    Layout layout;

    ov::Processor::Ports ports;
};

std::shared_ptr<ov::Processor> ov::Processor::gen(Ports ports, int width, int height, Layout layout, int capacity, const std::string &dir)
{
    if((ports.empty()) || (capacity < 2) || (width <= 0) || (height <= 0)|| (layout == Layout::NONE)) {
        return {};
    }

    std::string directory = Environment::value("OPENV_PROCESSOR_PLUGIN_DIR");
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

        if(!ins->query<Processor>()) {
            continue;
        }

        auto processor = std::static_pointer_cast<Processor>(ins);

        processor->d_func()->ports     =   ports;
        processor->d_func()->width     =   width;
        processor->d_func()->height    =   height;
        processor->d_func()->layout    =   layout;
        processor->d_func()->capacity  =   capacity;

        return processor;
    }

    return {};
}

ov::Processor::~Processor()
{
}

int ov::Processor::width() const
{
    OPENV_D(const Processor);
    return d->width;
}

int ov::Processor::height() const
{
    OPENV_D(const Processor);
    return d->height;
}

int ov::Processor::capacity() const
{
    OPENV_D(const Processor);
    return d->capacity;
}

ov::Layout ov::Processor::layout() const
{
    OPENV_D(const Processor);
    return d->layout;
}

ov::Processor::Ports ov::Processor::ports() const
{
    OPENV_D(const Processor);
    return d->ports;
}

std::optional<int> ov::Processor::descriptor(Port port) const
{
    if(!isRunning()) {
        return {};
    }

    auto fd = notifier(port);
    if(fd < 0) {
        return {};
    }

    return fd;
}

std::shared_ptr<ov::Image> ov::Processor::acquire(Port port, int timeout)
{
    if(!isRunning()) {
        return {};
    }

    auto image = receive(port, timeout);
    if(!image || image->empty()) {
        return {};
    }

    return image;
}

bool ov::Processor::submit(const std::shared_ptr<ov::Image> &image, int timeout)
{
    if(!isRunning()) {
        return false;
    }

    if(!image || image->empty()) {
        return false;
    }

    return transmit(image, timeout);
}

ov::Processor::Processor() : dptr(std::make_unique<ProcessorPrivate>(Ports(), 0, 0, Layout::NONE, 0))
{
}
