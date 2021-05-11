#include "cell.h"


Cell::Cell(Vector2 size, Vector2 position) : Widget(std::vector<std::shared_ptr<Widget>>())
{
    style.position = position;
    style.size = size;
    Color border = {50, 50, 50};
    style.innerBorderLeft = {true, border};
    style.innerBorderRight = {true, border};
    style.innerBorderTop = {true, border};
    style.innerBorderBottom = {true, border};
}

Cell::~Cell() = default;

int Cell::getState() const
{
    return state;
}

bool Cell::isEmpty() const
{
    return getState() == 0;
}

void Cell::postChildDraw() const
{
    Color(210, 175, 114).apply();
    topLeft().draw_rect(style.size);
    topLeft().move_to();
    switch (state)
    {
    case 1:
        Color(0, 0, 0).apply();
        genv::gout << genv::text("X");
        break;
    case 2:
        Color(255, 255, 255).apply();
        genv::gout << genv::text("O");
        break;
    }
}

void Cell::setPlayer(bool isWhite)
{
    state = isWhite ? 2 : 1;
}
