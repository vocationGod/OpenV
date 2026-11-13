#include "ovCamera.h"
#include "ovEnvironment.h"
#include "ovPluginLoader.h"
#include "ovImage.h"
#include "ovDir.h"

class ov::CameraPrivate
{
    OPENV_DECLARE_PUBLIC(Camera)
public:
    explicit CameraPrivate(const std::string& name, int width, int height, Layout layout, int capacity)
        : name(name), width(width), height(height), layout(layout), capacity(capacity) {}

private:
    int width;

    int height;
    
    int capacity;

    Layout layout;

    std::string name;
};

std::shared_ptr<ov::Camera> ov::Camera::gen(const std::string &name, int width, int height, Layout layout, int capacity, const std::string &dir)
{
    if(name.empty() || (capacity < 2) || (width <= 0) || (height <= 0)|| (layout == Layout::NONE)) {
        return {};
    }

    return openv_plugin_factory<ov::Camera>("OPENV_CAMERA_PLUGIN_DIR", OPENV_VCAM_MODULE, dir, 
        [&](Camera* camera) {                 
            camera->d_func()->name      =   name;
            camera->d_func()->width     =   width;
            camera->d_func()->height    =   height;
            camera->d_func()->layout    =   layout;
            camera->d_func()->capacity  =   capacity;
    });
}

ov::Camera::~Camera()
{
}

int ov::Camera::width() const
{
    OPENV_D(const Camera);
    return d->width;
}

int ov::Camera::height() const
{
    OPENV_D(const Camera);
    return d->height;
}

int ov::Camera::capacity() const
{
    OPENV_D(const Camera);
    return d->capacity;
}

ov::Layout ov::Camera::layout() const
{
    OPENV_D(const Camera);
    return d->layout;
}

const std::string& ov::Camera::name() const
{
    OPENV_D(const Camera);
    return d->name;
}

std::optional<int> ov::Camera::descriptor() const
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

std::shared_ptr<ov::Image> ov::Camera::acquire(int timeout)
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

ov::Camera::Camera() : dptr(std::make_unique<CameraPrivate>("", 0, 0, Layout::NONE, 0))
{
}
