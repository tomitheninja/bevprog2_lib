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

    event ev;
    while (gin >> ev && ev.keycode != genv::key_escape)
    {
        screen.clear();

        Vector2 cursor = {ev.pos_x, ev.pos_y};

        if (ev.button == genv::btn_left) {
            std::cout << "clicked\n";
            n.handle(ev, cursor);
        }

        n.draw();

        genv::gout << genv::refresh;
    }
    return 0;
}
