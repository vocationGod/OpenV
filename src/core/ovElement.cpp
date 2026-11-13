#include "ovElement.h"

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

    state = OPENED;
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

    state = RUNNING;
    return true;
}

void ov::Element::stop()
{
    if(!isRunning()) {
        return;
    }

    pause();
    state = OPENED;
}

void ov::Element::close()
{
    if(isRunning()) {
        stop();
    }

    if(isOpen()) {
        shutdown();
    }

    state = CLOSED;
}

bool ov::Element::isOpen() const
{
    return (state != CLOSED);
}

bool ov::Element::isRunning() const
{
    return (state == RUNNING);
}

ov::Element::Element() : state(CLOSED)
{
}
