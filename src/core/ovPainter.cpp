#include "ovPainter.h"
#include "ovEnvironment.h"
#include "ovPluginLoader.h"
#include "ovImage.h"
#include "ovDir.h"
#include <stack>

class ov::PainterPrivate
{
    OPENV_DECLARE_PUBLIC(Painter)
public:
    PainterPrivate() : opacity(0) {}

private:
    Painter::RenderHints renderHints;
    double opacity;
    Brush brush;
    Font font;
    Pen pen;
};

std::shared_ptr<ov::Painter> ov::Painter::gen(const std::string &dir)
{
    std::string directory = Environment::value("OPENV_PAINTER_PLUGIN_DIR");
    if(directory.empty()) {
        directory = Environment::value("OPENV_PLUGIN_DIR");
    }

    if(directory.empty()) {
        directory = dir;
    }

    if(directory.empty()) {
        return {};
    }

    auto pathList = Dir::scan(directory, {".so", ".dll"});
    if(pathList.empty()) {
        return {};
    }

    for(const auto& path : pathList) {
        auto loader = PluginLoader::gen(path);
        if(!loader || (!loader->isLoaded() && !loader->load())) {
            continue;
        }

        auto ins = loader->instantiate();
        if(!ins) {
            continue;
        }

        if(!ins->query<Painter>()) {
            continue;
        }

        return std::static_pointer_cast<Painter>(ins);
    }

    return {};
}

ov::Painter::~Painter()
{
}

ov::Pen ov::Painter::pen() const
{
    OPENV_D(const Painter);
    return d->pen;
}

void ov::Painter::setPen(const Pen &pen)
{
    OPENV_D(Painter);
    d->pen = pen;
}

ov::Brush ov::Painter::brush() const
{
    OPENV_D(const Painter);
    return d->brush;
}

void ov::Painter::setBrush(const Brush &brush)
{
    OPENV_D(Painter);
    d->brush = brush;
}

ov::Font ov::Painter::font() const
{
    OPENV_D(const Painter);
    return d->font;
}

void ov::Painter::setFont(const Font &font)
{
    OPENV_D(Painter);
    d->font = font;
}

double ov::Painter::opacity() const
{
    OPENV_D(const Painter);
    return d->opacity;
}

void ov::Painter::setOpacity(double opacity)
{
    OPENV_D(Painter);
    d->opacity = opacity;
}

ov::Painter::RenderHints ov::Painter::renderHints() const
{
    OPENV_D(const Painter);
    return d->renderHints;
}

void ov::Painter::setRenderHint(const RenderHint &hint, bool on)
{
    OPENV_D(Painter);
    if(on) {
        d->renderHints |= hint;
    }else {
        d->renderHints &= ~hint;
    }
}

void ov::Painter::drawRect(double x, double y, double w, double h)
{
    OPENV_D(Painter);
    bool stroked = (d->pen != NoPen);
    bool filled  = (d->brush != NoBrush);
    if(!stroked && !filled) {
        return;
    }

    moveTo(x, y);
    lineTo(x + w, y);
    lineTo(x + w, y + h);
    lineTo(x, y + h);
    closeSubPath();  

    if(filled) {
        fill();
    }

    if(stroked) {
        stroke();
    }
}

void ov::Painter::drawLine(double x0, double y0, double x1, double y1)
{
    OPENV_D(Painter);
    if(d->pen == NoPen) {
        return;
    }

    moveTo(x0, y0);
    lineTo(x1, y1);
    stroke();
}

void ov::Painter::drawEllipse(double x, double y, double w, double h)
{
    OPENV_D(Painter);
    bool stroked = (d->pen != NoPen);
    bool filled  = (d->brush != NoBrush);
    if(!stroked && !filled) {
        return;
    }

    const double cx = x + w * 0.5;
    const double cy = y + h * 0.5;
    const double rx = w * 0.5;
    const double ry = h * 0.5;

    const double K = 0.5522847498307936;
    const double kx = rx * K;
    const double ky = ry * K;

    moveTo(cx + rx, cy);
    curveTo(cx + rx, cy - ky,  cx + kx, cy - ry,  cx, cy - ry);
    curveTo(cx - kx, cy - ry,  cx - rx, cy - ky,  cx - rx, cy);
    curveTo(cx - rx, cy + ky,  cx - kx, cy + ry,  cx, cy + ry);
    curveTo(cx + kx, cy + ry,  cx + rx, cy + ky,  cx + rx, cy);
    closeSubPath();

    if(filled) {
        fill();
    }

    if(stroked) {
        stroke();
    }
}

ov::Painter::Painter() : dptr(std::make_unique<PainterPrivate>())
{
}