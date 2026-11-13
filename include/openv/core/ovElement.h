#pragma once
#include "openv/base/ovPlugin.h"
#include <atomic>
namespace ov {

class OPENV_API Element : public Plugin
{
    OPENV_DISABLE_COPY(Element)
public:
    ~Element();

public:
    bool open();

    bool start();

    void stop();

    void close();

    bool isOpen() const;

    bool isRunning() const;

protected:
    virtual bool startup()  = 0;

    virtual bool resume()   = 0;

    virtual void pause()    = 0;

    virtual void shutdown() = 0;

protected:
    explicit Element();

private:
    enum State { CLOSED, OPENED, RUNNING };
    std::atomic<State> state;
};
}