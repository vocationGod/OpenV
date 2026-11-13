/*****************************************************************
 * 作 者 ：LJX
 * 文 件 ：OLevel.h
 * 日 期 ：2026-10-25
 * 描 述 ：编码档次拓展功能
 * 备 注 ：无
 * ***************************************************************/
#pragma once
#include "openv/base/ovPlugin.h"
namespace ov {

class OPENV_API Level 
{
public:
    enum Profile { Baseline, Main, High };

public:
    virtual Profile profile() const = 0;
    virtual bool setProfile(Profile level) = 0;
};

OPENV_DECLARE_INTERFACE(Level, "ov.iid.venc.profile")
}