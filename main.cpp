#include "graphics.hpp"
#include "label.h"

using namespace genv;

int main()
{
    Vector2 screen(400, 400);
    gout.open(screen.x(), screen.y());
    gout << font("LiberationSans-Regular.ttf", 20);


    Label l({100, 100});
    l.addEvent([&](const genv::event& ev, const Vector2& cursor){
        if (l.containsPoint(cursor)) {
            genv::gout
                << genv::move_to(0, 0)
                << genv::color(255, 255, 0)
                << genv::box(50, 50);
        }
        return EventResult::Continue;
    });



    l.setText("lorem ipsum");
    event ev;
    while (gin >> ev && ev.keycode != genv::key_escape)
    {
        screen.clear();

        l.handle(ev, {ev.pos_x, ev.pos_y});

        l.draw();

        genv::gout << genv::refresh;
    }
    return 0;
}
