#include "pushable_button.h"

PushableButton::PushableButton(const std::string &text, const std::vector<Styler> &styles, const std::vector<Styler> &lbStyles) : Button(text, styles, lbStyles)
{
    auto &s = this->style;
    s.outerBorderTop = s.outerBorderBottom = s.outerBorderLeft = s.outerBorderRight = {true, Color{255, 255, 255}};
    s.bgColor.second = Color{32, 32, 32};
    addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self) {
        self.style.bgColor.first = self.containsPoint(cursor);
        return false;
    });
}

PushableButton::~PushableButton() = default;
