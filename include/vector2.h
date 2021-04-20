#ifndef CMAKE_ITK_GRAPHICSLIB_SRC_VECTOR2_H_
#define CMAKE_ITK_GRAPHICSLIB_SRC_VECTOR2_H_

#include "graphics.hpp"
#include <iostream>
#include <cmath>
#include "color.h"

class Vector2 {
 private:
  int _x{}, _y{};
 public:
  static Vector2 from_stream(std::istream &is);

  inline Vector2(int x, int y) {
    setX(x);
    setY(y);
  }

  inline virtual ~Vector2() = default;

  inline void move_to() const { genv::gout << genv::move_to(x(), y()); }

  inline void box() const { genv::gout << genv::box(x(), y()); }

  inline void draw_color(const Color &c) const {
    c.apply();
    draw_color();
  }

  inline void draw_color() const {
    this->move_to();
    genv::gout << genv::dot;
  }

  inline void line_to_abs(const Vector2 &v) const {
    this->move_to();
    genv::gout << genv::line_to(v.x(), v.y());
  };

  inline void line_to_rel(const Vector2 &v) const {
    this->move_to();
    genv::gout << genv::line(v.x(), v.y());
  };

  inline void draw_rect(const Vector2 &size) const {
    this->move_to();
    genv::gout << genv::box(size.x(), size.y());
  }

  inline void clear() const {
    Color(0, 0, 0).apply();
    Vector2(0, 0).draw_rect(*this);
  }

  inline Vector2() : Vector2(0, 0) {};

  inline int x() const { return _x; }

  inline int y() const { return _y; }

  inline int getX() const { return x(); }

  inline int getY() const { return y(); }

  inline void setX(int new_x) {
    if (new_x & ~1023) {
      throw std::invalid_argument("x should not be negative or too large!");
    }
    _x = new_x;
  }

  inline void setY(int new_y) {
    if (new_y & ~1023) {
      throw std::invalid_argument("y should not be negative or too large!");
    }
    _y = new_y;
  }

  inline int len_squared() const {
    return x() * x() + y() * y();
  }

  inline double len() const {
    return sqrt(len_squared() * 1.0);
  }

  inline bool eq(const Vector2 &rhs) const {
    return _x == rhs._x && _y == rhs._y;
  }

  inline bool ne(const Vector2 &rhs) const { return !eq(rhs); }

  inline Vector2 add(const Vector2 &rhs) const { return {x() + rhs.x(), y() + rhs.y()}; }

  inline Vector2 sub(const Vector2 &rhs) const { return {x() - rhs.x(), y() - rhs.y()}; }

  inline Vector2 mul(double scalar) const { return {static_cast<int>(x() * scalar), static_cast<int>(y() * scalar)}; }

  inline void add_assign(const Vector2 &rhs) {
    setX(x() + rhs.x());
    setY(y() + rhs.y());
  }

  inline void sub_assign(const Vector2 &rhs) {
    setX(x() - rhs.x());
    setY(y() - rhs.y());
  }

  inline void mul_assign(double scalar) {
    setX(x() * scalar);
    setY(y() * scalar);
  }

  inline Vector2 neg() const { return {-x(), -y()}; }

  inline Vector2 operator+(const Vector2 &rhs) const { return this->add(rhs); }

  inline Vector2 operator-(const Vector2 &rhs) const { return this->sub(rhs); }

  inline Vector2 operator*(double scalar) const { return this->mul(scalar); }

  inline Vector2 operator-() const { return this->neg(); }

  inline void operator+=(const Vector2 &rhs) { this->add_assign(rhs); }

  inline void operator-=(const Vector2 &rhs) { this->sub_assign(rhs); }

  inline void operator*=(double scalar) { this->mul_assign(scalar); }

  inline bool operator==(const Vector2 &rhs) const { return eq(rhs); }

  inline bool operator!=(const Vector2 &rhs) const { return ne(rhs); }

  inline friend std::ostream &operator<<(std::ostream &os, const Vector2 &vector2) {
    os << "Vector2(" << vector2._x << ", " << vector2._y << ')';
    return os;
  }

};

#endif //CMAKE_ITK_GRAPHICSLIB_SRC_VECTOR2_H_
