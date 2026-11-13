/*****************************************************************
 * 作 者 ：LJX
 * 文 件 ：OSyncer.h
 * 日 期 ：2026-10-24
 * 描 述 ：音视频帧内存同步器
 * 备 注 ：dma-buf-cached需使用该类进行内存同步
 * ***************************************************************/
#pragma once
#include "openv/openv.h"
#include <memory>
namespace ov {

class Image;
class SyncerPrivate;
class OPENV_API Syncer final
{
    OPENV_DECLARE_PRIVATE(Syncer)
    OPENV_DISABLE_COPY(Syncer)
public:
    explicit Syncer(const std::shared_ptr<Image>& image);
    ~Syncer();

public:
    bool sync();

private:
    std::unique_ptr<SyncerPrivate> dptr;
};
}