#include "vector2.h"

Vector2 Vector2::from_stream(std::istream &is) {
  int x, y;
  if (is >> x >> y) {
    return {x, y};
  } else {
    throw std::invalid_argument("Failed to parse the stream");
  }
}
