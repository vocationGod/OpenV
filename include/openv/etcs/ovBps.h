/*****************************************************************
 * 作 者 ：LJX
 * 文 件 ：OBps.h
 * 日 期 ：2026-10-25
 * 描 述 ：码率拓展功能
 * 备 注 ：单位：kbps
 * ***************************************************************/
#pragma once
#include "openv/base/ovPlugin.h"
namespace ov {

class OPENV_API Bps
{
public:
    virtual void bps(int* min, int* avg, int* max) const = 0;
    virtual bool setBps(int min, int avg, int max) = 0;
};

OPENV_DECLARE_INTERFACE(Bps, "ov.iid.venc.bps")
}