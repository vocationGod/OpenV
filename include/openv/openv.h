#pragma once

#define OPENV_VERSION_MAJOR 0
#define OPENV_VERSION_MINOR 0
#define OPENV_VERSION_PATCH 1

#if defined(_WIN32) || defined(__CYGWIN__)
    #if defined(OPENV_BUILD)
        #define OPENV_API __declspec(dllexport)
    #else
        #define OPENV_API __declspec(dllimport)
    #endif
#elif defined(__GNUC__) || defined(__clang__)
    #define OPENV_API __attribute__((visibility("default")))
#else
    #define OPENV_API
#endif

#define OPENV_DISABLE_COPY(A) \
    A (const A&) = delete; \
    A& operator= (const A&) = delete;

#define OPENV_DECLARE_PRIVATE(A) \
    protected: \
    A ## Private* d_func() { return reinterpret_cast<A ## Private*>(dptr.get()); } \
    const A ## Private* d_func() const { return reinterpret_cast<const A ## Private*>(dptr.get()); } \
    friend class A ## Private;

#define OPENV_DECLARE_PUBLIC(A) \
    friend class A;

#define OPENV_D(A) A ## Private * const d = d_func()

#define OPENV_ALIGN(x, align)  (((x) + (align) - 1) & ~((align) - 1))

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
}   
