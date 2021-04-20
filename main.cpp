#include "graphics.hpp"
#include "label.h"
#include "number_picker.h"

using namespace genv;

int main()
{
    Vector2 screen(400, 400);
    gout.open(screen.x(), screen.y());
    gout << font("LiberationSans-Regular.ttf", 20);

    NumberPicker n({100, 100});
    n.enableFlags(0b1111);

    n.moveTo({200, 200});

    Vector2 cursor;

    event ev;
    while (gin >> ev && ev.keycode != genv::key_escape)
    {
        screen.clear();

        if (ev.type == genv::ev_mouse && ev.button != genv::btn_wheelup && ev.button != btn_wheelup)
        {
            cursor = {ev.pos_x, ev.pos_y};
        }

        n.handle(ev, cursor);

        n.draw();

        genv::gout << genv::refresh;
    }
    return 0;
}
