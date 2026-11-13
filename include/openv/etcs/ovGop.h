/*****************************************************************
 * 作 者 ：LJX
 * 文 件 ：OGop.h
 * 日 期 ：2026-10-25
 * 描 述 ：I帧间隔拓展功能
 * 备 注 ：无
 * ***************************************************************/
#pragma once
#include "openv/base/ovPlugin.h"
namespace ov {

class OPENV_API Gop 
{
public:
    virtual int gop() const = 0;
    virtual bool setGop(int gop) = 0;
};

OPENV_DECLARE_INTERFACE(Gop, "ov.iid.venc.gop")
}