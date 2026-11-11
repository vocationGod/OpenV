#pragma once
#include "openv/openv.h"
#include <atomic>
namespace ov {

class ElementPrivate
{
    OPENV_DECLARE_PUBLIC(Element)
public:
    enum State { CLOSED, OPENED, RUNNING };

public:
    explicit ElementPrivate() : state(CLOSED) {}
    virtual ~ElementPrivate() = default;

private:
    std::atomic<State> state;
};
}