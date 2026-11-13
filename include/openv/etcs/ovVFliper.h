/*****************************************************************
 * 作 者 ：LJX
 * 文 件 ：OQp.h
 * 日 期 ：2026-10-25
 * 描 述 ：垂直翻转拓展功能
 * 备 注 ：无
 * ***************************************************************/
#pragma once
#include "openv/base/ovPlugin.h"
namespace ov {

class OPENV_API VFliper
{
public:
    virtual bool isVFlipped() const = 0;
    virtual bool setVFlip(bool on) = 0;
};

OPENV_DECLARE_INTERFACE(VFliper, "ov.iid.vflipper")
}