#ifndef CMAKE_ITK_GRAPHICSLIB_SRC_COLOR_H_
#define CMAKE_ITK_GRAPHICSLIB_SRC_COLOR_H_

#include <cmath>
#include <iostream>
#include "graphics.hpp"

struct Color
{
  int r, g, b;

  Color(int r, int g, int b) : r(r), g(g), b(b) {}

  Color() : Color(0, 0, 0) {}

  inline virtual ~Color() = default;

  static Color from_stream(std::istream &is);

  inline bool eq(const Color &x, int eps = 0) const
  {
    return abs(r - x.r) < eps && abs(g - x.g) < eps && abs(b - x.b) < eps;
  }

  inline void apply() const { genv::gout << genv::color(r, g, b); }

  inline bool ne(const Color &x, int eps = 0) const { return !eq(x, eps); }

  inline bool operator==(const Color &rhs) const { return this->eq(rhs); }

  inline bool operator!=(const Color &rhs) const { return this->ne(rhs); }

  inline friend std::ostream &operator<<(std::ostream &os, const Color &color)
  {
    os << "Color(" << color.r << ", " << color.g << ", " << color.b << ')';
    return os;
  }
};

#endif //CMAKE_ITK_GRAPHICSLIB_SRC_COLOR_H_
