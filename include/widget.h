#ifndef WIDGET_H
#define WIDGET_H

#include "styles.h"

class Widget
{
public:
    Widget(const std::vector<Styler> &styles = {}, const std::vector<Widget *> &children = {});
    ~Widget();

    void applyStyler(Styler sr);

    bool containsPoint(const Vector2 &point) const;

    // Single position values
    int top() const;
    int bottom() const;
    int left() const;
    int right() const;

    // Single position values (including margin)
    int topM() const;
    int bottomM() const;
    int leftM() const;
    int rightM() const;

    // Edges of the widget
    Vector2 topLeft() const;
    Vector2 topRight() const;
    Vector2 btmRight() const;
    Vector2 btmLeft() const;

    // Edges of the widget (including margin)
    Vector2 topLeftM() const;
    Vector2 topRightM() const;
    Vector2 btmRightM() const;
    Vector2 btmLeftM() const;

    void draw() const;

    Widget *getParent();

protected:
    void drawBorders() const; // Call be called any time to fix the borders
    Style _s;
    std::vector<Widget *> _children; // not owned!

private:
    Widget *_parent = nullptr;
};

#endif // WIDGET_H
