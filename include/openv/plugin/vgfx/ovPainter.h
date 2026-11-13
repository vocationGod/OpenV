#pragma once
#include "openv/plugin/vgfx/ovBrush.h"
#include "openv/plugin/vgfx/ovFont.h"
#include "openv/plugin/vgfx/ovPen.h"
#include "openv/base/ovPlugin.h"
#include "openv/base/ovFlags.h"
#include <memory>
#include <string>
#include <array>
namespace ov {

enum Alignment
{
    AlignTop        = 1 << 0,
    AlignLeft       = 1 << 1,
    AlignRight      = 1 << 2,
    AlignBottom     = 1 << 3,
    AlignHCenter    = 1 << 4,
    AlignVCenter    = 1 << 5,
    AlignCenter     = AlignVCenter | AlignHCenter,
};
using Alignments = Flags<Alignment>;
OPENV_FLAGS_ENABLE_OPERATORS(ov::Alignment)

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

    struct PaintState { RenderHints renderHints; Brush brush; Font font; Pen pen; std::array<double, 6> transform = {}; };
public:
    static std::shared_ptr<ov::Painter> gen(const std::string& dir = "./plugins");

public:
    ~Painter();

public:
    const ov::Pen& pen() const;
    void setPen(const Pen& pen);

    const ov::Brush& brush() const;
    void setBrush(const Brush& brush);

    const ov::Font& font() const;
    void setFont(const Font& font);

    const ov::Painter::RenderHints& renderHints() const;
    void setRenderHint(const RenderHint& hint, bool on = true);

public:
    virtual bool begin(std::shared_ptr<Image> image) = 0;
    virtual bool end() = 0;

public:
    virtual void save();
    virtual void restore();

public:
    virtual void rotate(double angle);
    virtual void shear(double hs, double vs);
    virtual void scale(double sx, double sy);
    virtual void translate(double dx, double dy);

public:
    virtual void moveTo(double x, double y) = 0;
    virtual void lineTo(double x, double y) = 0;
    virtual void curveTo(double x1, double y1, double x2, double y2, double x3, double y3) = 0;
    virtual void closeSubPath() = 0;

    virtual void drawText(double x, double y, const std::string& text) = 0;
    virtual void drawText(double x, double y, double w, double h, Alignments flags, const std::string& text) = 0;

    virtual void stroke() = 0;
    virtual void fill() = 0;

public:
    void drawRect(double x, double y, double w, double h);
    void drawLine(double x0, double y0, double x1, double y1);
    void drawEllipse(double x, double y, double w, double h);

protected:
    virtual void updatePaintState(const PaintState& state) = 0;

protected:
    explicit Painter();

private:
    std::unique_ptr<PainterPrivate> dptr;
};

OPENV_DECLARE_INTERFACE(Painter, "ov.iid.painter")
OPENV_FLAGS_ENABLE_OPERATORS(ov::Painter::RenderHint)
}