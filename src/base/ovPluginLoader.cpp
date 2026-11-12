#include "ovPluginLoader.h"
#include "ovLibrary.h"
#include <unordered_map>
#include <mutex>

class ov::PluginLoaderPrivate
{
    OPENV_DECLARE_PUBLIC(PluginLoader)
public:
    explicit PluginLoaderPrivate(const std::string& name) : library(std::make_unique<Library>()) {}

private:
    std::unique_ptr<Library> library;
};

static std::mutex mutex;
static std::unordered_map<std::string, std::weak_ptr<ov::PluginLoader>> cache;
std::shared_ptr<ov::PluginLoader> ov::PluginLoader::gen(const std::string &name)
{
    if(name.empty()) {
        return {};
    }

    std::lock_guard<std::mutex> locker(mutex);
    if(auto iter = cache.find(name); iter != cache.end()) {
        if(auto loader = iter->second.lock()) {
            return loader;
        }

        cache.erase(iter);
    }

    auto loader = std::shared_ptr<PluginLoader>(new PluginLoader(std::make_unique<PluginLoaderPrivate>(name)));
    if(!loader->load()) {
        return {};
    }

    cache[name] = loader;
    return loader;
}

ov::PluginLoader::~PluginLoader()
{
}

bool ov::PluginLoader::load()
{
    OPENV_D(PluginLoader);
    return d->library->load();
}

bool ov::PluginLoader::unload()
{
    OPENV_D(PluginLoader);
    return d->library->unload();
}

bool ov::PluginLoader::isLoaded() const
{
    OPENV_D(const PluginLoader);
    return d->library->isLoaded();
}

std::shared_ptr<ov::Plugin> ov::PluginLoader::instantiate()
{
    if(!isLoaded()) {
        return {};
    }

    OPENV_D(PluginLoader);

    using plugin_register_t   = Plugin*(*)();
    using plugin_unregister_t = void(*)(Plugin*);

    auto plugin_register   = reinterpret_cast<plugin_register_t>(d->library->resolve("openv_plugin_register"));
    auto plugin_unregister = reinterpret_cast<plugin_unregister_t>(d->library->resolve("openv_plugin_unregister"));
    if(!plugin_register || !plugin_unregister) {
        return {};
    }

    auto plugin = plugin_register();
    if(!plugin) {
        return {};
    }

    auto self = shared_from_this();
    return std::shared_ptr<Plugin>(plugin, [self, plugin_unregister](Plugin* plugin){ plugin_unregister(plugin); });
}

std::string ov::PluginLoader::name() const
{
    OPENV_D(const PluginLoader);
    return d->library->name();
}

std::string ov::PluginLoader::errorString() const
{
    OPENV_D(const PluginLoader);
    return d->library->errorString();
}

ov::PluginLoader::PluginLoader(std::unique_ptr<PluginLoaderPrivate> dd) : dptr(std::move(dd))
{
}