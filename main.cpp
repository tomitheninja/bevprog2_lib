
#include "widget.h"


int main()
{
    Vector2 screen(400, 400);
    genv::gout.open(screen.x(), screen.y());
    genv::gout << genv::font("LiberationSans-Regular.ttf", 20);

    auto s = Styles::MarginLeft::disabled();
    Widget w({
             new Styles::Move({100, 100}),
             new Styles::BgColor({32, 32, 32}),
             new Styles::Resize({100, 100}),
             new Styles::MarginAll(10),
             new Styles::OuterBorder({255, 255, 255}),
             &s
    }, {
        new Widget({ new Styles::RelativePosition(), new Styles::Move({10, 10}), new Styles::Resize({50, 50}), new Styles::BgColor({64, 64, 64}) })
    });

    Vector2 cursor;
    genv::event ev;
    while (genv::gin >> ev && ev.keycode != genv::key_escape)
    {
        screen.clear();

        if (ev.type == genv::ev_mouse && ev.button != genv::btn_wheelup && ev.button != genv::btn_wheelup)
        {
            cursor = {ev.pos_x, ev.pos_y};
        }

        w.draw();

        genv::gout << genv::refresh;
    }

    return 0;
}
