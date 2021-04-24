#include "fixed_size_label.h"

FixedSizeLabel::FixedSizeLabel(const std::string &text, const std::vector<Styler> &styles, bool centered): Widget(styles), _text(text), _centered(centered)
{
    addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self) {
        self.style.size.setY(genv::gout.cascent() + genv::gout.cdescent());
        return false;
    });
}

FixedSizeLabel::~FixedSizeLabel() = default;

std::string FixedSizeLabel::getText() const { return _text; }
void FixedSizeLabel::setText(const std::string &text) { _text = text; }

void FixedSizeLabel::preChildDraw() const
{
    style.fgColor.apply();
    std::string ok = "";
    std::string next = "";
    for(auto i = 0; i < _text.length(); i++) {
        next += getText()[i];
        if (genv::gout.twidth(next) <= style.size.x())
        {
            ok = next;
        } else { break; }
    }
    if (_centered) {
        int space = std::max(0, (style.size.x() - genv::gout.twidth(next)) / 2);
        (topLeft() + Vector2{space, 0}).move_to();
    } else {
        topLeft().move_to();
    }
    genv::gout << genv::text(ok);
}
