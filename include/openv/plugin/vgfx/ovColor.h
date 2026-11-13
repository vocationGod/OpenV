#pragma once
#include "openv/plugin/vgfx/ovGfx.h"
#include "openv/openv.h"
#include <cstdint>
namespace ov {

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