#pragma once
#include "openv/core/ovElement.h"
#include "openv/core/ovLayout.h"
#include <string_view>
#include <optional>
#include <string>
namespace ov {

class Image;
class CameraPrivate;
class OPENV_API Camera : public Element
{
    OPENV_DECLARE_PRIVATE(Camera)
    OPENV_DISABLE_COPY(Camera)
public:
    static std::shared_ptr<ov::Camera> gen(const std::string& name, int width, int height, Layout layout, int capacity = 5, const std::string& dir = "./plugins");

public:
    ~Camera();

public:
    int width() const;

    int height() const;
    
    int capacity() const;
    
    ov::Layout layout() const;
    
    std::string_view name() const;

    std::optional<int> descriptor() const;
    
    std::shared_ptr<ov::Image> acquire(int timeout = -1);

protected:
    virtual int notifier() const = 0;

    virtual std::shared_ptr<ov::Image> receive(int timeout) = 0;

protected:
    explicit Camera();
};

OPENV_DECLARE_INTERFACE(Camera, "ov.iid.camera")
}