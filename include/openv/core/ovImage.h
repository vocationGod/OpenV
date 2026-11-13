/*****************************************************************
 * 作 者 ：LJX
 * 文 件 ：OImage.h
 * 日 期 ：2026-10-24
 * 描 述 ：音视频帧
 * 备 注 ：必须gen函数创建共享智能指针实例；搭配OSyncer实现内存同步功能。
 * ***************************************************************/
#pragma once
#include "openv/core/ovLayout.h"
#include "openv/openv.h"
#include <functional>
#include <optional>
#include <cstddef>
#include <memory>
namespace ov {

class ImagePrivate;
class OPENV_API Image final
{
    OPENV_DECLARE_PRIVATE(Image)
    OPENV_DISABLE_COPY(Image)
public:
    static std::shared_ptr<ov::Image> gen(int width, int height, Layout layout, long timestamp = {}, std::function<void(void*)> cleaner = {}, void* opaque = {});
    static std::shared_ptr<ov::Image> gen(std::byte* bits, int width, int height, Layout layout, int bytesPerLine, int sizeInBytes, long timestamp = {}, std::function<void(void*)> cleaner = {}, void* opaque = {});
    static std::shared_ptr<ov::Image> gen(std::byte* bits, int handle, int width, int height, Layout layout, int bytesPerLine, int sizeInBytes, long timestamp = {}, std::function<void(void*)> cleaner = {}, void* opaque = {});

public:
    ~Image();

public:
    std::byte* bits();

    int width() const;

    int height() const;

    bool empty() const;

    long timestamp() const;

    int sizeInBytes() const;

    int bytesPerLine() const;

    ov::Layout layout() const;

    const std::byte* bits() const;

    std::optional<int> handle() const;

protected:
    explicit Image(std::byte* bits, int handle, int width, int height, Layout layout, int bytesPerLine, int sizeInBytes, long timestamp, std::function<void(void*)> cleaner, void* opaque);

private:
    std::unique_ptr<ImagePrivate> dptr;
};
}