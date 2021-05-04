#include "button.h"

Button::Button(const std::string &text) : Container({std::make_shared<Label>(text)})
{
    lb = std::static_pointer_cast<Label>(_children[0]);
    lb->style.isRelative = true;

    // change the background color on hover
    addEvent([](const genv::event &evt, const Vector2 &cursor, Widget &self) {
        self.style.bgMColor.first = self.containsPointM(cursor);
        return false;
    });
}

Button::~Button() = default;

std::string Button::getText() const { return lb->getText(); }
void Button::setText(const std::string &newText) { lb->setText(newText); };
