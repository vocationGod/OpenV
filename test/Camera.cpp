#include "openv/openv.hpp"

using namespace ov;
int main(int argc, char* argv[])
{
    auto camera = ov::Camera::gen(.....);

    auto window = ov::Window::gen(.....);

    while(true) {
        auto image = camera->acquire();
        if(!image || image->empty()) {
            continue;
        }

        Painter painter;
        painter->begin(image);
        painter->setPen(Pen(ov::red, 2));
        painter->drawRect(10, 10, 40, 60);
        painter->drawText(10, 10, 40, 60, ov::AlignCenter, "你好世界");
        painter->end();

        window->submit(image);
    }
}