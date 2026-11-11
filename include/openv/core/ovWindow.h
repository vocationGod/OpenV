/*****************************************************************
 * 作 者 ：LJX
 * 文 件 ：OWindow.h
 * 日 期 ：2026-10-25
 * 描 述 ：音视频显示设备
 * 备 注 ：插件派生必须实现 setup()、resume()、pause()、shutdown()transmit()；notifier()为可选实现
 * ***************************************************************/
#pragma once
#include "openv/core/ovElement.h"
#include "openv/core/ovLayout.h"
#include <string>
namespace ov {

class Image;
class WindowPrivate;
class OPENV_API Window : public Element
{
    OPENV_DECLARE_PRIVATE(Window)
    OPENV_DISABLE_COPY(Window)
public:
    enum Connector
    {
        DP,    
        DP1, 
        EDP,
        VGA, 
        LCD,
        EDP1, 
        CVBS,
        LVDS,  
        MIPI, 
        HDMI, 
        MIPI1, 
        HDMI1,   
        YPBPR,     
        BT656,  
        BT1120,   
        NONE,
    };

    struct Geometry { int x; int y; int w; int h; };
    
public:
    static std::shared_ptr<ov::Window> gen(Connector connector, int width, int height, Layout layout, int capacity, const std::string& dir = "./plugins");
    static std::shared_ptr<ov::Window> gen(Connector connector, Geometry geometry, int width, int height, Layout layout, int capacity, const std::string& dir = "./plugins");

public:
    ~Window();

public:
    int width() const;

    int height() const;

    int capacity() const;

    ov::Layout layout() const;

    ov::Window::Geometry geometry() const;

    ov::Window::Connector connector() const;

    bool submit(const std::shared_ptr<ov::Image>& image, int timeout = 0);

protected:
    virtual bool transmit(const std::shared_ptr<ov::Image>& image, int timeout) = 0;

protected:
    explicit Window();
};

OPENV_DECLARE_INTERFACE(Window, "ov.iid.window")
}