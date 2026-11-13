#include "ovEnvironment.h"
#include <cstdlib>

std::string ov::Environment::value(const std::string& key)
{
    if(key.empty()) {
        return "";
    }

    auto var = std::getenv(key.c_str());
    if(!var) {
        return "";
    }

    return var;
}

bool ov::Environment::setValue(const std::string& key, const std::string& var)
{
    if(key.empty()) {
        return false;
    }

#ifdef _WIN32
    return _putenv_s(key.c_str(), var.c_str()) == 0;
#else
    return setenv(key.c_str(), var.c_str(), 1) == 0;
#endif 
}
