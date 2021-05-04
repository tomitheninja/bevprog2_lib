#include "widget.h"
#include <iostream>

Widget *Widget::_focused = nullptr;

Widget::Widget(std::vector<std::shared_ptr<Widget>> children) : _children(std::move(children))
{
    for (auto &p_child : _children)
    {
        p_child->_parent = this;
    }
}

Widget::Widget(Widget &&) = default;

Widget::~Widget() = default;

void Widget::disable()
{
    if (!_self_disabled)
    {
        _self_disabled = true;
        _disabled += 1;
        for (auto &p_child : _children)
            p_child->disable();
    }
}

void Widget::enable()
{
    if (_self_disabled)
    {
        _self_disabled = false;
        _disabled -= 1;
        for (auto &p_child : _children)
            p_child->enable();
    }
}

bool Widget::isEnabled() const
{
    return _disabled == 0;
}

bool Widget::isFocused() const { return Widget::_focused == this; }

void Widget::clearFocus() { Widget::_focused = nullptr; }

void Widget::draw() const
{
    if (!isEnabled())
        return;
    preDraw();
    preChildDraw();
    for (const auto &p_child : _children)
    {
        p_child->draw();
    }
    postChildDraw();
    postDraw();
}

void Widget::preDraw() const { _drawBg(); }
void Widget::preChildDraw() const {}
void Widget::postChildDraw() const {}
void Widget::postDraw() const { _drawBorders(isFocused()); }

void Widget::addEvent(Handler handler)
{
    _events.push_back(handler);
}

bool Widget::handle(const genv::event &evt, const Vector2 cursor, bool &canCaptureFocus)
{
    if (!isEnabled())
        return false;
    if (canCaptureFocus && evt.button == genv::btn_left)
    {
        if (containsPointM(cursor))
        {
            canCaptureFocus = false;
            _focused = this;
        }
        else
        {
            clearFocus();
        }
    }
    for (auto &fn : _events)
    {
        if (fn(evt, cursor, *this))
            return true;
    }
    for (auto &p_child : _children)
    {
        if (p_child->handle(evt, cursor, canCaptureFocus))
            return true;
    }
    return false;
}

bool Widget::handle(const genv::event &evt, const Vector2 cursor)
{
    bool noFocusCapture = false;
    return handle(evt, cursor, noFocusCapture);
}

int Widget::topM() const
{
    auto parentTop = style.isRelative ? _parent->topM() : 0;
    return Renderable::topM() + parentTop;
}

int Widget::leftM() const
{
    return Renderable::leftM() + (style.isRelative ? _parent->leftM() : 0);
}
