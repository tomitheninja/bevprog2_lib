#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "vector2.h"
#include "styles.h"

// This interface was created, because the Widget class became too large to handle.
// So some simpler behaviors were factored out from it into this class
class Renderable
{
public:
    Renderable();
    virtual ~Renderable();

    Style style;

    // Apply a styler function
    void applyStyler(Styler sr);
    // Apply multiple styler functions
    void applyStylers(const std::vector<Styler> &srs);

    // Check if the point is strictly inside the object's render area
    virtual bool containsPoint(const Vector2 &point) const;
    // Check if the point is inside the object's render area (including the margin)
    virtual bool containsPointM(const Vector2 &point) const;

    // Single position values
    virtual int top() const;
    virtual int bottom() const;
    virtual int left() const;
    virtual int right() const;

    // Single position values (including margin)
    virtual int topM() const;
    virtual int bottomM() const;
    virtual int leftM() const;
    virtual int rightM() const;

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

protected:
    // draws a rectangle, which is colored based on the style
    void _drawBg() const;
    // draws all enabled borders, and also focus border
    void _drawBorders(bool isFocused) const; // Call be called any time to fix the borders
private:
};

#endif // RENDERABLE_H
