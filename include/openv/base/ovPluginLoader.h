#pragma once
#include "openv/openv.h"
#include <string_view>
#include <string>
#include <memory>
namespace ov {

class Plugin;
class PluginLoaderPrivate;
class OPENV_API PluginLoader final : public std::enable_shared_from_this<PluginLoader>
{
    OPENV_DECLARE_PRIVATE(PluginLoader)
    OPENV_DISABLE_COPY(PluginLoader)
public:
    static std::shared_ptr<ov::PluginLoader> gen(const std::string& name);

public:
    ~PluginLoader();

public:
    bool load();

    bool unload();

    bool isLoaded() const;

    std::string_view name() const;
    
    std::string_view errorString() const;

    std::shared_ptr<ov::Plugin> instantiate();

protected:
    explicit PluginLoader(std::unique_ptr<PluginLoaderPrivate> dd);

private:
    std::unique_ptr<PluginLoaderPrivate> dptr;
};
}