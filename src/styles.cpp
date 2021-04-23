#include "styles.h"

Styles::Move::Move(const Vector2 &pos) : _pos(pos) {}

void Styles::Move::applyOn(StyleProperties &styles)
{
    styles.position = _pos;
}

Styles::RelativePosition::RelativePosition() = default;

void Styles::RelativePosition::applyOn(StyleProperties &styles)
{
    styles.isRelative = true;
}

Styles::AbsolutePosition::AbsolutePosition() = default;

void Styles::AbsolutePosition::applyOn(StyleProperties &styles)
{
    styles.isRelative = false;
}

Styles::Resize::Resize(const Vector2 &size) : _size(size) {}

void Styles::Resize::applyOn(StyleProperties &styles)
{
    styles.size = _size;
}

Styles::BgColor::BgColor(const Color &color) : _color(color), _enabled(true) {}

Styles::BgColor Styles::BgColor::disabled()
{
    BgColor bg({0, 0, 0});
    bg._enabled = false;
    return bg;
}

void Styles::BgColor::applyOn(StyleProperties &styles)
{
    styles.bgColor.first = _enabled;
    if (_enabled)
    {
        styles.bgColor.second = _color;
    }
}

Styles::OuterBorder::OuterBorder(const Color &color) : _color(color), _enabled(true) {}

Styles::OuterBorder Styles::OuterBorder::disabled()
{
    OuterBorder bg({0, 0, 0});
    bg._enabled = false;
    return bg;
}

void Styles::OuterBorder::applyOn(StyleProperties &styles)
{
    styles.outerBorder.first = _enabled;
    if (_enabled)
    {
        styles.outerBorder.second = _color;
    }
}

// Margin distance
Styles::MarginAll::MarginAll(int value) : _value(value), _enabled(true) {}

void Styles::MarginAll::applyOn(StyleProperties &styles)
{
    if (_enabled)
    {
        styles.marginLeft.first = true;
        styles.marginLeft.second = _value;
        styles.marginRight.first = true;
        styles.marginRight.second = _value;
        styles.marginTop.first = true;
        styles.marginTop.second = _value;
        styles.marginBottom.first = true;
        styles.marginBottom.second = _value;
    }
    else
    {
        styles.marginLeft.first = false;
        styles.marginRight.first = false;
        styles.marginTop.first = false;
        styles.marginBottom.first = false;
    }
}

Styles::MarginAll Styles::MarginAll::disabled()
{
    MarginAll x(0);
    x._enabled = false;
    return x;
}

// Margin X distance
Styles::MarginX::MarginX(int value) : _value(value), _enabled(true) {}

void Styles::MarginX::applyOn(StyleProperties &styles)
{
    if (_enabled)
    {
        styles.marginLeft.first = true;
        styles.marginLeft.second = _value;
        styles.marginRight.first = true;
        styles.marginRight.second = _value;
    }
    else
    {
        styles.marginLeft.first = _value;
        styles.marginRight.first = false;
    }
}

Styles::MarginX Styles::MarginX::disabled()
{
    MarginX x(0);
    x._enabled = false;
    return x;
}

// Margin Y distance
Styles::MarginY::MarginY(int value) : _value(value), _enabled(true) {}

void Styles::MarginY::applyOn(StyleProperties &styles)
{
    if (_enabled)
    {
        styles.marginTop.first = true;
        styles.marginTop.second = _value;
        styles.marginBottom.first = true;
        styles.marginBottom.second = _value;
    }
    else
    {
        styles.marginTop.first = false;
        styles.marginBottom.first = false;
    }
}

Styles::MarginY Styles::MarginY::disabled()
{
    MarginY x(0);
    x._enabled = false;
    return x;
}

// Margin Left distance
Styles::MarginLeft::MarginLeft(int value) : _value(value), _enabled(true) {}

void Styles::MarginLeft::applyOn(StyleProperties &styles)
{
    if (_enabled)
    {
        styles.marginLeft.first = true;
        styles.marginLeft.second = _value;
    }
    else
    {
        styles.marginLeft.first = false;
    }
}

Styles::MarginLeft Styles::MarginLeft::disabled()
{
    MarginLeft x(0);
    x._enabled = false;
    return x;
}

// Margin Right distance
Styles::MarginRight::MarginRight(int value) : _value(value), _enabled(true) {}

void Styles::MarginRight::applyOn(StyleProperties &styles)
{
    if (_enabled)
    {

        styles.marginRight.first = true;
        styles.marginRight.second = _value;
    }
    else
    {
        styles.marginRight.first = false;
    }
}

Styles::MarginRight Styles::MarginRight::disabled()
{
    MarginRight x(0);
    x._enabled = false;
    return x;
}

// Margin Top distance
Styles::MarginTop::MarginTop(int value) : _value(value), _enabled(true) {}

void Styles::MarginTop::applyOn(StyleProperties &styles)
{
    if (_enabled)
    {

        styles.marginTop.first = true;
        styles.marginTop.second = _value;
    }
    else
    {
        styles.marginTop.first = false;
    }
}

Styles::MarginTop Styles::MarginTop::disabled()
{
    MarginTop x(0);
    x._enabled = false;
    return x;
}

// Margin Btm distance
Styles::MarginBtm::MarginBtm(int value) : _value(value), _enabled(true) {}

void Styles::MarginBtm::applyOn(StyleProperties &styles)
{
    if (_enabled)
    {

        styles.marginBottom.first = true;
        styles.marginBottom.second = _value;
    }
    else
    {
        styles.marginBottom.first = false;
    }
}

Styles::MarginBtm Styles::MarginBtm::disabled()
{
    MarginBtm x(0);
    x._enabled = false;
    return x;
}
