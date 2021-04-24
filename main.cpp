
#include "widget.h"
#include "label.h"
#include "container.h"
#include "button.h"
#include "pushable_button.h"
#include "number_picker.h"
#include "fixed_size_label.h"
#include "select.h"
#include <fstream>

int main()
{
    Vector2 screen(400, 400);
    genv::gout.open(screen.x(), screen.y());
    genv::gout << genv::font("LiberationSans-Regular.ttf", 20);

    std::vector<Widget *> ws {
        new NumberPicker({[](Style &s) { s.position = {75, 100}; }}, 0, 100),
        new NumberPicker({[](Style &s) { s.position = {200, 100}; }}, -100, 100),
        new Select({"alma", "korte", "barack", "cseresznye" ,"dinnye", "vanilia", "csoki"}, {[](Style &s) { s.position = {75, 200}; s.size = {250, 30}; }}),
        new Select({"piros", "feher", "zold", "mar", "szombat", "hajnali" ,"negy", "van"}, {[](Style &s) { s.position = {200, 200}; s.size = {250, 30}; }})
    };

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
            for(auto w: ws)
            {
                if (auto* p_np = dynamic_cast<NumberPicker*>(w))
                {
                    f << "NumberPicker(" << p_np->getValue() << ")\n";
                } else if (auto* n_s = dynamic_cast<Select*>(w))
                {
                    f << "Select(" << n_s->getValue() << ")\n";
                }
            }
            f.close();
        }

        bool focus = true;
        for (auto& w: ws)
        {
            w->handle(ev, cursor, focus);
            w->draw();
        }

        genv::gout << genv::refresh;
    }
    for(auto& w: ws) delete w;
    return 0;
}
