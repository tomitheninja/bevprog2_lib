#include "graphics.hpp"
#include "label.h"
#include "number_picker.h"
#include "list_box.h"

int main()
{
    Vector2 screen(400, 400);
    genv::gout.open(screen.x(), screen.y());
    genv::gout << genv::font("LiberationSans-Regular.ttf", 20);

    std::vector<Widget *> ws;

    ListBox w1({150, 100}, {"alma", "korte", "barack", "cseresznye", "meggy"});
    w1.setOpenLength(3);

    ListBox w2({150, 25}, {"alma", "korte", "barack", "cseresznye", "meggy"});
    w2.setOpenLength(3);

    NumberPicker w3({150, 200});
    // TODO:
    // Yes, there should be a better border API
    // But unfortunately I have more homeworks to do
    //w3.setBorders(true, true, false, true);
    NumberPicker w4({150, 300}, -25, 25);
    //w4.setBorders(true, true, false, true);



    ws.push_back(&w1);
    ws.push_back(&w2);
    ws.push_back(&w3);
    ws.push_back(&w4);

    Vector2 cursor;
    genv::event ev;
    genv::gin.timer(1000);
    while (genv::gin >> ev && ev.keycode != genv::key_escape)
    {
        screen.clear();

        if (ev.type == genv::ev_mouse && ev.button != genv::btn_wheelup && ev.button != genv::btn_wheelup)
        {
            cursor = {ev.pos_x, ev.pos_y};
            if (ev.button == genv::btn_left)
                Widget::clearFocus();
        }

        bool didntCaptureFocus = true;
        for (auto &pw : ws)
        {
            pw->handle(ev, cursor, didntCaptureFocus);
            pw->draw();
        }

        genv::gout << genv::refresh;
    }
    return 0;
}
