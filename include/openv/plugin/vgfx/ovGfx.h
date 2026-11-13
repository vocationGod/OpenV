#pragma once
#include "openv/base/ovFlags.h"
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

    enum PenStyle
    {
        NoPen,
        SolidLine,
    };

    enum BrushStyle
    {
        NoBrush,
        SolidPattern,
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

    enum Alignment
    {
        AlignTop        = 1 << 0,
        AlignLeft       = 1 << 1,
        AlignRight      = 1 << 2,
        AlignBottom     = 1 << 3,
        AlignHCenter    = 1 << 4,
        AlignVCenter    = 1 << 5,
        AlignCenter     = AlignVCenter | AlignHCenter,
    };
    using Alignments = Flags<Alignment>;

    OPENV_FLAGS_ENABLE_OPERATORS(ov::Alignment)
}   