#pragma once
#include "openv/core/ovElement.h"
#include "openv/core/ovMedia.h"
#include <memory>
#include <vector>
#include <string>
namespace ov {

class Fragment;
class RTSPServerPrivate;
class OPENV_API RTSPServer : public Element
{
    OPENV_DECLARE_PRIVATE(RTSPServer)
    OPENV_DISABLE_COPY(RTSPServer)
public:
    struct Session{ std::string live; ov::Media media; };

public:
    static std::shared_ptr<ov::RTSPServer> gen(const std::vector<Session>& sessions, int port, int capacity = 60, const std::string& dir = "./plugins");

public:
    ~RTSPServer();

public:
    int port() const;

    int capacity() const;

    const std::vector<ov::RTSPServer::Session>& sessions() const;

    bool submit(const Session& session, const std::shared_ptr<ov::Fragment>& fragment, int timeout = 0);

protected:
    virtual bool transmit(const Session& session, const std::shared_ptr<ov::Fragment>& fragment, int timeout) = 0;

protected:
    explicit RTSPServer();

private:
    std::unique_ptr<RTSPServerPrivate> dptr;
};

OPENV_DECLARE_INTERFACE(RTSPServer, "ov.iid.rtspserver")
}