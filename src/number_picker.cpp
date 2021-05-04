#include "number_picker.h"
#include <algorithm>

NumberPicker::NumberPicker(int lower, int upper) : Container({
                                                       std::make_shared<Label>("0"),
                                                       std::make_shared<Button>("-"),
                                                       std::make_shared<Button>("+"),
                                                   }),
                                                   _lower(lower), _upper(upper)
{
    style.marginRight = 5;
    style.outerBorderTop = style.outerBorderBottom = style.outerBorderLeft = style.outerBorderRight = {true, Color{255, 255, 255}};

    lb = static_cast<Label *>(&(*_children[0]));
    btnIncr = static_cast<Button *>(&(*_children[1]));
    btnDecr = static_cast<Button *>(&(*_children[2]));

    btnIncr->style.isRelative = true;
    lb->style.isRelative = true;
    btnDecr->style.isRelative = true;
    lb->style.position = {10, 10};
    btnDecr->style.position = {68, 0};
    btnIncr->style.position = {70, 20};

    // Increment on click
    btnIncr->addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self) {
        if (evt.button == genv::btn_left && self.containsPointM(cursor))
        {
            setValue(getValue() + 1);
            return true;
        }
        return false;
    });

    // Decrement on click
    btnDecr->addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self) {
        if (evt.button == genv::btn_left && self.containsPointM(cursor))
        {
            setValue(getValue() - 1);
            return true;
        }
        return false;
    });

    // Keyboard control
    addEvent([&](const genv::event &evt, const Vector2 &cursor, Widget &self) {
        lb->setText(std::to_string(_value));
        if (isFocused())
        {
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
