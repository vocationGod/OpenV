#pragma once
#include "openv/openv.h"
#include <string>
#include <vector>
namespace ov {

class OPENV_API Dir final
{
public:
    static std::vector<std::string> scan(const std::string& dir, const std::vector<std::string>& patterns, bool recurse = true);
};
}