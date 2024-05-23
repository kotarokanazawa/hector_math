// Copyright (c) 2023 Stefan Fabian. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef HECTOR_MATH_COLORING_H
#define HECTOR_MATH_COLORING_H

#include <cassert>

namespace hector_math
{
namespace coloring
{
struct RGBf {
  float r, g, b;
};

struct RGB {
  unsigned char r, g, b;
  RGBf toRGBf() const { return { r / 255.f, g / 255.f, b / 255.f }; }
};

static constexpr int NUM_COLORS = 19;

RGB color( int index )
{
  switch ( index ) {
  case 0:
    return { 255, 225, 25 };
  case 1:
    return { 0, 130, 200 };
  case 2:
    return { 245, 130, 48 };
  case 3:
    return { 220, 190, 255 };
  case 4:
    return { 128, 0, 0 };
  case 5:
    return { 0, 0, 128 };
  case 6:
    return { 230, 25, 75 };
  case 7:
    return { 60, 180, 75 };
  case 8:
    return { 70, 240, 240 };
  case 9:
    return { 240, 50, 230 };
  case 10:
    return { 250, 190, 212 };
  case 11:
    return { 0, 128, 128 };
  case 12:
    return { 170, 110, 40 };
  case 13:
    return { 255, 250, 200 };
  case 14:
    return { 170, 255, 195 };
  case 15:
    return { 145, 30, 180 };
  case 16:
    return { 210, 245, 60 };
  case 17:
    return { 128, 128, 0 };
  case 18:
    return { 255, 215, 180 };
  default:
    assert( false && "hector_math only provides 18 distinct colors!" );
    return { 0, 0, 0 }; // Default to black for invalid index
  }
}
} // namespace coloring
} // namespace hector_math

#endif // HECTOR_MATH_COLORING_H
