#pragma once
#include "openv/plugin/vgfx/ovColor.h"
namespace ov {

enum PenStyle
{
    NoPen,
    SolidLine,
};

enum PenCapStyle
{
    FlatCap,
    SquareCap,
    RoundCap,
};

enum PenJoinStyle
{
    MiterJoin,
    BevelJoin,
    RoundJoin,
};

class OPENV_API Pen final
{
public:
    Pen(PenStyle style = NoPen);
    Pen(const Color &color, double width = 2, PenStyle style = SolidLine, PenCapStyle cap = SquareCap, PenJoinStyle join = BevelJoin);

public:
    const ov::Color& color() const;
    void setColor(const Color& color);

    double width() const;
    void setWidth(double width);

    ov::PenStyle style() const;
    void setStyle(PenStyle style);

    ov::PenCapStyle capStyle() const;
    void setCapStyle(PenCapStyle cap);

    ov::PenJoinStyle joinStyle() const;
    void setJoinStyle(PenJoinStyle join);

    bool operator==(const Pen& rhs) const;
    bool operator!=(const Pen& rhs) const;

    bool operator==(PenStyle style) const;
    bool operator!=(PenStyle style) const;
private:
    Color chroma;
    double thick;
    PenStyle penStyle;
    PenCapStyle penCap;
    PenJoinStyle penJoin;
};
}