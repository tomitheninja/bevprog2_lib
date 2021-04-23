#ifndef STYLES_H
#define STYLES_H

#include "color.h"
#include "vector2.h"

struct StyleProperties
{
    // is relative to the parent?
    bool isRelative = false;
    Vector2 position = {0, 0};
    Vector2 size = {0, 0};
    std::pair<bool, Color> bgColor;

    std::pair<bool, Color> outerBorder;
    std::pair<bool, int> marginLeft;
    std::pair<bool, int> marginRight;
    std::pair<bool, int> marginTop;
    std::pair<bool, int> marginBottom;
};

class Style
{
public:
    virtual void applyOn(StyleProperties &styles) = 0;
};

namespace Styles
{
    // Resize
    class Resize : public Style
    {
    public:
        Resize(const Vector2 &size);
        void applyOn(StyleProperties &styles) override;

    private:
        Vector2 _size;
    };

    // Move
    class Move : public Style
    {
    public:
        Move(const Vector2 &pos);
        void applyOn(StyleProperties &styles) override;

    private:
        Vector2 _pos;
    };

    // Relative position
    class RelativePosition : public Style
    {
    public:
        RelativePosition();
        void applyOn(StyleProperties &styles) override;
    };

    // Absolute position
    class AbsolutePosition : public Style
    {
    public:
        AbsolutePosition();
        void applyOn(StyleProperties &styles) override;
    };

    // Background color
    class BgColor : public Style
    {
    public:
        BgColor(const Color &color);
        void applyOn(StyleProperties &styles) override;
        static BgColor disabled();

    private:
        Color _color;
        bool _enabled;
    };

    // Border color
    class OuterBorder : public Style
    {
    public:
        OuterBorder(const Color &color);
        void applyOn(StyleProperties &styles) override;
        static OuterBorder disabled();

    private:
        Color _color;
        bool _enabled;
    };

    // Margin distance
    class MarginAll : public Style
    {
    public:
        MarginAll(int value);
        void applyOn(StyleProperties &styles) override;
        static MarginAll disabled();

    private:
        int _value;
        bool _enabled;
    };

    // Margin X distance
    class MarginX : public Style
    {
    public:
        MarginX(int value);
        void applyOn(StyleProperties &styles) override;
        static MarginX disabled();

    private:
        int _value;
        bool _enabled;
    };

    // Margin Y distance
    class MarginY : public Style
    {
    public:
        MarginY(int value);
        void applyOn(StyleProperties &styles) override;
        static MarginY disabled();

    private:
        int _value;
        bool _enabled;
    };

    // Margin Top distance
    class MarginTop : public Style
    {
    public:
        MarginTop(int value);
        void applyOn(StyleProperties &styles) override;
        static MarginTop disabled();

    private:
        int _value;
        bool _enabled;
    };

    // Margin Btm distance
    class MarginBtm : public Style
    {
    public:
        MarginBtm(int value);
        void applyOn(StyleProperties &styles) override;
        static MarginBtm disabled();

    private:
        int _value;
        bool _enabled;
    };

    // Margin Left distance
    class MarginLeft : public Style
    {
    public:
        MarginLeft(int value);
        void applyOn(StyleProperties &styles) override;
        static MarginLeft disabled();

    private:
        int _value;
        bool _enabled;
    };

    // Margin Right distance
    class MarginRight : public Style
    {
    public:
        MarginRight(int value);
        void applyOn(StyleProperties &styles) override;
        static MarginRight disabled();

    private:
        int _value;
        bool _enabled;
    };
}

#endif // STYLES_H
