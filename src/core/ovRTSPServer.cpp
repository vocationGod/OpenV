#include "ovRTSPServer.h"
#include "ovElement_p.h"
#include "ovEnvironment.h"
#include "ovPluginLoader.h"
#include "ovFragment.h"
#include "ovDir.h"

class ov::RTSPServerPrivate : public ElementPrivate
{
    OPENV_DECLARE_PUBLIC(RTSPServer)
public:
    explicit RTSPServerPrivate(const std::vector<ov::RTSPServer::Session> &sessions, int port, int capacity)
        : sessions(sessions), port(port), capacity(capacity) {}

private:
    int port;

    int capacity;

    std::vector<ov::RTSPServer::Session> sessions;
};

std::shared_ptr<ov::RTSPServer> ov::RTSPServer::gen(const std::vector<Session> &sessions, int port, int capacity, const std::string &dir)
{
    if((capacity < 2) || (port <= 0)) {
        return {};
    }

    std::vector<Session> lives;
    for(const auto& session : sessions) {
        if(!session.live.empty() && session.media != Media::NONE) {
            lives.push_back(session);
        }
    }

    if(lives.empty()) {
        return {};
    }

    std::string directory = Environment::value("OPENV_RTSPSERVER_PLUGIN_DIR");
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

        if(!ins->query<RTSPServer>()) {
            continue;
        }

        auto server = std::static_pointer_cast<RTSPServer>(ins);

        server->d_func()->port       =   port;
        server->d_func()->sessions   =   lives;
        server->d_func()->capacity   =   capacity;

        return server;
    }

    return {};
}

ov::RTSPServer::~RTSPServer()
{
}

int ov::RTSPServer::port() const
{
    OPENV_D(const RTSPServer);
    return d->port;
}

int ov::RTSPServer::capacity() const
{
    OPENV_D(const RTSPServer);
    return d->capacity;
}

std::vector<ov::RTSPServer::Session> ov::RTSPServer::sessions() const
{
    OPENV_D(const RTSPServer);
    return d->sessions;
}

bool ov::RTSPServer::submit(const Session &session, const std::shared_ptr<ov::Fragment> &fragment, int timeout)
{
    if(!isRunning()) {
        return false;
    }

    if(!fragment || fragment->empty() || session.live.empty() || session.media == Media::NONE) {
        return false;
    }

    return transmit(session, fragment, timeout);
}

ov::RTSPServer::RTSPServer() : Element(std::make_unique<RTSPServerPrivate>(std::vector<Session>{}, 0, 0))
{
}
