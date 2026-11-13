#include "ovPainter.h"
#include "ovEnvironment.h"
#include "ovPluginLoader.h"
#include "ovImage.h"
#include "ovDir.h"
#include <cmath>
#include <stack>

class ov::PainterPrivate
{
    OPENV_DECLARE_PUBLIC(Painter)
private:
    std::stack<Painter::PaintState> states;
    Painter::PaintState state;
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

#ifdef _WIN32
    std::vector<std::string> patterns = {".dll"};
#else 
    std::vector<std::string> patterns = {".so"};
#endif

    auto pathList = Dir::scan(directory, patterns);
    if(pathList.empty()) {
        return {};
    }

    for(const auto& path : pathList) {
        auto loader = PluginLoader::gen(path);
        if(!loader || (!loader->isLoaded() && !loader->load())) {
            continue;
        }

        auto ins = loader->instantiate(OPENV_VGFX_MODULE);
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

const ov::Pen& ov::Painter::pen() const
{
    OPENV_D(const Painter);
    return d->state.pen;
}

void ov::Painter::setPen(const Pen &pen)
{
    OPENV_D(Painter);
    if(d->state.pen != pen) {
        d->state.pen = pen;
        updatePaintState(d->state);
    }
}

const ov::Brush& ov::Painter::brush() const
{
    OPENV_D(const Painter);
    return d->state.brush;
}

void ov::Painter::setBrush(const Brush &brush)
{
    OPENV_D(Painter);
    if(d->state.brush != brush) {
        d->state.brush = brush;
        updatePaintState(d->state);
    } 
}

const ov::Font& ov::Painter::font() const
{
    OPENV_D(const Painter);
    return d->state.font;
}

void ov::Painter::setFont(const Font &font)
{
    OPENV_D(Painter);
    if(d->state.font != font) {
        d->state.font = font;
        updatePaintState(d->state);
    }
}

const ov::Painter::RenderHints& ov::Painter::renderHints() const
{
    OPENV_D(const Painter);
    return d->state.renderHints;
}

void ov::Painter::setRenderHint(const RenderHint &hint, bool on)
{
    OPENV_D(Painter);
    if(on) {
        d->state.renderHints |= hint;
    }else {
        d->state.renderHints &= ~hint;
    }

    updatePaintState(d->state);
}

void ov::Painter::save()
{
    OPENV_D(Painter);
    d->states.push(d->state);
}

void ov::Painter::restore()
{
    OPENV_D(Painter);
    if(!d->states.empty()) {
        d->state = d->states.top();
        d->states.pop();
        updatePaintState(d->state);
    }
}

void ov::Painter::rotate(double angle)
{
    double c = std::cos(angle), s = std::sin(angle);
    transform(c, -s, 0, s, c, 0);
}

void ov::Painter::shear(double hs, double vs)
{
    transform(1, hs, 0, vs, 1, 0);
}

void ov::Painter::scale(double sx, double sy)
{
    transform(sx, 0, 0, 0, sy, 0);
}

void ov::Painter::translate(double dx, double dy)
{
    transform(1, 0, dx, 0, 1, dy);
}

void ov::Painter::transform(double m0, double m1, double m2, double m3, double m4, double m5)
{
    OPENV_D(Painter);

    double a0 = d->state.transform[0];
    double b0 = d->state.transform[1];
    double e0 = d->state.transform[2];
    double c0 = d->state.transform[3];
    double d0 = d->state.transform[4];
    double f0 = d->state.transform[5];

    d->state.transform[0] = m0 * a0 + m1 * c0;
    d->state.transform[1] = m0 * b0 + m1 * d0;
    d->state.transform[2] = m2 * a0 + m5 * c0 + e0;
    d->state.transform[3] = m3 * a0 + m4 * c0;
    d->state.transform[4] = m3 * b0 + m4 * d0;
    d->state.transform[5] = m2 * b0 + m5 * d0 + f0;

    updatePaintState(d->state);
}

void ov::Painter::drawRect(double x, double y, double w, double h)
{
    OPENV_D(Painter);
    bool stroked = (d->state.pen != NoPen);
    bool filled  = (d->state.brush != NoBrush);
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
    if(d->state.pen == NoPen) {
        return;
    }

    moveTo(x0, y0);
    lineTo(x1, y1);
    stroke();
}

void ov::Painter::drawEllipse(double x, double y, double w, double h)
{
    OPENV_D(Painter);
    bool stroked = (d->state.pen != NoPen);
    bool filled  = (d->state.brush != NoBrush);
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


