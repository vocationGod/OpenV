/*****************************************************************
 * 作 者 ：LJX
 * 文 件 ：OLayout.h
 * 日 期 ：2026-10-24
 * 描 述 ：音视频帧格式
 * 备 注 ：OPENV_DECLARE_LAYOUT_TOKENS宏为(排列格式、排列深度、排列位数)
 * ***************************************************************/
#pragma once
#include "openv/openv.h"
#define OPENV_DECLARE_LAYOUT_TOKENS(F) \
    /* YYYY...                      (1 plane) */ \
    F(GREY,         8,      8)  \
    /* YYYY... UUUU... VVVV         (3 plane) */ \
    F(YUV420P,      8,      12) \
    /* YYYY... UUUU... VVVV         (3 plane) */ \
    F(YUV422P,      8,      16) \
    /* YYYY... UV...                (2 plane) */ \
    F(YUV420SP,     8,      12) \
    /* YYYY... UVUV...              (2 plane) */ \
    F(YUV422SP,     8,      16) \
    /* YUYVYUYV...                  (1 plane) */ \
    F(YUYV,         16,     16) \
    /* UYVYUYVY...                  (1 plane) */ \
    F(UYVY,         16,     16) \
    /* YVYUYVYU...                  (1 plane) */ \
    F(YVYU,         16,     16) \
    /* VYUYVYUY...                  (1 plane) */ \
    F(VYUY,         16,     16) \
    /* 24-bit RGB */ \
    F(RGB888,       24,     24) \
    /* 24-bit RGB */ \
    F(BGR888,       24,     24) \
    /* 32-bit RGB */ \
    F(ARGB8888,     32,     32) \
    /* 32-bit RGB */ \
    F(ABGR8888,     32,     32) \
    /* 32-bit RGB */ \
    F(BGRA8888,     32,     32) \
    /* 32-bit RGB */ \
    F(RGBA8888,     32,     32) \
    /* 8-bit raw */ \
    F(SBGGR8,       8,      8)  \
    /* 8-bit raw */ \
    F(SGBRG8,       8,      8)  \
    /* 8-bit raw */ \
    F(SGRBG8,       8,      8)  \
    /* 8-bit raw */ \
    F(SRGGB8,       8,      8)  \
    /* 10-bit raw */ \
    F(SBGGR10,      10,     10) \
    /* 10-bit raw */ \
    F(SGBRG10,      10,     10) \
    /* 10-bit raw */ \
    F(SGRBG10,      10,     10) \
    /* 10-bit raw */ \
    F(SRGGB10,      10,     10) \
    /* 12-bit raw */ \
    F(SBGGR12,      12,     12) \
    /* 12-bit raw */ \
    F(SGBRG12,      12,     12) \
    /* 12-bit raw */ \
    F(SGRBG12,      12,     12) \
    /* 12-bit raw */ \
    F(SRGGB12,      12,     12) \
    /* 16-bit raw */ \
    F(SBGGR16,      16,     16) \
    /* 16-bit raw */ \
    F(SGBRG16,      16,     16) \
    /* 16-bit raw */ \
    F(SGRBG16,      16,     16) \
    /* 16-bit raw */ \
    F(SRGGB16,      16,     16) \
    F(NONE,         0,      0)

namespace ov {
enum class Layout : int 
{
#define CREATE_ENUM(a, b, c)    a,
    OPENV_DECLARE_LAYOUT_TOKENS(CREATE_ENUM)
#undef  CREATE_ENUM
};
}