#pragma once
#include "openv/plugin/vgfx/ovColor.h"
namespace ov {

class OPENV_API Brush final
{
public:
    Brush(BrushStyle style = NoBrush);
    Brush(const Color& color, BrushStyle style = SolidPattern);

public:
    const ov::Color& color() const;
    void setColor(const Color& color);

    ov::BrushStyle style() const;
    void setStyle(BrushStyle style);

    bool operator==(const Brush& rhs) const;
    bool operator!=(const Brush& rhs) const;

    bool operator==(BrushStyle style) const;
    bool operator!=(BrushStyle style) const;

private:
    Color chroma;
    BrushStyle brushStyle;
};
}