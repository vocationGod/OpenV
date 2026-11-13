#include "ovBrush.h"

ov::Brush::Brush(BrushStyle style) : Brush(ov::black, style)
{
}

ov::Brush::Brush(const Color &color, BrushStyle style)
    : chroma(color), brushStyle(style)
{
}

const ov::Color& ov::Brush::color() const
{
    return chroma;
}

void ov::Brush::setColor(const Color &color)
{
    chroma = color;
}

ov::BrushStyle ov::Brush::style() const
{
    return brushStyle;
}

void ov::Brush::setStyle(BrushStyle style)
{
    brushStyle = style;
}

bool ov::Brush::operator==(const Brush &rhs) const
{
    return (chroma == rhs.chroma) && (brushStyle == rhs.brushStyle);
}

bool ov::Brush::operator!=(const Brush &rhs) const
{
    return !(*this == rhs);
}
