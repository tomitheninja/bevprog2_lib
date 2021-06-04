#include "application.h"

#include "checkbox.h"

Application::Application()
{
    _screen = Vector2(640, 480);
    genv::gout.open(_screen.x(), _screen.y());
    genv::gout << genv::font("LiberationSans-Regular.ttf", 20);

    genv::gin.timer(1000 / 8);

    auto x = std::make_shared<TextInput>();
    x->lb->setText("insert text");

    x->style.position = {100, 100};

    _ws.push_back(x);

    auto y = std::make_shared<CheckBox>();
    y->style.position = {200, 200};

    _ws.push_back(y);
}

Application::~Application() = default;

bool Application::tick()
{
    genv::gin >> _ev;

    if (_ev.keycode == genv::key_escape)
    {
        return false;
    }

    _screen.clear();

    if (_ev.type == genv::ev_mouse && _ev.button != genv::btn_wheelup && _ev.button != genv::btn_wheelup)
    {
        _cursor = {_ev.pos_x, _ev.pos_y};
    }

    bool focus = true;
    for (auto &w : _ws)
    {
        if (w->handle(_ev, _cursor, focus))
            break;
    }
    for (auto &w : _ws)
    {
        w->draw();
    }

    Vector2(10, 10).move_to();
    Color(255, 0, 0).apply();

    genv::gout << genv::refresh;

    return true;
}
