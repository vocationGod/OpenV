/*****************************************************************
 * 作 者 ：LJX
 * 文 件 ：OFreezer.h
 * 日 期 ：2026-10-25
 * 描 述 ：冻结拓展功能
 * 备 注 ：无
 * ***************************************************************/
#pragma once
#include "openv/base/ovPlugin.h"
namespace ov {

class OPENV_API Freezer
{
public:
    virtual bool isFrozen() const = 0;
    virtual bool setFrozen(bool freeze) = 0;
};

OPENV_DECLARE_INTERFACE(Freezer, "ov.iid.vcam.freezer")
}