#include "widget.h"
#include <iostream>

Widget::Widget(const std::vector<Style*> &styles, const std::vector<Widget*> &children): _children(children) {
    for (auto p_style: styles) {
        applyStyle(*p_style);
    }
    for (auto p_child: _children) {
        p_child->_parent = this;
    }
}

int Widget::top() const { return _s.position.y() + (_s.isRelative ? _parent->top() : 0); }
int Widget::bottom() const { return top() + _s.size.y(); }
int Widget::left() const { return _s.position.x() + (_s.isRelative ? _parent->left() : 0); }
int Widget::right() const { return left() + _s.size.x(); }

int Widget::topM() const { return top() - (_s.marginTop.first ? _s.marginTop.second : 0); }
int Widget::bottomM() const { return bottom() + (_s.marginBottom.first ? _s.marginBottom.second : 0); }
int Widget::leftM() const { return left() - (_s.marginLeft.first ? _s.marginLeft.second : 0); }
int Widget::rightM() const { return right() + (_s.marginRight.first ? _s.marginRight.second : 0); }

Vector2 Widget::topLeft() const { return Vector2{left(), top()}; }
Vector2 Widget::topRight() const { return Vector2{right(), top()}; }
Vector2 Widget::btmLeft() const { return Vector2{left(), bottom()}; }
Vector2 Widget::btmRight() const { return Vector2{right(), bottom()}; }

Vector2 Widget::topLeftM() const { return Vector2{leftM(), topM()}; }
Vector2 Widget::topRightM() const { return Vector2{rightM(), topM()}; }
Vector2 Widget::btmLeftM() const { return Vector2{leftM(), bottomM()}; }
Vector2 Widget::btmRightM() const { return Vector2{rightM(), bottomM()}; }

void Widget::applyStyle(Style &style)
{
    style.applyOn(_s);
}

bool Widget::containsPoint(const Vector2 &point) const
{
    bool y_ok = top() <= point.y() && point.y() <= bottom();
    bool x_ok = left() <= point.x() && point.x() <= right();
    return y_ok && x_ok;
}

void Widget::draw() const
{
    // background
    if (_s.bgColor.first)
    {
        _s.bgColor.second.apply();
        topLeft().draw_rect(_s.size);
    }
    // children
    for (auto p_child: _children) {
        p_child->draw();
    }
    drawBorders();
}

void Widget::drawBorders() const
{
    if (_s.outerBorder.first)
    {
        _s.outerBorder.second.apply();
        if (_s.marginTop.first)
            topLeftM().line_to_abs(topRightM());
        if (_s.marginBottom.first)
            btmLeftM().line_to_abs(btmRightM());
        if (_s.marginLeft.first)
            btmLeftM().line_to_abs(topLeftM());
        if (_s.marginRight.first)
            btmRightM().line_to_abs(topRightM());
    }
}
