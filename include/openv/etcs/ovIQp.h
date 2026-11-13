/*****************************************************************
 * 作 者 ：LJX
 * 文 件 ：OIQp.h
 * 日 期 ：2026-10-25
 * 描 述 ：I帧量化参数拓展功能
 * 备 注 ：无
 * ***************************************************************/
#pragma once
#include "openv/base/ovPlugin.h"
namespace ov {

class OPENV_API IQp 
{
public:
    virtual void iqp(int* min, int* max) const = 0;
    virtual bool setIQp(int min, int max) = 0;
};

OPENV_DECLARE_INTERFACE(IQp, "ov.iid.venc.iqp")
}