#include "number_picker.h"
#include <algorithm>

NumberPicker::NumberPicker(const std::vector<Styler> &styles, int lower, int upper) : Container(styles, {new Label("0", {[](Style &s) { s.isRelative = true; s.position = {10 , 10}; }}),
                                                                                   new Button("-", {[](Style &s) { s.isRelative = true; s.position = {70, 20}; }}),
                                                                                   new Button("+", {[](Style &s) { s.isRelative = true; s.position = {68, 0}; }}),
                                                                                   }),
                                                                                   _lower(lower), _upper(upper)
{
    style.marginRight = 5;
    style.outerBorderTop = style.outerBorderBottom = style.outerBorderLeft = style.outerBorderRight = {true, Color{255, 255, 255}};
    lb = reinterpret_cast<Label *>(_children[0]);
    btnIncr = reinterpret_cast<Button *>(_children[2]);
    btnDecr = reinterpret_cast<Button *>(_children[1]);

    btnIncr->addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self) {
        if (evt.button == genv::btn_left && self.containsPoint(cursor))
        {
            setValue(getValue() + 1);
            return true;
        }
        return false;
    });
    btnDecr->addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self) {
        if (evt.button == genv::btn_left && self.containsPoint(cursor))
        {
            setValue(getValue() - 1);
            return true;
        }
        return false;
    });
    addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self) {
        lb->setText(std::to_string(_value));
        if (isFocused()) {
            switch (evt.keycode)
            {
            case genv::key_up:
                setValue(getValue() + 1);
                return true;
            case genv::key_pgup:
                setValue(getValue() + 10);
                return true;
            case genv::key_down:
                setValue(getValue() - 1);
                return true;
            case genv::key_pgdn:
                setValue(getValue() - 10);
                return true;
            }
        }
        return false;
    });
}

void NumberPicker::setValue(int value)
{
    _value = std::max(_lower, std::min(value, _upper));
}

int NumberPicker::getValue()
{
    return _value;
}
