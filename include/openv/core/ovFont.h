#pragma once
#include "openv/openv.h"
#include <string>
namespace ov {

class OPENV_API Font final
{
public:
    Font();
    Font(const std::string&family, double pixelSize = 25);

public:
    std::string family() const;
    void setFamily(const std::string& family);

    double pixelSize() const;
    void setPixelSize(double pixelSize);

    bool operator==(const Font& rhs) const;
    bool operator!=(const Font& rhs) const;

private:
    std::string name;
    double size;
};
}