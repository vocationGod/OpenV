/*****************************************************************
 * 作 者 ：LJX
 * 文 件 ：OMedia.h
 * 日 期 ：2026-10-24
 * 描 述 ：音视频编码类型
 * 备 注 ：OPENV_DECLARE_MEDIA_TOKENS宏为(编码格式)
 * ***************************************************************/
#pragma once
#include "openv/openv.h"
#define OPENV_DECLARE_MEDIA_TOKENS(F)\
    /* MPEG1 */                                 \
    F(MPEG1)                                    \
    /* H.262 */                                 \
    F(MPEG2)                                    \
    /* H.263 */                                 \
    F(H263)                                     \
    /* MPEG-4 */                                \
    F(MPEG4)                                    \
    /* Windows Media Video (WMV1,WMV2,WMV3) */  \
    F(WMV)                                      \
    /* All Versions Of Real Video */            \
    F(RV)                                       \
    /* H.264 */                                 \
    F(H264)                                     \
    /* Motion JPEG */                           \
    F(MJPEG)                                    \
    /* VP8 */                                   \
    F(VP8)                                      \
    /* VP9 */                                   \
    F(VP9)                                      \
    /* ITU H.265/HEVC */                        \
    F(H265)                                     \
    /* JPEG */                                  \
    F(JPEG)                                     \
    /* Windows Media Video (WMV1,WMV2,WMV3) */  \
    F(VC1)                                      \
    /* DIVX3 */                                 \
    F(DIVX3)                                    \
    /* VP6 */                                   \
    F(VP6)                                      \
    /* AVS+ */                                  \
    F(AVSPLUS)                                  \
    /* AVS */                                   \
    F(AVS)                                      \
    /* AV1 */                                   \
    F(AV1)                                      \
    F(NONE)

namespace ov {
enum class Media : int 
{
#define CREATE_ENUM(a)    a,
    OPENV_DECLARE_MEDIA_TOKENS(CREATE_ENUM)
#undef  CREATE_ENUM
};    
}