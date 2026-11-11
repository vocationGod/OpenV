#include "ovWindow.h"
#include "ovElement_p.h"
#include "ovEnvironment.h"
#include "ovPluginLoader.h"
#include "ovImage.h"
#include "ovDir.h"

class ov::WindowPrivate : public ElementPrivate
{
    OPENV_DECLARE_PUBLIC(Window)
public:
    explicit WindowPrivate(Window::Connector connector, Window::Geometry geometry, int width, int height, Layout layout, int capacity)
        : connector(connector), geometry(geometry), width(width), height(height), layout(layout), capacity(capacity) {}

private:
    int width;

    int height;

    int capacity;

    Layout layout;

    Window::Geometry geometry;

    Window::Connector connector;
};

std::shared_ptr<ov::Window> ov::Window::gen(Connector connector, int width, int height, Layout layout, int capacity, const std::string &dir)
{
    return gen(connector, Geometry{0, 0, width, height}, width, height, layout, capacity, dir);
}

std::shared_ptr<ov::Window> ov::Window::gen(Connector connector, Geometry geometry, int width, int height, Layout layout, int capacity, const std::string &dir)
{
    if((capacity < 2) || (width <= 0) || (height <= 0)|| (connector == Connector::NONE) || (layout == Layout::NONE)) {
        return {};
    }

    if((geometry.w <= 0) || (geometry.h <= 0) || (geometry.x + geometry.w <= 0) || (geometry.y + geometry.h <= 0) || (geometry.x + geometry.w > width) || (geometry.y + geometry.h > height)) {
        return {};
    }

    std::string directory = Environment::value("OPENV_WINDOW_PLUGIN_DIR");
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

        if(!ins->query<Window>()) {
            continue;
        }

        auto window = std::static_pointer_cast<Window>(ins);

        window->d_func()->width      =   width;
        window->d_func()->height     =   height;
        window->d_func()->layout     =   layout;
        window->d_func()->capacity   =   capacity;
        window->d_func()->geometry   =   geometry;
        window->d_func()->connector  =   connector;

        return window;
    }

    return {};
}

ov::Window::~Window()
{
}

int ov::Window::width() const
{
    OPENV_D(const Window);
    return d->width;
}

int ov::Window::height() const
{
    OPENV_D(const Window);
    return d->height;
}

int ov::Window::capacity() const
{
    OPENV_D(const Window);
    return d->capacity;
}

ov::Layout ov::Window::layout() const
{
    OPENV_D(const Window);
    return d->layout;
}

ov::Window::Geometry ov::Window::geometry() const
{
    OPENV_D(const Window);
    return d->geometry;
}

ov::Window::Connector ov::Window::connector() const
{
    OPENV_D(const Window);
    return d->connector;
}

bool ov::Window::submit(const std::shared_ptr<ov::Image> &image, int timeout)
{
    if(!isRunning()) {
        return false;
    }

    if(!image || image->empty()) {
        return false;
    }

    return transmit(image, timeout);
}

ov::Window::Window() : Element(std::make_unique<WindowPrivate>(Connector::NONE, Geometry{0,0,0,0}, 0, 0, Layout::NONE, 0))
{
}
