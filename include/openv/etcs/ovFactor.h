/*****************************************************************
 * 作 者 ：LJX
 * 文 件 ：OFactor.h
 * 日 期 ：2026-10-25
 * 描 述 ：编码图像质量拓展功能
 * 备 注 ：MJPEG生效
 * ***************************************************************/
#pragma once
#include "openv/base/ovPlugin.h"
namespace ov {

class OPENV_API Factor 
{
public:
    virtual int factor() const = 0;
    virtual bool setFactor(int factor) = 0;
};

OPENV_DECLARE_INTERFACE(Factor, "ov.iid.mjpeg.qfactor")
}