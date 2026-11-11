#pragma once
#include "openv/openv.h"
namespace ov {

class OPENV_API Environment final
{
public:
    static const char* value(const char* key);
    
    static bool setValue(const char* key, const char* var);
};
}