#include "label.h"

void Label::update()
{
    int text_height = genv::gout.cascent() + genv::gout.cdescent();
    int text_width = genv::gout.twidth(getText());
    setSize({text_width, text_height});
}

void Label::draw() const
{
    getPosition().move_to();
    getColor().apply();
    genv::gout << genv::text(getText());
}
