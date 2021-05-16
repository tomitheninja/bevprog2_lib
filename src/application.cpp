#include "application.h"

Application::Application()
{
    _screen = Vector2(NCELLS * 32 + 1, NCELLS * 32 + 1);
    genv::gout.open(_screen.x(), _screen.y());
    genv::gout << genv::font("LiberationSans-Regular.ttf", 20);

    genv::gin.timer(1000 / 10);

    _initCells();

    genv::gout.showmouse(false);
}

Application::~Application()
{
    //dtor
}

void Application::_initCells()
{
    _cells.clear();
    _cells.reserve(NCELLS * NCELLS);
    for (int y = 0; y < NCELLS; y++)
    {
        for (int x = 0; x < 15; x++)
        {
            _cells.push_back(Cell({32, 32}, {32 * x, 32 * y}));
            int i = _cells.size() - 1;
            _cells[i].addEvent([&, i](const genv::event &ev, const Vector2 &cursor, Widget &self)
                               {
                                   if (winner != 0)
                                       return false;
                                   auto &c = _cells[i];
                                   if (c.isEmpty() && self.containsPoint(cursor) && ev.button == genv::btn_left)
                                   {
                                       c.setPlayer(_isWhiteNext);
                                       _isWhiteNext = !_isWhiteNext;
                                       winner = checkWinner();
                                       return true; // handled the event
                                   }
                                   return false;
                               });
        }
    }
}

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

    for (auto &c : _cells)
    {
        if (c.handle(_ev, _cursor))
            break;
    }
    for (auto &c : _cells)
    {
        c.draw();
    }

    Vector2(10, 10).move_to();
    Color(255, 0, 0).apply();

    switch (winner)
    {
        // TODO: show game over with .kep files containing chickens
    case 1:
        genv::gout << genv::text("Black won");
        break;
    case 2:
        genv::gout << genv::text("White won");
        break;
    case -1:
        genv::gout << genv::text("draw");
        break;
    case 0:
        (_cursor - Vector2(10, 10)).move_to();
        if (_isWhiteNext)
        {
            Color(255, 255, 255).apply();
            genv::gout << genv::text("o");
        }
        else
        {
            Color(0, 0, 0).apply();
            genv::gout << genv::text("x");
        }
        break;
    }

    genv::gout << genv::refresh;

    return true;
}

int Application::checkWinner()
{
    bool hasEmpty = false;
    for (int row = 0; row < NCELLS; row++)
    {
        for (int col = 0; col < NCELLS; col++)
        {
            hasEmpty = hasEmpty || _cells[row * NCELLS + col].getState() == 0;

            std::vector<int> prevValues{0, 0, 0, 0};
            std::vector<bool> canWins{true, true, true, true};
            for (int i = 0; i < 5; i++)
            {
                std::vector<int> states{
                    // row:
                    col >= 4 ? _cells[row * NCELLS + col - i].getState() : 0,
                    // col: (the trick is that row and col are swapped)
                    col >= 4 ? _cells[col * NCELLS + row - i * NCELLS].getState() : 0,
                    // cross1:
                    row >= 4 && col >= 4 ? _cells[row * NCELLS + col - (NCELLS + 1) * i].getState() : 0,
                    // cross2:
                    row <= NCELLS - 5 && col <= NCELLS - 5 ? _cells[row * NCELLS + col - (NCELLS - 1) * i].getState() : 0,
                };

                // set canWin[j] to false, if the chain broke
                for (int j = 0; j < 4; j++)
                {
                    int state = states[j];
                    bool isEmpty = state == 0;
                    bool isChanged = prevValues[j] != state;
                    bool isFirst = i == 0;
                    if ((!isFirst && isChanged) || isEmpty)
                    {
                        canWins[j] = false;
                    }
                    prevValues[j] = state;
                }
            }
            for (int j = 0; j < 4; j++)
            {
                bool won = canWins[j];
                auto color = prevValues[j];
                if (won)
                    return color;
            }
        }
    }
    return !hasEmpty ? -1 : 0;
}
