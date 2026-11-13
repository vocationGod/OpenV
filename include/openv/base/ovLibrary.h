#pragma once
#include "openv/openv.h"
#include <string>
#include <memory>
namespace ov {

using FunctionPointer = void(*)();

class LibraryPrivate;
class OPENV_API Library final 
{
    OPENV_DECLARE_PRIVATE(Library)
    OPENV_DISABLE_COPY(Library)
public:
    explicit Library(const std::string& name);
    ~Library();

public:
    bool load();
    
    bool unload();
    
    bool isLoaded() const;

    const std::string& name() const;
    
    const std::string& errorString() const;

    ov::FunctionPointer resolve(const char* symbol);

private:
    std::unique_ptr<LibraryPrivate> dptr;
};
}