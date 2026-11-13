/*****************************************************************
 * 作 者 ：LJX
 * 文 件 ：OFragment.h
 * 日 期 ：2026-10-24
 * 描 述 ：音视频编码码流
 * 备 注 ：必须gen函数创建共享智能指针实例
 * ***************************************************************/
#pragma once
#include "openv/core/ovMedia.h"
#include "openv/openv.h"
#include <functional>
#include <cstddef>
#include <memory>
namespace ov {

class FragmentPrivate;
class OPENV_API Fragment final
{
    OPENV_DECLARE_PRIVATE(Fragment)
    OPENV_DISABLE_COPY(Fragment)
public:
    enum Type
    {
        VPS,
        SEI,
        SPS,
        PPS,
        BSLICE,
        PSLICE,
        ISLICE,
        IDRSLICE,
        NONE,
    };

public:
    static std::shared_ptr<ov::Fragment> gen(size_t sizeInBytes, Media media = Media::NONE, Type type = Fragment::NONE, int64_t timestamp = {}, std::function<void(void*)> cleaner = {}, void* opaque = {});
    static std::shared_ptr<ov::Fragment> gen(std::byte* bits, size_t sizeInBytes, Media media = Media::NONE, Type type = Fragment::NONE, int64_t timestamp = {}, std::function<void(void*)> cleaner = {}, void* opaque = {});

public:
    ~Fragment();
    
public:
    std::byte* bits();

    bool empty() const;

    int64_t timestamp() const;

    size_t sizeInBytes() const;

    ov::Media media() const;

    const std::byte* bits() const;

    ov::Fragment::Type type() const;

protected:
    explicit Fragment(std::byte* bits, size_t sizeInBytes, Media media, Type type, int64_t timestamp, std::function<void(void*)> cleaner, void* opaque);

private:
    std::unique_ptr<FragmentPrivate> dptr;
};
}