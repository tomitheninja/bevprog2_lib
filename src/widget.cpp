#include "widget.h"
#include <iostream>

Widget *Widget::_focused = nullptr;

Widget::Widget(const std::vector<Styler> &styles, const std::vector<Widget *> &children) : _children(children)
{
    for (auto styler : styles)
    {
        applyStyler(styler);
    }
    for (auto p_child : _children)
    {
        p_child->_parent = this;
    }
}

Widget::~Widget()
{
    for (auto p_child : _children)
        delete p_child;
}

void Widget::applyStyler(Styler sr)
{
    sr(style);
}

bool Widget::isFocused() const { return Widget::_focused == this; }

void Widget::clearFocus() { Widget::_focused = nullptr; }

int Widget::top() const
{
    return style.position.y() + (style.isRelative ? _parent->top() : 0);
}
int Widget::bottom() const { return top() + style.size.y(); }
int Widget::left() const { return style.position.x() + (style.isRelative ? _parent->left() : 0); }
int Widget::right() const { return left() + style.size.x(); }

int Widget::topM() const { return top() - style.marginTop; }
int Widget::bottomM() const { return bottom() + style.marginBottom; }
int Widget::leftM() const { return left() - style.marginLeft; }
int Widget::rightM() const { return right() + style.marginRight; }

Vector2 Widget::topLeft() const { return Vector2{left(), top()}; }
Vector2 Widget::topRight() const { return Vector2{right(), top()}; }
Vector2 Widget::btmLeft() const { return Vector2{left(), bottom()}; }
Vector2 Widget::btmRight() const { return Vector2{right(), bottom()}; }

Vector2 Widget::topLeftM() const { return Vector2{leftM(), topM()}; }
Vector2 Widget::topRightM() const { return Vector2{rightM(), topM()}; }
Vector2 Widget::btmLeftM() const { return Vector2{leftM(), bottomM()}; }
Vector2 Widget::btmRightM() const { return Vector2{rightM(), bottomM()}; }

bool Widget::containsPoint(const Vector2 &point) const
{
    bool y_ok = top() <= point.y() && point.y() <= bottom();
    bool x_ok = left() <= point.x() && point.x() <= right();
    return x_ok && y_ok;
}

bool Widget::containsPointM(const Vector2 &point) const
{
    bool y_ok = topM() <= point.y() && point.y() <= bottomM();
    bool x_ok = leftM() <= point.x() && point.x() <= rightM();
    return x_ok && y_ok;
}

void Widget::draw() const
{
    preDraw();
    preChildDraw();
    for (auto p_child : _children)
    {
        p_child->draw();
    }
    postChildDraw();
    postDraw();
}

void Widget::preDraw() const { _drawBg(); }
void Widget::preChildDraw() const {}
void Widget::postChildDraw() const {}
void Widget::postDraw() const { _drawBorders(); }

void Widget::_drawBg() const
{
    // margin background
    if (style.bgMColor.first)
    {
        style.bgMColor.second.apply();
        topLeftM().draw_rect_to(btmRightM());
    }
    // background
    if (style.bgColor.first)
    {
        style.bgColor.second.apply();
        topLeft().draw_rect(style.size);
    }
}

void Widget::_drawBorders() const
{
    // inner border
    if (style.innerBorderTop.first)
    {
        style.innerBorderTop.second.apply();
        topLeftM().line_to_abs(topRightM());
    }
    if (style.innerBorderBottom.first)
    {
        style.innerBorderBottom.second.apply();
        btmLeftM().line_to_abs(btmRightM());
    }
    if (style.innerBorderLeft.first)
    {
        style.innerBorderLeft.second.apply();
        btmLeftM().line_to_abs(topLeftM());
    }
    if (style.innerBorderRight.first)
    {
        style.innerBorderRight.second.apply();
        btmRightM().line_to_abs(topRightM());
    }

    // outer border
    if (style.outerBorderTop.first)
    {
        style.outerBorderTop.second.apply();
        topLeftM().line_to_abs(topRightM());
    }
    if (style.outerBorderBottom.first)
    {
        style.outerBorderBottom.second.apply();
        btmLeftM().line_to_abs(btmRightM());
    }
    if (style.outerBorderLeft.first)
    {
        style.outerBorderLeft.second.apply();
        btmLeftM().line_to_abs(topLeftM());
    }
    if (style.outerBorderRight.first)
    {
        style.outerBorderRight.second.apply();
        btmRightM().line_to_abs(topRightM());
    }
}

void Widget::addEvent(Handler handler)
{
    _events.push_back(handler);
}

bool Widget::handle(const genv::event &evt, const Vector2 cursor, bool &canCaptureFocus)
{
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
    for (auto &p_child: _children)
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
