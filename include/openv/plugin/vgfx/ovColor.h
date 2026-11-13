#pragma once
#include "openv/openv.h"
#include <cstdint>
namespace ov {

enum GlobalColor
{
    white,          // #ffffffff
    black,          // #000000ff 
    red,            // #ff0000ff 
    darkRed,        // #800000ff 
    green,          // #00ff00ff 
    darkGreen,      // #008000ff 
    blue,           // #0000ffff 
    darkBlue,       // #000080ff 
    cyan,           // #00ffffff 
    darkCyan,       // #008080ff 
    magenta,        // #ff00ffff 
    darkMagenta,    // #800080ff 
    yellow,         // #ffff00ff 
    darkYellow,     // #808000ff 
    gray,           // #a0a0a4ff
    darkGray,       // #808080ff
    lightGray,      // #c0c0c0ff 
    transparent,    // #00000000
};

class OPENV_API Color final
{
public:
    static ov::Color fromRGB(int r, int g, int b, int a = 255);
    static ov::Color fromRGBF(float r, float g, float b, float a = 1.0f);

public:
    Color(GlobalColor color = ov::black);
    Color(int r, int g, int b, int a = 255);
    Color(float r, float g, float b, float a = 1.0f);

public:
    int red() const;
    void setRed(int red);

    int green() const;
    void setGreen(int green);

    int blue() const;
    void setBlue(int blue);

    int alpha() const;
    void setAlpha(int alpha);

    float redF() const;
    void setRedF(float red);

    float greenF() const;
    void setGreenF(float green);

    float blueF() const;
    void setBlueF(float blue);

    float alphaF() const;
    void setAlphaF(float alpha);

    bool operator==(const Color& rhs) const;
    bool operator!=(const Color& rhs) const;

    ov::Color& operator=(GlobalColor color);

private:
    uint8_t r, g, b, a;
};
}