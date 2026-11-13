/*****************************************************************
 * 作 者 ：LJX
 * 文 件 ：ODegree.h
 * 日 期 ：2026-10-25
 * 描 述 ：旋转角度拓展功能
 * 备 注 ：单位：角度
 * ***************************************************************/
#pragma once
#include "openv/base/ovPlugin.h"
namespace ov {

class OPENV_API Degree 
{
public:
    virtual float degree() const = 0;
    virtual bool setDegree(float degree) = 0;
};

OPENV_DECLARE_INTERFACE(Degree, "ov.iid.degree")
}