#ifndef CELL_H
#define CELL_H

#include <widget.h>

/*    enum CellState
    {
        empty = 0,
        black,
        white
    };*/

class Cell : public Widget
{
public:

    Cell(Vector2 size, Vector2 position);
    virtual ~Cell();
    int getState() const;
    void setPlayer(bool isWhite);
    bool isEmpty() const;

protected:
    int state = 0;
    void postChildDraw() const;

private:
};

#endif // CELL_H
