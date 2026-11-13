#include "ovLibrary.h"
#include <cstdio>
#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #define openv_module_t                          HMODULE
#else
    #include <dlfcn.h>
    #define openv_module_t                          void*
#endif

static openv_module_t openv_module_load(const char* name)
{
#ifdef _WIN32
    ::SetLastError(0); 
    return ::LoadLibraryA(name);
#else
    return ::dlopen(name, RTLD_NOW | RTLD_LOCAL);
#endif    
}

static bool openv_module_unload(openv_module_t module)
{
#ifdef _WIN32
    ::SetLastError(0); 
    return ::FreeLibrary(module) != FALSE;
#else
    return ::dlclose(module) == 0;
#endif     
}

static ov::FunctionPointer openv_module_symbol(openv_module_t module, const char* symbol)
{
#ifdef _WIN32
    ::SetLastError(0); 
    return reinterpret_cast<void*>(::GetProcAddress(module, symbol));
#else
    ::dlerror();
    return ::dlsym(module, symbol);
#endif      
}

static const char* openv_module_errstr()
{
    static thread_local char errstr[256] = {};
#ifdef _WIN32
    auto err = ::GetLastError();
    if(!err) {
        return {};
    }    

    auto size = ::FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, err, 0, errstr, sizeof(errstr), nullptr);
    if(!size) {
        snprintf(errstr, sizeof(errstr), "load library error : 0x%X", (uint32_t)err);
        return errstr;
    }

    while(size > 0 && (errstr[size - 1] == '\r' || errstr[size - 1] == '\n')) {
        errstr[--size] = '\0';
    }

    return errstr;
#else 
    auto err = ::dlerror();
    if(!err) {
        return {};
    }

    snprintf(errstr, sizeof(errstr), "%s", err);
    return errstr;
#endif
}

class ov::LibraryPrivate
{
    OPENV_DECLARE_PUBLIC(Library)
public:
    explicit LibraryPrivate(const std::string& name) : modlue(nullptr), name(name) {}

private:
    openv_module_t modlue;
    std::string errorString;
    std::string name;
};

ov::Library::Library(const std::string &name) : dptr(std::make_unique<LibraryPrivate>(name))
{
}

ov::Library::~Library()
{
    if(isLoaded()) {
        unload();
    }
}

bool ov::Library::load()
{
    OPENV_D(Library);
    if(d->name.empty()) {
        d->errorString = "library name is empty";
        return false;
    }

    if(isLoaded()) {
        return true;
    }

    d->modlue = openv_module_load(d->name.c_str());
    if(!d->modlue) {
        auto err = openv_module_errstr();
        d->errorString = d->name + " " + (err ? err : "library open error");
        return false;
    }

    d->errorString = {};
    return true;
}

bool ov::Library::unload()
{
    OPENV_D(Library);
    if(!isLoaded()) {
        return true;
    }

    if(!openv_module_unload(d->modlue)) {
        auto err = openv_module_errstr();
        d->errorString = d->name + " " + (err ? err : "library close error");
        return false;
    }

    d->modlue = {};
    d->errorString = {};
    return true;
}

bool ov::Library::isLoaded() const
{
    OPENV_D(const Library);
    return !!(d->modlue);
}

ov::FunctionPointer ov::Library::resolve(const char *symbol)
{
    OPENV_D(Library);
    if(!symbol) {
        d->errorString = d->name + " " + "symbol is nullptr";
        return {};
    }

    if(!isLoaded()) {
        d->errorString = d->name + " " + "library not loaded";
        return {};
    }

    auto sym = openv_module_symbol(d->modlue, symbol);
    auto err = openv_module_errstr();
    if(err) {
        d->errorString = d->name + " " + err;
        return {};
    }

    d->errorString = {};
    return sym;
}

const std::string& ov::Library::name() const
{
    OPENV_D(const Library);
    return d->name;
}

const std::string& ov::Library::errorString() const
{
    OPENV_D(const Library);
    return d->errorString;
}
