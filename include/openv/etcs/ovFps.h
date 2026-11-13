/*****************************************************************
 * 作 者 ：LJX
 * 文 件 ：OFps.h
 * 日 期 ：2026-10-25
 * 描 述 ：帧率控制拓展功能
 * 备 注 ：无
 * ***************************************************************/
#pragma once
#include "openv/base/ovPlugin.h"
namespace ov {

class OPENV_API Fps 
{
public:
    virtual void fps(int* src, int* dst) const = 0;
    virtual bool setFps(int src, int dst) = 0;
};

OPENV_DECLARE_INTERFACE(Fps, "ov.iid.fps")
}