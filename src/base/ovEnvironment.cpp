#include "ovEnvironment.h"
#include <cstdlib>

const char *ov::Environment::value(const char *key)
{
    if(!key) {
        return {};
    }

    return std::getenv(key);
}

bool ov::Environment::setValue(const char *key, const char *var)
{
    if(!key || !var) {
        return false;
    }

#ifdef _WIN32
    #define setenv(key, var, rep)   _putenv_s(key, var)
#endif

    return setenv(key, var, 1) == 0; 
}
