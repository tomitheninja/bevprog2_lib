#include "widget.h"
#include <iostream>

Widget *Widget::focused = nullptr;

void Widget::moveTo(const Vector2 &topLeft)
{
    if (_position != topLeft)
    {
        _position = topLeft;
        update();
    }
}

void Widget::setSize(const Vector2 &size)
{
    if (_size != size)
    {
        _size = size;
        update();
    }
}

bool Widget::containsPoint(const Vector2 &cursor) const
{
    const Vector2 &pos = getPosition();
    const Vector2 &size = getSize();
    if (!(size.x() | size.y()))
    {
        std::cerr << "Widget with zero size detected!" << std::endl;
        return false;
    }
    bool x_ok = pos.x() <= cursor.x() && cursor.x() <= pos.x() + size.x();
    bool y_ok = pos.y() <= cursor.y() && cursor.y() <= pos.y() + size.y();
    return x_ok && y_ok;
}

void Widget::update()
{
}

int Widget::addEvent(EventHandler event)
{

    listeners.push_back(event);
    return listeners.size();
}

EventResult Widget::handle(const genv::event &evt, const Vector2 &cursor, bool &canCaptureFocus)
{
    if (canCaptureFocus && evt.button == genv::btn_left && containsPoint(cursor))
    {
        focused = this;
        canCaptureFocus = false;
    }
    for (auto p_listener : listeners)
    {
        p_listener(evt, cursor);
    }
    return EventResult::Unhandled;
}

void Widget::draw() const
{
    Vector2 size = getSize();
    Vector2 topLeft = getPosition();
    Vector2 topRight = topLeft + Vector2{size.x(), 0};
    Vector2 btmRight = topLeft + Vector2{size.x(), size.y()};
    Vector2 btmLeft = topLeft + Vector2{0, size.y()};

    Color(255, 255, isFocused() ? 0 : 255).apply();

    if (flags & 1)
        topLeft.line_to_abs(topRight);
    if (flags & 2)
        topRight.line_to_abs(btmRight);
    if (flags & 4)
        btmRight.line_to_abs(btmLeft);
    if (flags & 8)
        btmLeft.line_to_abs(topLeft);
}
