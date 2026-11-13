/*****************************************************************
 * 作 者 ：LJX
 * 文 件 ：OQp.h
 * 日 期 ：2026-10-25
 * 描 述 ：量化参数拓展功能
 * 备 注 ：无
 * ***************************************************************/
#pragma once
#include "openv/base/ovPlugin.h"
namespace ov {

class OPENV_API Qp 
{
public:
    virtual void qp(int* min, int* max) const = 0;
    virtual bool setQp(int min, int max) = 0;
};

OPENV_DECLARE_INTERFACE(Qp, "ov.iid.venc.qp")
}