
#include "widget.h"
#include "label.h"
#include "container.h"
#include "button.h"

int main()
{
    Vector2 screen(400, 400);
    genv::gout.open(screen.x(), screen.y());
    genv::gout << genv::font("LiberationSans-Regular.ttf", 20);

    Button w("lorem ipsum", {[](Style &s) { s.position = {100, 100}; }});

    Vector2 cursor;
    genv::event ev;
    genv::gin.timer(1000 / 64);
    while (genv::gin >> ev && ev.keycode != genv::key_escape)
    {
        screen.clear();

        if (ev.type == genv::ev_mouse && ev.button != genv::btn_wheelup && ev.button != genv::btn_wheelup)
        {
            cursor = {ev.pos_x, ev.pos_y};
        }

        bool focus = true;
        w.handle(ev, cursor, focus);
        w.draw();

        genv::gout << genv::refresh;
    }
    return 0;
}
