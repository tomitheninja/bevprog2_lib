#include "color.h"

Color Color::from_stream(std::istream &is)
{
  int r = 0, g = 0, b = 0;
  if (is >> r >> g >> b)
  {
    return {r, g, b};
  }
  else
  {
    throw std::invalid_argument("Failed to parse the stream");
  }
}
