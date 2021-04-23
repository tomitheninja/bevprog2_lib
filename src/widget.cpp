#include "widget.h"
#include <iostream>

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
    sr(_s);
}

int Widget::top() const
{
    return _s.position.y() + (_s.isRelative ? _parent->top() : 0);
}
int Widget::bottom() const { return top() + _s.size.y(); }
int Widget::left() const { return _s.position.x() + (_s.isRelative ? _parent->left() : 0); }
int Widget::right() const { return left() + _s.size.x(); }

int Widget::topM() const { return top() - _s.marginTop; }
int Widget::bottomM() const { return bottom() + _s.marginBottom; }
int Widget::leftM() const { return left() - _s.marginLeft; }
int Widget::rightM() const { return right() + _s.marginRight; }

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
    bool y_ok = topM() <= point.y() && point.y() <= bottomM();
    bool x_ok = leftM() <= point.x() && point.x() <= rightM();
    return x_ok && y_ok;
}

void Widget::draw() const
{
    // background
    if (_s.bgMColor.first)
    {
        _s.bgMColor.second.apply();
        topLeftM().draw_rect_to(btmRightM());
    }
    if (_s.bgColor.first)
    {
        _s.bgColor.second.apply();
        topLeft().draw_rect(_s.size);
    }
    drawBorders();

    // preChildrenDraw()

    // children
    for (auto p_child : _children)
    {
        p_child->draw();
    }

    // postChildrenDraw()
}

void Widget::drawBorders() const
{
    // inner border
    if (_s.innerBorderTop.first)
    {
        _s.innerBorderTop.second.apply();
        topLeftM().line_to_abs(topRightM());
    }
    if (_s.innerBorderBottom.first)
    {
        _s.innerBorderBottom.second.apply();
        btmLeftM().line_to_abs(btmRightM());
    }
    if (_s.innerBorderLeft.first)
    {
        _s.innerBorderLeft.second.apply();
        btmLeftM().line_to_abs(topLeftM());
    }
    if (_s.innerBorderRight.first)
    {
        _s.innerBorderRight.second.apply();
        btmRightM().line_to_abs(topRightM());
    }

    // outer border
    if (_s.outerBorderTop.first)
    {
        _s.outerBorderTop.second.apply();
        topLeftM().line_to_abs(topRightM());
    }
    if (_s.outerBorderBottom.first)
    {
        _s.outerBorderBottom.second.apply();
        btmLeftM().line_to_abs(btmRightM());
    }
    if (_s.outerBorderLeft.first)
    {
        _s.outerBorderLeft.second.apply();
        btmLeftM().line_to_abs(topLeftM());
    }
    if (_s.outerBorderRight.first)
    {
        _s.outerBorderRight.second.apply();
        btmRightM().line_to_abs(topRightM());
    }
}
