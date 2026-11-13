#pragma once
#include "openv/openv.h"
#include <string>
namespace ov {

class OPENV_API Environment final
{
public:
    static std::string value(const std::string& key);
    
    static bool setValue(const std::string& key, const std::string& var);
};
}