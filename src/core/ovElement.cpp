#include "ovElement.h"
#include "ovElement_p.h"

ov::Element::~Element()
{
}

bool ov::Element::open()
{
    if(isOpen()) {
        return true;
    }

    if(!startup()) {
        return false;
    }

    OPENV_D(Element);
    d->state = ElementPrivate::OPENED;
    return true;
}

bool ov::Element::start()
{
    if(!isOpen()) {
        return false;
    }

    if(isRunning()) {
        return true;
    }

    if(!resume()) {
        return false;
    }

    OPENV_D(Element);
    d->state = ElementPrivate::RUNNING;
    return true;
}

void ov::Element::stop()
{
    if(!isRunning()) {
        return;
    }

    pause();

    OPENV_D(Element);
    d->state = ElementPrivate::OPENED;
}

void ov::Element::close()
{
    if(isRunning()) {
        stop();
    }

    if(isOpen()) {
        shutdown();
    }

    OPENV_D(Element);
    d->state = ElementPrivate::CLOSED;
}

bool ov::Element::isOpen() const
{
    OPENV_D(const Element);
    return (d->state != ElementPrivate::CLOSED);
}

bool ov::Element::isRunning() const
{
    OPENV_D(const Element);
    return (d->state == ElementPrivate::RUNNING);
}

ov::Element::Element(std::unique_ptr<ElementPrivate> dd) : dptr(std::move(dd))
{
}
