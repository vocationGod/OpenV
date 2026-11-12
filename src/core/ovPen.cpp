#include "ovPen.h"
#include <algorithm>

ov::Pen::Pen(PenStyle style) : Pen(ov::black, 2, style)
{
}

ov::Pen::Pen(const Color &color)  : Pen(color, 2)
{
}

ov::Pen::Pen(const Color &color, double width, PenStyle style, PenCapStyle cap, PenJoinStyle join)
    : chroma(color), thick(width), penStyle(style), penCap(cap), penJoin(join)
{
}

ov::Color ov::Pen::color() const
{
    return chroma;
}

void ov::Pen::setColor(const Color &color)
{
    chroma = color;
}

double ov::Pen::width() const
{
    return thick;
}

void ov::Pen::setWidth(double width)
{
    thick = std::max(1.0, width);
}

ov::PenStyle ov::Pen::style() const
{
    return penStyle;
}

void ov::Pen::setStyle(PenStyle style)
{
    penStyle = style;
}

ov::PenCapStyle ov::Pen::capStyle() const
{
    return penCap;
}

void ov::Pen::setCapStyle(PenCapStyle cap)
{
    penCap = cap;
}

ov::PenJoinStyle ov::Pen::joinStyle() const
{
    return penJoin;
}

void ov::Pen::setJoinStyle(PenJoinStyle join)
{
    penJoin = join;
}

bool ov::Pen::operator==(const Pen &rhs) const
{
    return (chroma == rhs.chroma) && (thick == rhs.thick) && (penStyle == rhs.penStyle) && (penCap == rhs.penCap) && (penJoin == rhs.penJoin);
}

bool ov::Pen::operator!=(const Pen &rhs) const
{
    return !(*this == rhs);
}
