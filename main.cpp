
// #include "widget.h"
// #include "label.h"
// #include "container.h"
// #include "button.h"
// #include "pushable_button.h"
// #include "number_picker.h"
// #include "fixed_size_label.h"
// #include "select.h"
#include <fstream>

#include "widget.h"
#include "container.h"
#include "label.h"
#include "fixed_size_label.h"
#include "button.h"
#include "fixed_size_label.h"
#include "pushable_button.h"
#include "number_picker.h"
#include "select.h"
#include "pushable_button.h"

int main()
{
    Vector2 screen(400, 400);
    genv::gout.open(screen.x(), screen.y());
    genv::gout << genv::font("LiberationSans-Regular.ttf", 20);

    std::vector<std::shared_ptr<Widget>> ws{
        std::make_shared<NumberPicker>(-100, 100),
        std::make_shared<Select>(std::vector<std::string> {"foo", "bar", "baz", "quux", "pite"}),
        std::make_shared<PushableButton>("press me")
        // std::make_unique<Select>({"piros", "feher", "zold", "mar", "szombat", "hajnali", "negy", "van"})};
    };

    ws[0]->style.position = {100, 100};
    ws[1]->style.position = {200, 10};

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

        if (ev.keycode == genv::key_space)
        {
            std::ofstream f("log.txt");
            for (const auto &unique_w : ws)
            {
                Widget *w = &(*unique_w);
                if (auto *p_np = dynamic_cast<NumberPicker *>(w))
                {
                    f << "NumberPicker(" << p_np->getValue() << ")\n";
                }
                else if (auto* p_s = dynamic_cast<Select*>(w))
                {
                    f << "Select(" << p_s->getValue() << ")\n";
                }
            }
            f.close();
        }

        bool focus = true;
        for (auto &w : ws)
        {
            w->handle(ev, cursor, focus);
            w->draw();
        }

        genv::gout << genv::refresh;
    }
    return 0;
}
