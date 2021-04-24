#ifndef STYLES_H
#define STYLES_H

#include "color.h"
#include "vector2.h"
#include <functional>

struct Style
{

    // is position relative to the parent?
    bool isRelative = false;
    Vector2 position = {0, 0};

    Vector2 size = {0, 0};

    Color fgColor = {255, 255, 255};

    std::pair<bool, Color> bgMColor = {false, Color{0, 0, 0}};
    std::pair<bool, Color> bgColor = {false, Color{0, 0, 0}};

    unsigned int marginLeft = 0;
    unsigned int marginRight = 0;
    unsigned int marginTop = 0;
    unsigned int marginBottom = 0;

    // enabled? color
    std::pair<bool, Color> outerBorderTop = {false, Color{0, 0, 0}};
    std::pair<bool, Color> outerBorderRight = {false, Color{0, 0, 0}};
    std::pair<bool, Color> outerBorderBottom = {false, Color{0, 0, 0}};
    std::pair<bool, Color> outerBorderLeft = {false, Color{0, 0, 0}};

    std::pair<bool, Color> innerBorderTop = {false, Color{0, 0, 0}};
    std::pair<bool, Color> innerBorderRight = {false, Color{0, 0, 0}};
    std::pair<bool, Color> innerBorderBottom = {false, Color{0, 0, 0}};
    std::pair<bool, Color> innerBorderLeft = {false, Color{0, 0, 0}};
};

typedef std::function<void(Style &style)> Styler;

#endif // STYLES_H
