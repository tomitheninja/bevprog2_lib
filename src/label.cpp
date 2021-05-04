#include "label.h"

Label::Label(const std::string &text) : Widget()
{
    setText(text);
    // update size, so it constains the text
    addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self) {
        self.style.size.setX(genv::gout.twidth(getText()));
        self.style.size.setY(genv::gout.cascent() + genv::gout.cdescent());
        return false;
    });
}

Label::~Label() = default;

std::string Label::getText() const { return _text; }

void Label::setText(const std::string &text)
{
    _text = text;
}

void Label::preChildDraw() const
{
    topLeft().move_to();
    style.fgColor.apply();
    genv::gout << genv::text(getText());
}
