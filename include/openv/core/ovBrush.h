#pragma once
#include "openv/core/ovColor.h"
namespace ov {

class OPENV_API Brush final
{
public:
    Brush(BrushStyle style = NoBrush);
    Brush(const Color& color, BrushStyle style = SolidPattern);

public:
    ov::Color color() const;
    void setColor(const Color& color);

    ov::BrushStyle style() const;
    void setStyle(BrushStyle style);

    bool operator==(const Brush& rhs) const;
    bool operator!=(const Brush& rhs) const;

private:
    Color chroma;
    BrushStyle brushStyle;
};
}