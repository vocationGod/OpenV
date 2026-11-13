#include "ovFont.h"

ov::Font::Font() : Font("")
{
}

ov::Font::Font(const std::string &family, double pixelSize) : name(family), size(pixelSize)
{
}

const std::string& ov::Font::family() const
{
    return name;
}

void ov::Font::setFamily(const std::string &family)
{
    name = family;
}

double ov::Font::pixelSize() const
{
    return size;
}

void ov::Font::setPixelSize(double pixelSize)
{
    size = pixelSize;
}

bool ov::Font::operator==(const Font &rhs) const
{
    return (name == rhs.name) && (size == rhs.size);
}

bool ov::Font::operator!=(const Font &rhs) const
{
    return !(*this == rhs);
}
