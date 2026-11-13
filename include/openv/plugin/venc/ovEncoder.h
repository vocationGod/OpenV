/*****************************************************************
 * 作 者 ：LJX
 * 文 件 ：OEncoder.h
 * 日 期 ：2026-10-25
 * 描 述 ：音视频编码设备
 * 备 注 ：插件派生必须实现 setup()、resume()、pause()、shutdown()、transmit()、receive()；notifier()为可选实现
 * ***************************************************************/
#pragma once
#include "openv/core/ovElement.h"
#include "openv/core/ovLayout.h"
#include "openv/core/ovMedia.h"
#include <optional>
#include <memory>
#include <string>
namespace ov {

class Image;
class Fragment;
class EncoderPrivate;
class OPENV_API Encoder : public Element
{
    OPENV_DECLARE_PRIVATE(Encoder)
    OPENV_DISABLE_COPY(Encoder)
public:
    static std::shared_ptr<ov::Encoder> gen(int width, int height, Layout layout, Media media, int capacity, const std::string& dir = "./plugins");

public:
    ~Encoder();

public:
    int width() const;

    int height() const;

    int capacity() const;

    ov::Media media() const;

    ov::Layout layout() const;

    std::optional<int> descriptor() const;

    std::shared_ptr<ov::Fragment> acquire(int timeout = -1);

    bool submit(const std::shared_ptr<ov::Image>& image, int timeout = 0);

protected:
    virtual int notifier() const = 0;

    virtual std::shared_ptr<ov::Fragment> receive(int timeout) = 0;

    virtual bool transmit(const std::shared_ptr<ov::Image>& image, int timeout) = 0;

protected:
    explicit Encoder();

private:
    std::unique_ptr<EncoderPrivate> dptr;
};

OPENV_DECLARE_INTERFACE(Encoder, "ov.iid.encoder")
}