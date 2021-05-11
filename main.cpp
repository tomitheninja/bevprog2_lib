
// #include "widget.h"
// #include "label.h"
// #include "container.h"
// #include "button.h"
// #include "pushable_button.h"
// #include "number_picker.h"
// #include "fixed_size_label.h"
// #include "select.h"
// #include <fstream>

/*#include "widget.h"
#include "container.h"
#include "label.h"
#include "fixed_size_label.h"
#include "button.h"
#include "fixed_size_label.h"
#include "pushable_button.h"
#include "number_picker.h"
#include "select.h"
#include "pushable_button.h"*/
#include "cell.h"

int main()
{
    Vector2 screen(15*32 + 1, 15*32 + 1);
    genv::gout.open(screen.x(), screen.y());
    genv::gout << genv::font("LiberationSans-Regular.ttf", 20);

    Vector2 cursor;
    genv::event ev;
    genv::gin.timer(1000 / 64);

    std::vector<Cell> cells;

    bool isWhiteNext = true;

    cells.reserve(15 *15);
    for(int y = 0; y < 15; y++)
    {
        for (int x = 0; x < 15; x++)
        {
            cells.push_back(Cell({32, 32}, {32*x, 32*y}));
            auto& c = cells[cells.size() - 1];
            c.addEvent([&](const genv::event& ev, const Vector2& cursor, Widget& self) {
                if (c.isEmpty() && self.containsPoint(cursor) && ev.button == genv::btn_left)
                {
                    c.setPlayer(isWhiteNext);
                    isWhiteNext = !isWhiteNext;
                    return true;
                }
                return false;
            });

        }
    }

    while (genv::gin >> ev)
    {
        screen.clear();

        if (ev.type == genv::ev_mouse && ev.button != genv::btn_wheelup && ev.button != genv::btn_wheelup)
        {
            cursor = {ev.pos_x, ev.pos_y};
        }

        for(auto& c: cells)
        {
            c.handle(ev, cursor);
            c.draw();
        }

        genv::gout << genv::refresh;
    }

    return 0;
}
