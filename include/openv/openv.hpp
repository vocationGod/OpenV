/*****************************************************************
 * 作 者 ：LJX
 * 文 件 ：openv.hpp
 * 日 期 ：2026-10-24
 * 描 述 ：公共头文件
 * 备 注 ：使用该库时只包含该头文件即可
 * ***************************************************************/
#pragma once

#include "openv/base/ovFlags.h"
#include "openv/base/ovPlugin.h"
#include "openv/base/ovEnvironment.h"

#if defined(HAVE_OPENV_PLUGIN_VCAM) || defined(HAVE_OPENV_PLUGIN_VENC) || defined(HAVE_OPENV_PLUGIN_VDEC) || defined(HAVE_OPENV_PLUGIN_VWIN) || defined(HAVE_OPENV_PLUGIN_VGFX)
    #include "openv/core/ovImage.h"
    #include "openv/core/ovSyncer.h"
#endif

#if defined(HAVE_OPENV_PLUGIN_VENC) || defined(HAVE_OPENV_PLUGIN_VDEC) || defined(HAVE_OPENV_PLUGIN_VMUX)
    #include "openv/core/ovFragment.h"
#endif

#if defined(HAVE_OPENV_PLUGIN_VCAM) || defined(HAVE_OPENV_PLUGIN_VENC)
    #include "openv/etcs/ovDegree.h"
    #include "openv/etcs/ovHFliper.h"
    #include "openv/etcs/ovVFliper.h"
#endif

#ifdef HAVE_OPENV_PLUGIN_VCAM
    #include "openv/etcs/ovFreezer.h"
#endif

#ifdef HAVE_OPENV_PLUGIN_VENC
    #include "openv/etcs/ovBps.h"
    #include "openv/etcs/ovCQp.h"
    #include "openv/etcs/ovFps.h"
    #include "openv/etcs/ovGop.h"
    #include "openv/etcs/ovIQp.h"
    #include "openv/etcs/ovQp.h"
    #include "openv/etcs/ovLevel.h"
    #include "openv/etcs/ovFactor.h"
#endif

#ifdef HAVE_OPENV_PLUGIN_VCAM
    #include "openv/plugin/vcam/ovCamera.h"
#endif

#ifdef HAVE_OPENV_PLUGIN_VENC
    #include "openv/plugin/venc/ovEncoder.h"
#endif

#ifdef HAVE_OPENV_PLUGIN_VDEC
    #include "openv/plugin/vdec/ovDecoder.h"
#endif

#ifdef HAVE_OPENV_PLUGIN_VWIN
    #include "openv/plugin/vwin/ovWindow.h"
#endif

#ifdef HAVE_OPENV_PLUGIN_VMUX
    #include "openv/plugin/vmux/ovRTSPServer.h"
#endif

#ifdef HAVE_OPENV_PLUGIN_VPSS
    #include "openv/plugin/vpss/ovProcessor.h"
#endif

#ifdef HAVE_OPENV_PLUGIN_VGFX
    #include "openv/plugin/vgfx/ovPen.h"
    #include "openv/plugin/vgfx/ovFont.h"
    #include "openv/plugin/vgfx/ovColor.h"
    #include "openv/plugin/vgfx/ovBrush.h"
    #include "openv/plugin/vgfx/ovPainter.h"
#endif
