#include "ovColor.h"
#include <algorithm>

ov::Color ov::Color::fromRGB(int r, int g, int b, int a)
{
    return Color(r, g, b, a);
}

ov::Color ov::Color::fromRGBF(float r, float g, float b, float a)
{
    return Color(r, g, b, a);
}

ov::Color::Color(GlobalColor color)
{
    *this = color;
}

ov::Color::Color(int r, int g, int b, int a)
{
    setRed(r);
    setGreen(g);
    setBlue(b);
    setAlpha(a);
}

ov::Color::Color(float r, float g, float b, float a)
{
    setRedF(r);
    setGreenF(g);
    setBlueF(b);
    setAlphaF(a);
}

int ov::Color::red() const
{
    return r;
}

void ov::Color::setRed(int red)
{
    r = std::clamp(0, red, 255);
}

int ov::Color::green() const
{
    return g;
}

void ov::Color::setGreen(int green)
{
    g = std::clamp(0, green, 255);
}

int ov::Color::blue() const
{
    return b;
}

void ov::Color::setBlue(int blue)
{
    b = std::clamp(0, blue, 255);
}

int ov::Color::alpha() const
{
    return a;
}

void ov::Color::setAlpha(int alpha)
{
    a = std::clamp(0, alpha, 255);
}

float ov::Color::redF() const
{
    return r/255.0f;
}

void ov::Color::setRedF(float red)
{
    r = std::clamp(0.0f, red, 1.0f) * 255;
}

float ov::Color::greenF() const
{
    return g/255.0f;
}

void ov::Color::setGreenF(float green)
{
    g = std::clamp(0.0f, green, 1.0f) * 255;
}

float ov::Color::blueF() const
{
    return b/255.0f;
}

void ov::Color::setBlueF(float blue)
{
    b = std::clamp(0.0f, blue, 1.0f) * 255;
}

float ov::Color::alphaF() const
{
    return a/255.0f;
}

void ov::Color::setAlphaF(float alpha)
{
    a = std::clamp(0.0f, alpha, 1.0f) * 255;
}

bool ov::Color::operator==(const Color &rhs) const
{
    return (r == rhs.r) && (g == rhs.g) && (b == rhs.b) && (a == rhs.a);
}

bool ov::Color::operator!=(const Color &rhs) const
{
    return !(*this == rhs);
}

ov::Color &ov::Color::operator=(GlobalColor color)
{
    switch(color) {
    case GlobalColor::white      : r = 255; g = 255; b = 255; a = 255; break;
    case GlobalColor::black      : r =   0; g =   0; b =   0; a = 255; break;
    case GlobalColor::red        : r = 255; g =   0; b =   0; a = 255; break;
    case GlobalColor::darkRed    : r = 128; g =   0; b =   0; a = 255; break;
    case GlobalColor::green      : r =   0; g = 255; b =   0; a = 255; break;
    case GlobalColor::darkGreen  : r =   0; g = 128; b =   0; a = 255; break;
    case GlobalColor::blue       : r =   0; g =   0; b = 255; a = 255; break;
    case GlobalColor::darkBlue   : r =   0; g =   0; b = 128; a = 255; break;
    case GlobalColor::cyan       : r =   0; g = 255; b = 255; a = 255; break;
    case GlobalColor::darkCyan   : r =   0; g = 128; b = 128; a = 255; break;
    case GlobalColor::magenta    : r = 255; g =   0; b = 255; a = 255; break;
    case GlobalColor::darkMagenta: r = 128; g =   0; b = 128; a = 255; break;
    case GlobalColor::yellow     : r = 255; g = 255; b =   0; a = 255; break;
    case GlobalColor::darkYellow : r = 128; g = 128; b =   0; a = 255; break;
    case GlobalColor::gray       : r = 160; g = 160; b = 164; a = 255; break;
    case GlobalColor::darkGray   : r = 128; g = 128; b = 128; a = 255; break;
    case GlobalColor::lightGray  : r = 192; g = 192; b = 192; a = 255; break;
    case GlobalColor::transparent: r =   0; g =   0; b =   0; a =   0; break;
    }

    return *this;
}
