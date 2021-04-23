#ifndef WIDGET_H
#define WIDGET_H

#include "styles.h"

class Widget
{
public:
    Widget(const std::vector<Style*> &styles, const std::vector<Widget*> &children);
    Widget(const std::vector<Style*> &styles): Widget(styles, {}) {};
    Widget(const std::vector<Widget*> &children): Widget({}, children) {};
    Widget(): Widget({}, {}) {};
    ~Widget() = default;

    void applyStyle(Style &style);
    bool containsPoint(const Vector2 &point) const;

    int top() const;
    int bottom() const;
    int left() const;
    int right() const;

    int topM() const;
    int bottomM() const;
    int leftM() const;
    int rightM() const;

    Vector2 topLeft() const;
    Vector2 topRight() const;
    Vector2 btmRight() const;
    Vector2 btmLeft() const;

    Vector2 topLeftM() const;
    Vector2 topRightM() const;
    Vector2 btmRightM() const;
    Vector2 btmLeftM() const;

    void draw() const;

    Widget* getParent();
protected:
    void drawBorders() const;
    std::vector<Widget*> _children;

private:
    Widget* _parent = nullptr;
    StyleProperties _s;
};

#endif // WIDGET_H
