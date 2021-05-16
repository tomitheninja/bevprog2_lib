#ifndef APPLICATION_H
#define APPLICATION_H

#include "cell.h"

class Application
{
public:
    Application();
    virtual ~Application();
    bool tick();
    int checkWinner();
    const int NCELLS = 15;

protected:
private:
    void _initCells();
    Vector2 _screen;
    genv::event _ev;
    std::vector<Cell> _cells;
    Vector2 _cursor;
    bool _isWhiteNext = true;
    int winner = 0;
};

#endif // APPLICATION_H
