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

    Vector2 lbSize = {size.x(), size.y() / 2};
    Vector2 btnSize = {size.x() / 2, size.y() / 2};

    _lbValue.setSize(lbSize);
    _btnIncr.setSize(btnSize);
    _btnDecr.setSize(btnSize);

    Vector2 pos = getPosition();

    _lbValue.moveTo(pos);
    _btnIncr.moveTo(pos + Vector2{0, btnSize.y()});
    _btnDecr.moveTo(_btnIncr.getPosition() + Vector2{btnSize.x(), 0});
}

EventResult NumberPicker::handle(const genv::event &ev, const Vector2 &cursor)
{
    Widget::handle(ev, cursor);
    _lbValue.handle(ev, cursor);
    _btnIncr.handle(ev, cursor);
    _btnDecr.handle(ev, cursor);
}
