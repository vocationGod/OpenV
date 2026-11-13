/*****************************************************************
 * 作 者 ：LJX
 * 文 件 ：OCQp.h
 * 日 期 ：2026-10-25
 * 描 述 ：恒定量化参数拓展功能
 * 备 注 ：无
 * ***************************************************************/
#pragma once
#include "openv/base/ovPlugin.h"
namespace ov {

class OPENV_API CQp 
{
public:
    virtual void cqp(int* iqp, int* pqp, int* bqp) const = 0;
    virtual bool setCQp(int iqp, int pqp, int bqp) = 0;
};

OPENV_DECLARE_INTERFACE(CQp, "ov.iid.venc.cqp")
}