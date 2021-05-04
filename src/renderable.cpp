#include "renderable.h"

Renderable::Renderable()
{
    //ctor
}

Renderable::~Renderable() = default;

bool Renderable::containsPoint(const Vector2 &point) const
{
    bool y_ok = top() <= point.y() && point.y() <= bottom();
    bool x_ok = left() <= point.x() && point.x() <= right();
    return x_ok && y_ok;
}

bool Renderable::containsPointM(const Vector2 &point) const
{
    bool y_ok = topM() <= point.y() && point.y() <= bottomM();
    bool x_ok = leftM() <= point.x() && point.x() <= rightM();
    return x_ok && y_ok;
}

void Renderable::applyStyler(Styler sr)
{
    sr(style);
}

void Renderable::applyStylers(const std::vector<Styler> &srs)
{
    for (auto &sr : srs)
    {
        sr(style);
    }
}

void Renderable::_drawBg() const
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

void Renderable::_drawBorders(bool isFocused) const
{
    // border around the object
    if (style.innerBorderTop.first)
    {
        style.innerBorderTop.second.apply();
        topLeft().line_to_abs(topRight());
    }
    if (style.innerBorderBottom.first)
    {
        style.innerBorderBottom.second.apply();
        btmLeft().line_to_abs(btmRight());
    }
    if (style.innerBorderLeft.first)
    {
        style.innerBorderLeft.second.apply();
        btmLeft().line_to_abs(topLeft());
    }
    if (style.innerBorderRight.first)
    {
        style.innerBorderRight.second.apply();
        btmRight().line_to_abs(topRight());
    }
    // border around the margin
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

    // border when in focus
    if (isFocused)
    {
        Color(255, 255, 32).apply();
        topLeftM().line_to_abs(topRightM());
        btmLeftM().line_to_abs(btmRightM());
        btmLeftM().line_to_abs(topLeftM());
        btmRightM().line_to_abs(topRightM());
    }
}

int Renderable::top() const { return topM() + style.marginTop; }
int Renderable::bottom() const { return top() + style.size.y(); }
int Renderable::left() const { return leftM() + style.marginLeft; }
int Renderable::right() const { return left() + style.size.x(); }

int Renderable::topM() const { return style.position.y(); }
int Renderable::bottomM() const { return bottom() + style.marginBottom; }
int Renderable::leftM() const { return style.position.x(); }
int Renderable::rightM() const { return right() + style.marginRight; }

Vector2 Renderable::topLeft() const { return Vector2{left(), top()}; }
Vector2 Renderable::topRight() const { return Vector2{right(), top()}; }
Vector2 Renderable::btmLeft() const { return Vector2{left(), bottom()}; }
Vector2 Renderable::btmRight() const { return Vector2{right(), bottom()}; }

Vector2 Renderable::topLeftM() const { return Vector2{leftM(), topM()}; }
Vector2 Renderable::topRightM() const { return Vector2{rightM(), topM()}; }
Vector2 Renderable::btmLeftM() const { return Vector2{leftM(), bottomM()}; }
Vector2 Renderable::btmRightM() const { return Vector2{rightM(), bottomM()}; }
