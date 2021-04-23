
#include "widget.h"
#include "label.h"
#include "container.h"

int main()
{
    Vector2 screen(400, 400);
    genv::gout.open(screen.x(), screen.y());
    genv::gout << genv::font("LiberationSans-Regular.ttf", 20);

    Container w({
                    [](Style &s) {
                        s.position = {100, 100};
                        s.isRelative = false;
                        //    s.bgColor = {true, Color{32, 32, 32}};
                        s.bgMColor = {false, Color{32, 32, 32}};
                        s.innerBorderLeft = s.innerBorderRight = {true, Color{255, 255, 255}};
                        s.innerBorderTop = s.innerBorderBottom = {true, Color{255, 255, 255}};
                    },
                },
                {new Label("lorem ipsum", {[](Style &s) {
                               s.isRelative = true;
                               s.position = {5, 5};
                               s.marginRight = s.marginBottom = 5;
                               s.marginLeft = s.marginTop = 10;
                        }})
                });

     w.addEvent([](const genv::event &evt, const Vector2 &cursor, Widget &self) {
        self.style.bgMColor.first = self.containsPointM(cursor);
      /*  self.style.outerBorderTop.second =
            self.style.outerBorderRight.second =
                self.style.outerBorderBottom.second =
                    self.style.outerBorderLeft.second =
                        Color{255, 255, self.isFocused() ? 0 : 255};*/
        return false;
    });

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
