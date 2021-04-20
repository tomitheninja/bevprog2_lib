#include "number_picker.h"

NumberPicker::NumberPicker(const Vector2 &position) : Widget(position)
{
    _btnIncr.setText("+");
    _btnIncr.addEvent([&](const genv::event &ev, const Vector2 &cursor) {
        if (ev.button == genv::btn_left && _btnIncr.containsPoint(cursor))
        {
            setValue(getValue() + 1);
            return EventResult::Continue;
        }
        return EventResult::Unhandled;
    });

    _btnDecr.setText("-");
    _btnDecr.addEvent([&](const genv::event &ev, const Vector2 &cursor) {
        if (ev.button == genv::btn_left && _btnDecr.containsPoint(cursor))
        {
            setValue(getValue() - 1);
            return EventResult::Continue;
        }
        return EventResult::Unhandled;
    });

    addEvent([&](const genv::event &ev, const Vector2 &cursor) {
        if (isFocused())
        {
            if (ev.keycode == genv::key_pgup)
            {
                setValue(getValue() + 10);
                return EventResult::Handled;
            }
            if (ev.keycode == genv::key_pgdn)
            {
                setValue(getValue() - 10);
                return EventResult::Handled;
            }
        }
        return EventResult::Unhandled;
    });

    update();
}

void NumberPicker::setValue(int value)
{
    _value = value;
    update();
}

void NumberPicker::update()
{
    _lbValue.setText(std::to_string(_value));
    _lbValue.update();

    _btnIncr.update();
    _btnDecr.update();

    setSize({100, _lbValue.getSize().y() + _btnIncr.getSize().y()});
}

void NumberPicker::draw() const
{
    Widget::draw();
    _lbValue.draw();
    _btnIncr.draw();
    _btnDecr.draw();
}

void NumberPicker::setSize(const Vector2 &size)
{
    Widget::setSize(size);

    Vector2 position = getPosition();
    auto halfHeight = size.y() / 2;
    auto fourthWidth = size.x() / 3;

    Vector2 btnSize = {fourthWidth, halfHeight};

    Vector2 pos = getPosition() + Vector2{10, 0};

    _btnIncr.moveTo(pos);
    _btnIncr.setSize(btnSize);
    _btnIncr.update();

    _btnDecr.moveTo(pos + Vector2{0, halfHeight});
    _btnDecr.setSize(btnSize);
    _btnDecr.update();

    _lbValue.moveTo(pos + Vector2{fourthWidth, size.y() / 4});
    _lbValue.update();
}

EventResult NumberPicker::handle(const genv::event &ev, const Vector2 &cursor, bool &canCaptureFocus)
{
    auto r0 = Widget::handle(ev, cursor, canCaptureFocus);
    if (r0 == EventResult::Handled)
        return EventResult::Handled;
    auto r1 = _lbValue.handle(ev, cursor);
    if (r1 == EventResult::Handled)
        return EventResult::Handled;
    auto r2 = _btnIncr.handle(ev, cursor);
    if (r2 == EventResult::Handled)
        return EventResult::Handled;
    auto r3 = _btnDecr.handle(ev, cursor);
    if (r3 == EventResult::Handled)
        return EventResult::Handled;

    return EventResult::Continue;
}
