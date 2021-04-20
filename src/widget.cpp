#include "widget.h"
#include <iostream>

Widget::~Widget()
{
    for (auto p_listener : listeners)
    {
        delete p_listener;
    }
}

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

    listeners.push_back(&event);
    return listeners.size();
}

EventResult Widget::handle(const genv::event &evt, const Vector2 &cursor)
{
    for (auto p_listener : listeners)
    {
        if (p_listener)
            (*p_listener)(evt, cursor);
    }
    return EventResult::Unhandled;
}
