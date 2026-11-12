#pragma once
#include "openv/core/ovElement.h"
#include "openv/core/ovLayout.h"
#include "openv/base/ovFlags.h"
#include <optional>
namespace ov {

class Image;
class ProcessorPrivate;
class OPENV_API Processor : public Element
{
    OPENV_DECLARE_PRIVATE(Processor)
    OPENV_DISABLE_COPY(Processor)
public:
    enum Port
    {
        P0 = 1 << 0,
        P1 = 1 << 1,
        P2 = 1 << 2,
        P3 = 1 << 3,
    };
    using Ports = Flags<Port>;

public:
    static std::shared_ptr<ov::Processor> gen(Ports ports, int width, int height, Layout layout, int capacity = 5, const std::string& dir = "./plugins");

public:
    ~Processor();

public:
    int width() const;

    int height() const;
    
    int capacity() const;
    
    ov::Layout layout() const;

    ov::Processor::Ports ports() const;

    std::optional<int> descriptor(Port port) const;

    std::shared_ptr<ov::Image> acquire(Port port, int timeout = -1);

    bool submit(const std::shared_ptr<ov::Image>& image, int timeout = 0);

protected:
    virtual int notifier(Port port) const = 0;

    virtual std::shared_ptr<ov::Image> receive(Port port, int timeout) = 0;

    virtual bool transmit(const std::shared_ptr<ov::Image>& image, int timeout) = 0;

protected:
    explicit Processor();

};

OPENV_FLAGS_ENABLE_OPERATORS(ov::Processor::Port)
OPENV_DECLARE_INTERFACE(Processor, "ov.iid.processor")
}