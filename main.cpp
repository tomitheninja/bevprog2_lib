
#include "widget.h"

int main()
{
    Vector2 screen(400, 400);
    genv::gout.open(screen.x(), screen.y());
    genv::gout << genv::font("LiberationSans-Regular.ttf", 20);

    Widget w({
                 [](Style &s) {
                     s.position = {100, 100};
                     s.isRelative = false;
                     s.bgColor = {true, Color{32, 32, 32}};
                     s.bgMColor = {true, Color{16, 16, 16}};
                     s.size = {100, 100};
                     s.marginLeft = s.marginRight = s.marginTop = s.marginBottom = 10;
                     s.outerBorderLeft = s.outerBorderRight = {true, Color{255, 255, 255}};
                 },
             },
             {new Widget({[](Style &s) {
                 s.isRelative = true;
                 s.position = {25, 25};
                 s.size = {25, 25};
                 s.bgColor = {true, {255, 255, 255}};
             }})});

    w.addEvent([](const genv::event &evt, const Vector2 &cursor, Widget &self) {
        self.applyStyler([&](Style &s) {
            s.bgColor.first = self.containsPoint(cursor);
            s.outerBorderTop.second = s.outerBorderRight.second = s.outerBorderBottom.second = s.outerBorderLeft.second = Color{255, 255, self.isFocused() ? 0 : 255};
        });
        return false;
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

        bool focus = true;
        w.handle(ev, cursor, focus);
        w.draw();

        genv::gout << genv::refresh;
    }
    return 0;
}
