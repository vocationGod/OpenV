#pragma once
#include "openv/base/ovPlugin.h"
#include "openv/base/ovFlags.h"
#include "openv/core/ovBrush.h"
#include "openv/core/ovFont.h"
#include "openv/core/ovPen.h"
#include <memory>
#include <string>
namespace ov {

class Image;
class PainterPrivate;
class OPENV_API Painter : public Plugin
{
    OPENV_DECLARE_PRIVATE(Painter)
    OPENV_DISABLE_COPY(Painter)
public:
    enum RenderHint
    {
        Antialiasing = 1 << 0,
    };
    using RenderHints = Flags<RenderHint>;

public:
    static std::shared_ptr<ov::Painter> gen(const std::string& dir = "./plugins");

public:
    ~Painter();

public:
    ov::Pen pen() const;
    void setPen(const Pen& pen);

    ov::Brush brush() const;
    void setBrush(const Brush& brush);

    ov::Font font() const;
    void setFont(const Font& font);

    double opacity() const;
    void setOpacity(double opacity);

    ov::Painter::RenderHints renderHints() const;
    void setRenderHint(const RenderHint& hint, bool on = true);

public:
    virtual bool begin(std::shared_ptr<Image> image) = 0;
    virtual bool end() = 0;

public:
    virtual void save() = 0;
    virtual void restore() = 0;

public:
    virtual void rotate(double angle) = 0;
    virtual void shear(double hs, double vs) = 0;
    virtual void scale(double sx, double sy) = 0;
    virtual void translate(double dx, double dy) = 0;

public:
    virtual void moveTo(double x, double y) = 0;
    virtual void lineTo(double x, double y) = 0;
    virtual void curveTo(double x1, double y1, double x2, double y2, double x3, double y3) = 0;
    virtual void closeSubPath() = 0;

    virtual void drawText(double x, double y, const std::string& text) = 0;
    virtual void drawText(double x, double y, double w, double h, int flags, const std::string& text) = 0;

    virtual void stroke() = 0;
    virtual void fill() = 0;

public:
    void drawRect(double x, double y, double w, double h);
    void drawLine(double x0, double y0, double x1, double y1);
    void drawEllipse(double x, double y, double w, double h);

protected:
    explicit Painter();

private:
    std::unique_ptr<PainterPrivate> dptr;
};

OPENV_DECLARE_INTERFACE(Painter, "ov.iid.painter")
OPENV_FLAGS_ENABLE_OPERATORS(ov::Painter::RenderHint)
}