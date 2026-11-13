/*****************************************************************
 * 作 者 ：LJX
 * 文 件 ：ODecoder.h
 * 日 期 ：2026-10-25
 * 描 述 ：音视频解码设备
 * 备 注 ：插件派生必须实现 setup()、resume()、pause()、shutdown()、transmit()、receive()；notifier()为可选实现
 * ***************************************************************/
#pragma once
#include "openv/core/ovElement.h"
#include "openv/core/ovMedia.h"
#include <memory>
#include <string>
namespace ov {

class Image;
class Fragment;
class DecoderPrivate;
class OPENV_API Decoder : public Element
{
    OPENV_DECLARE_PRIVATE(Decoder)
    OPENV_DISABLE_COPY(Decoder)
public:
    static std::shared_ptr<ov::Decoder> gen(int width, int height, Media media, int capacity, const std::string& dir = "./plugins");

public:
    ~Decoder();

public:
    int width() const;

    int height() const;

    int capacity() const;

    ov::Media media() const;

    std::optional<int> descriptor() const;

    std::shared_ptr<ov::Image> acquire(int timeout = -1);

    bool submit(const std::shared_ptr<ov::Fragment>& fragment, int timeout = 0);

protected:
    virtual int notifier() const = 0;

    virtual std::shared_ptr<ov::Image> receive(int timeout) = 0;

    virtual bool transmit(const std::shared_ptr<ov::Fragment>& fragment, int timeout) = 0;

protected:
    explicit Decoder();

private:
    std::unique_ptr<DecoderPrivate> dptr;
};

OPENV_DECLARE_INTERFACE(Decoder, "ov.iid.decoder")
}