#pragma once
#include "openv/openv.h"
#include <type_traits>
#include <cstring>
namespace ov {

class OPENV_API Plugin 
{
public:
    virtual ~Plugin() = default;

public:
    virtual void* metacast(const char*) { return nullptr; }

public:
    template <typename T> T* query();
    template <typename T> const T* query() const;
};

template <typename T> 
constexpr const char* plugin_interface_iid() = delete;

template <typename T> 
inline T* plugin_iid_cast(Plugin* plugin, const char* iid = plugin_interface_iid<std::remove_cv_t<T>*>())
{
    return reinterpret_cast<T*>(plugin ? plugin->metacast(iid) : nullptr);
}

template <typename T> 
inline std::enable_if_t<std::is_const<T>::value, T*> plugin_iid_cast(const Plugin *plugin)
{
    return plugin_iid_cast<T>(const_cast<Plugin*>(plugin));
}

template <typename... Ts>
void* plugin_metacast(Plugin* plugin, const char* iid)
{
    static_assert(sizeof...(Ts) > 0, "#error plugin_metacast<>");
    const char* iids[] = { plugin_interface_iid<Ts*>()... };
    void* const ptrs[] = { static_cast<void*>(static_cast<Ts*>(plugin))... };
    for(std::size_t i=0; i<sizeof...(Ts); ++i) {
        if(iid && iids[i] && (iid==iids[i] || std::strcmp(iid, iids[i])==0)) {
            return ptrs[i];
        }
    }

    return nullptr;
}

template <typename... Ts>
void* plugin_metacast(const Plugin* plugin, const char* iid)
{
    return plugin_metacast<Ts...>(const_cast<Plugin*>(plugin), iid);
}

template <typename T> inline T* Plugin::query() { return plugin_iid_cast<T>(this); }
template <typename T> inline const T* Plugin::query() const { return plugin_iid_cast<const T>(this); }

#define OPENV_INTERFACES(...) void* metacast(const char* iid) override { return plugin_metacast<__VA_ARGS__>(this, iid); }
#define OPENV_DECLARE_INTERFACE(IFace, IId) template <> constexpr const char* plugin_interface_iid<IFace*>() { return IId; }

#define OPENV_REGISTER_PLUGIN(A, Name) \
extern "C" OPENV_API ov::Plugin* openv_plugin_register() { try { return new A(); } catch(...) { return nullptr; } } \
extern "C" OPENV_API void openv_plugin_unregister(ov::Plugin* plugin) { delete plugin; } \
extern "C" OPENV_API const char* openv_plugin_module() { return Name; }

#define OPENV_VCAM_MODULE "vcam"
#define OPENV_REGISTER_VCAM_PLUGIN(A) OPENV_REGISTER_PLUGIN(A, OPENV_VCAM_MODULE)

#define OPENV_VENC_MODULE "venc"
#define OPENV_REGISTER_VENC_PLUGIN(A) OPENV_REGISTER_PLUGIN(A, OPENV_VENC_MODULE)

#define OPENV_VDEC_MODULE "vdec"
#define OPENV_REGISTER_VDEC_PLUGIN(A) OPENV_REGISTER_PLUGIN(A, OPENV_VDEC_MODULE)

#define OPENV_VGFX_MODULE "vgfx"
#define OPENV_REGISTER_VGFX_PLUGIN(A) OPENV_REGISTER_PLUGIN(A, OPENV_VGFX_MODULE)

#define OPENV_VMUX_MODULE "vmux"
#define OPENV_REGISTER_VMUX_PLUGIN(A) OPENV_REGISTER_PLUGIN(A, OPENV_VMUX_MODULE)

#define OPENV_VPSS_MODULE "vpss"
#define OPENV_REGISTER_VPSS_PLUGIN(A) OPENV_REGISTER_PLUGIN(A, OPENV_VPSS_MODULE)

#define OPENV_VWIN_MODULE "vwin"
#define OPENV_REGISTER_VWIN_PLUGIN(A) OPENV_REGISTER_PLUGIN(A, OPENV_VWIN_MODULE)
}