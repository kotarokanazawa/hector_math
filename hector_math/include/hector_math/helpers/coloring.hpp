// Copyright (c) 2023 Stefan Fabian. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef HECTOR_MATH_COLORING_H
#define HECTOR_MATH_COLORING_H

#include <algorithm>
#include <cassert>

namespace hector_math
{
namespace coloring
{
struct RGB;
struct RGBf {
  float r, g, b;
  RGBf( float r, float g, float b ) : r( r ), g( g ), b( b ) { }

  RGB toRGB() const;
};

struct RGB {
  unsigned char r, g, b;
  constexpr RGB( unsigned char r = 0, unsigned char g = 0, unsigned char b = 0 )
      : r( r ), g( g ), b( b )
  {
  }

  RGBf toRGBf() const { return { r / 255.f, g / 255.f, b / 255.f }; }
};

inline RGB RGBf::toRGB() const
{
  return { static_cast<unsigned char>( r * 255 ), static_cast<unsigned char>( g * 255 ),
           static_cast<unsigned char>( b * 255 ) };
}

enum class GradientMethod : int {
  Grayscale,
  Blue2Red,
  Red2Blue,
  // An optimized version of the Jet colormap, see https://research.google/blog/turbo-an-improved-rainbow-colormap-for-visualization/
  Turbo,
  // A color vision deficiency optimized version of Virides, see https://doi.org/10.1371/journal.pone.0199239
  Civides
};

static constexpr GradientMethod DEFAULT_GRADIENT_METHOD = GradientMethod::Turbo;

namespace _impl
{
static constexpr RGB TURBO_COLORS[256] = {
    RGB( 48, 18, 59 ),   RGB( 50, 21, 67 ),   RGB( 51, 24, 74 ),    RGB( 52, 27, 81 ),
    RGB( 53, 30, 88 ),   RGB( 54, 33, 95 ),   RGB( 55, 36, 102 ),   RGB( 56, 39, 109 ),
    RGB( 57, 42, 115 ),  RGB( 58, 45, 121 ),  RGB( 59, 47, 128 ),   RGB( 60, 50, 134 ),
    RGB( 61, 53, 139 ),  RGB( 62, 56, 145 ),  RGB( 63, 59, 151 ),   RGB( 63, 62, 156 ),
    RGB( 64, 64, 162 ),  RGB( 65, 67, 167 ),  RGB( 65, 70, 172 ),   RGB( 66, 73, 177 ),
    RGB( 66, 75, 181 ),  RGB( 67, 78, 186 ),  RGB( 68, 81, 191 ),   RGB( 68, 84, 195 ),
    RGB( 68, 86, 199 ),  RGB( 69, 89, 203 ),  RGB( 69, 92, 207 ),   RGB( 69, 94, 211 ),
    RGB( 70, 97, 214 ),  RGB( 70, 100, 218 ), RGB( 70, 102, 221 ),  RGB( 70, 105, 224 ),
    RGB( 70, 107, 227 ), RGB( 71, 110, 230 ), RGB( 71, 113, 233 ),  RGB( 71, 115, 235 ),
    RGB( 71, 118, 238 ), RGB( 71, 120, 240 ), RGB( 71, 123, 242 ),  RGB( 70, 125, 244 ),
    RGB( 70, 128, 246 ), RGB( 70, 130, 248 ), RGB( 70, 133, 250 ),  RGB( 70, 135, 251 ),
    RGB( 69, 138, 252 ), RGB( 69, 140, 253 ), RGB( 68, 143, 254 ),  RGB( 67, 145, 254 ),
    RGB( 66, 148, 255 ), RGB( 65, 150, 255 ), RGB( 64, 153, 255 ),  RGB( 62, 155, 254 ),
    RGB( 61, 158, 254 ), RGB( 59, 160, 253 ), RGB( 58, 163, 252 ),  RGB( 56, 165, 251 ),
    RGB( 55, 168, 250 ), RGB( 53, 171, 248 ), RGB( 51, 173, 247 ),  RGB( 49, 175, 245 ),
    RGB( 47, 178, 244 ), RGB( 46, 180, 242 ), RGB( 44, 183, 240 ),  RGB( 42, 185, 238 ),
    RGB( 40, 188, 235 ), RGB( 39, 190, 233 ), RGB( 37, 192, 231 ),  RGB( 35, 195, 228 ),
    RGB( 34, 197, 226 ), RGB( 32, 199, 223 ), RGB( 31, 201, 221 ),  RGB( 30, 203, 218 ),
    RGB( 28, 205, 216 ), RGB( 27, 208, 213 ), RGB( 26, 210, 210 ),  RGB( 26, 212, 208 ),
    RGB( 25, 213, 205 ), RGB( 24, 215, 202 ), RGB( 24, 217, 200 ),  RGB( 24, 219, 197 ),
    RGB( 24, 221, 194 ), RGB( 24, 222, 192 ), RGB( 24, 224, 189 ),  RGB( 25, 226, 187 ),
    RGB( 25, 227, 185 ), RGB( 26, 228, 182 ), RGB( 28, 230, 180 ),  RGB( 29, 231, 178 ),
    RGB( 31, 233, 175 ), RGB( 32, 234, 172 ), RGB( 34, 235, 170 ),  RGB( 37, 236, 167 ),
    RGB( 39, 238, 164 ), RGB( 42, 239, 161 ), RGB( 44, 240, 158 ),  RGB( 47, 241, 155 ),
    RGB( 50, 242, 152 ), RGB( 53, 243, 148 ), RGB( 56, 244, 145 ),  RGB( 60, 245, 142 ),
    RGB( 63, 246, 138 ), RGB( 67, 247, 135 ), RGB( 70, 248, 132 ),  RGB( 74, 248, 128 ),
    RGB( 78, 249, 125 ), RGB( 82, 250, 122 ), RGB( 85, 250, 118 ),  RGB( 89, 251, 115 ),
    RGB( 93, 252, 111 ), RGB( 97, 252, 108 ), RGB( 101, 253, 105 ), RGB( 105, 253, 102 ),
    RGB( 109, 254, 98 ), RGB( 113, 254, 95 ), RGB( 117, 254, 92 ),  RGB( 121, 254, 89 ),
    RGB( 125, 255, 86 ), RGB( 128, 255, 83 ), RGB( 132, 255, 81 ),  RGB( 136, 255, 78 ),
    RGB( 139, 255, 75 ), RGB( 143, 255, 73 ), RGB( 146, 255, 71 ),  RGB( 150, 254, 68 ),
    RGB( 153, 254, 66 ), RGB( 156, 254, 64 ), RGB( 159, 253, 63 ),  RGB( 161, 253, 61 ),
    RGB( 164, 252, 60 ), RGB( 167, 252, 58 ), RGB( 169, 251, 57 ),  RGB( 172, 251, 56 ),
    RGB( 175, 250, 55 ), RGB( 177, 249, 54 ), RGB( 180, 248, 54 ),  RGB( 183, 247, 53 ),
    RGB( 185, 246, 53 ), RGB( 188, 245, 52 ), RGB( 190, 244, 52 ),  RGB( 193, 243, 52 ),
    RGB( 195, 241, 52 ), RGB( 198, 240, 52 ), RGB( 200, 239, 52 ),  RGB( 203, 237, 52 ),
    RGB( 205, 236, 52 ), RGB( 208, 234, 52 ), RGB( 210, 233, 53 ),  RGB( 212, 231, 53 ),
    RGB( 215, 229, 53 ), RGB( 217, 228, 54 ), RGB( 219, 226, 54 ),  RGB( 221, 224, 55 ),
    RGB( 223, 223, 55 ), RGB( 225, 221, 55 ), RGB( 227, 219, 56 ),  RGB( 229, 217, 56 ),
    RGB( 231, 215, 57 ), RGB( 233, 213, 57 ), RGB( 235, 211, 57 ),  RGB( 236, 209, 58 ),
    RGB( 238, 207, 58 ), RGB( 239, 205, 58 ), RGB( 241, 203, 58 ),  RGB( 242, 201, 58 ),
    RGB( 244, 199, 58 ), RGB( 245, 197, 58 ), RGB( 246, 195, 58 ),  RGB( 247, 193, 58 ),
    RGB( 248, 190, 57 ), RGB( 249, 188, 57 ), RGB( 250, 186, 57 ),  RGB( 251, 184, 56 ),
    RGB( 251, 182, 55 ), RGB( 252, 179, 54 ), RGB( 252, 177, 54 ),  RGB( 253, 174, 53 ),
    RGB( 253, 172, 52 ), RGB( 254, 169, 51 ), RGB( 254, 167, 50 ),  RGB( 254, 164, 49 ),
    RGB( 254, 161, 48 ), RGB( 254, 158, 47 ), RGB( 254, 155, 45 ),  RGB( 254, 153, 44 ),
    RGB( 254, 150, 43 ), RGB( 254, 147, 42 ), RGB( 254, 144, 41 ),  RGB( 253, 141, 39 ),
    RGB( 253, 138, 38 ), RGB( 252, 135, 37 ), RGB( 252, 132, 35 ),  RGB( 251, 129, 34 ),
    RGB( 251, 126, 33 ), RGB( 250, 123, 31 ), RGB( 249, 120, 30 ),  RGB( 249, 117, 29 ),
    RGB( 248, 114, 28 ), RGB( 247, 111, 26 ), RGB( 246, 108, 25 ),  RGB( 245, 105, 24 ),
    RGB( 244, 102, 23 ), RGB( 243, 99, 21 ),  RGB( 242, 96, 20 ),   RGB( 241, 93, 19 ),
    RGB( 240, 91, 18 ),  RGB( 239, 88, 17 ),  RGB( 237, 85, 16 ),   RGB( 236, 83, 15 ),
    RGB( 235, 80, 14 ),  RGB( 234, 78, 13 ),  RGB( 232, 75, 12 ),   RGB( 231, 73, 12 ),
    RGB( 229, 71, 11 ),  RGB( 228, 69, 10 ),  RGB( 226, 67, 10 ),   RGB( 225, 65, 9 ),
    RGB( 223, 63, 8 ),   RGB( 221, 61, 8 ),   RGB( 220, 59, 7 ),    RGB( 218, 57, 7 ),
    RGB( 216, 55, 6 ),   RGB( 214, 53, 6 ),   RGB( 212, 51, 5 ),    RGB( 210, 49, 5 ),
    RGB( 208, 47, 5 ),   RGB( 206, 45, 4 ),   RGB( 204, 43, 4 ),    RGB( 202, 42, 4 ),
    RGB( 200, 40, 3 ),   RGB( 197, 38, 3 ),   RGB( 195, 37, 3 ),    RGB( 193, 35, 2 ),
    RGB( 190, 33, 2 ),   RGB( 188, 32, 2 ),   RGB( 185, 30, 2 ),    RGB( 183, 29, 2 ),
    RGB( 180, 27, 1 ),   RGB( 178, 26, 1 ),   RGB( 175, 24, 1 ),    RGB( 172, 23, 1 ),
    RGB( 169, 22, 1 ),   RGB( 167, 20, 1 ),   RGB( 164, 19, 1 ),    RGB( 161, 18, 1 ),
    RGB( 158, 16, 1 ),   RGB( 155, 15, 1 ),   RGB( 152, 14, 1 ),    RGB( 149, 13, 1 ),
    RGB( 146, 11, 1 ),   RGB( 142, 10, 1 ),   RGB( 139, 9, 2 ),     RGB( 136, 8, 2 ),
    RGB( 133, 7, 2 ),    RGB( 129, 6, 2 ),    RGB( 126, 5, 2 ),     RGB( 122, 4, 3 ) };
static constexpr RGB CIVIDES_COLORS[256] = {
    RGB( 0, 32, 76 ),     RGB( 0, 32, 78 ),     RGB( 0, 33, 80 ),     RGB( 0, 34, 81 ),
    RGB( 0, 35, 83 ),     RGB( 0, 35, 85 ),     RGB( 0, 36, 86 ),     RGB( 0, 37, 88 ),
    RGB( 0, 38, 90 ),     RGB( 0, 38, 91 ),     RGB( 0, 39, 93 ),     RGB( 0, 40, 95 ),
    RGB( 0, 40, 97 ),     RGB( 0, 41, 99 ),     RGB( 0, 42, 100 ),    RGB( 0, 42, 102 ),
    RGB( 0, 43, 104 ),    RGB( 0, 44, 106 ),    RGB( 0, 45, 108 ),    RGB( 0, 45, 109 ),
    RGB( 0, 46, 110 ),    RGB( 0, 46, 111 ),    RGB( 0, 47, 111 ),    RGB( 0, 47, 111 ),
    RGB( 0, 48, 111 ),    RGB( 0, 49, 111 ),    RGB( 0, 49, 111 ),    RGB( 0, 50, 110 ),
    RGB( 0, 51, 110 ),    RGB( 0, 52, 110 ),    RGB( 0, 52, 110 ),    RGB( 1, 53, 110 ),
    RGB( 6, 54, 110 ),    RGB( 10, 55, 109 ),   RGB( 14, 55, 109 ),   RGB( 18, 56, 109 ),
    RGB( 21, 57, 109 ),   RGB( 23, 57, 109 ),   RGB( 26, 58, 108 ),   RGB( 28, 59, 108 ),
    RGB( 30, 60, 108 ),   RGB( 32, 60, 108 ),   RGB( 34, 61, 108 ),   RGB( 36, 62, 108 ),
    RGB( 38, 62, 108 ),   RGB( 39, 63, 108 ),   RGB( 41, 64, 107 ),   RGB( 43, 65, 107 ),
    RGB( 44, 65, 107 ),   RGB( 46, 66, 107 ),   RGB( 47, 67, 107 ),   RGB( 49, 68, 107 ),
    RGB( 50, 68, 107 ),   RGB( 51, 69, 107 ),   RGB( 53, 70, 107 ),   RGB( 54, 70, 107 ),
    RGB( 55, 71, 107 ),   RGB( 56, 72, 107 ),   RGB( 58, 73, 107 ),   RGB( 59, 73, 107 ),
    RGB( 60, 74, 107 ),   RGB( 61, 75, 107 ),   RGB( 62, 75, 107 ),   RGB( 64, 76, 107 ),
    RGB( 65, 77, 107 ),   RGB( 66, 78, 107 ),   RGB( 67, 78, 107 ),   RGB( 68, 79, 107 ),
    RGB( 69, 80, 107 ),   RGB( 70, 80, 107 ),   RGB( 71, 81, 107 ),   RGB( 72, 82, 107 ),
    RGB( 73, 83, 107 ),   RGB( 74, 83, 107 ),   RGB( 75, 84, 107 ),   RGB( 76, 85, 107 ),
    RGB( 77, 85, 107 ),   RGB( 78, 86, 107 ),   RGB( 79, 87, 108 ),   RGB( 80, 88, 108 ),
    RGB( 81, 88, 108 ),   RGB( 82, 89, 108 ),   RGB( 83, 90, 108 ),   RGB( 84, 90, 108 ),
    RGB( 85, 91, 108 ),   RGB( 86, 92, 108 ),   RGB( 87, 93, 109 ),   RGB( 88, 93, 109 ),
    RGB( 89, 94, 109 ),   RGB( 90, 95, 109 ),   RGB( 91, 95, 109 ),   RGB( 92, 96, 109 ),
    RGB( 93, 97, 110 ),   RGB( 94, 98, 110 ),   RGB( 95, 98, 110 ),   RGB( 95, 99, 110 ),
    RGB( 96, 100, 110 ),  RGB( 97, 101, 111 ),  RGB( 98, 101, 111 ),  RGB( 99, 102, 111 ),
    RGB( 100, 103, 111 ), RGB( 101, 103, 111 ), RGB( 102, 104, 112 ), RGB( 103, 105, 112 ),
    RGB( 104, 106, 112 ), RGB( 104, 106, 112 ), RGB( 105, 107, 113 ), RGB( 106, 108, 113 ),
    RGB( 107, 109, 113 ), RGB( 108, 109, 114 ), RGB( 109, 110, 114 ), RGB( 110, 111, 114 ),
    RGB( 111, 111, 114 ), RGB( 111, 112, 115 ), RGB( 112, 113, 115 ), RGB( 113, 114, 115 ),
    RGB( 114, 114, 116 ), RGB( 115, 115, 116 ), RGB( 116, 116, 117 ), RGB( 117, 117, 117 ),
    RGB( 117, 117, 117 ), RGB( 118, 118, 118 ), RGB( 119, 119, 118 ), RGB( 120, 120, 118 ),
    RGB( 121, 120, 119 ), RGB( 122, 121, 119 ), RGB( 123, 122, 119 ), RGB( 123, 123, 120 ),
    RGB( 124, 123, 120 ), RGB( 125, 124, 120 ), RGB( 126, 125, 120 ), RGB( 127, 126, 120 ),
    RGB( 128, 126, 120 ), RGB( 129, 127, 120 ), RGB( 130, 128, 120 ), RGB( 131, 129, 120 ),
    RGB( 132, 129, 120 ), RGB( 133, 130, 120 ), RGB( 134, 131, 120 ), RGB( 135, 132, 120 ),
    RGB( 136, 133, 120 ), RGB( 137, 133, 120 ), RGB( 138, 134, 120 ), RGB( 139, 135, 120 ),
    RGB( 140, 136, 120 ), RGB( 141, 136, 120 ), RGB( 142, 137, 120 ), RGB( 143, 138, 120 ),
    RGB( 144, 139, 120 ), RGB( 145, 140, 120 ), RGB( 146, 140, 120 ), RGB( 147, 141, 120 ),
    RGB( 148, 142, 120 ), RGB( 149, 143, 120 ), RGB( 150, 143, 119 ), RGB( 151, 144, 119 ),
    RGB( 152, 145, 119 ), RGB( 153, 146, 119 ), RGB( 154, 147, 119 ), RGB( 155, 147, 119 ),
    RGB( 156, 148, 119 ), RGB( 157, 149, 119 ), RGB( 158, 150, 118 ), RGB( 159, 151, 118 ),
    RGB( 160, 152, 118 ), RGB( 161, 152, 118 ), RGB( 162, 153, 118 ), RGB( 163, 154, 117 ),
    RGB( 164, 155, 117 ), RGB( 165, 156, 117 ), RGB( 166, 156, 117 ), RGB( 167, 157, 117 ),
    RGB( 168, 158, 116 ), RGB( 169, 159, 116 ), RGB( 170, 160, 116 ), RGB( 171, 161, 116 ),
    RGB( 172, 161, 115 ), RGB( 173, 162, 115 ), RGB( 174, 163, 115 ), RGB( 175, 164, 115 ),
    RGB( 176, 165, 114 ), RGB( 177, 166, 114 ), RGB( 178, 166, 114 ), RGB( 180, 167, 113 ),
    RGB( 181, 168, 113 ), RGB( 182, 169, 113 ), RGB( 183, 170, 112 ), RGB( 184, 171, 112 ),
    RGB( 185, 171, 112 ), RGB( 186, 172, 111 ), RGB( 187, 173, 111 ), RGB( 188, 174, 110 ),
    RGB( 189, 175, 110 ), RGB( 190, 176, 110 ), RGB( 191, 177, 109 ), RGB( 192, 177, 109 ),
    RGB( 193, 178, 108 ), RGB( 194, 179, 108 ), RGB( 195, 180, 108 ), RGB( 197, 181, 107 ),
    RGB( 198, 182, 107 ), RGB( 199, 183, 106 ), RGB( 200, 184, 106 ), RGB( 201, 184, 105 ),
    RGB( 202, 185, 105 ), RGB( 203, 186, 104 ), RGB( 204, 187, 104 ), RGB( 205, 188, 103 ),
    RGB( 206, 189, 103 ), RGB( 208, 190, 102 ), RGB( 209, 191, 102 ), RGB( 210, 192, 101 ),
    RGB( 211, 192, 101 ), RGB( 212, 193, 100 ), RGB( 213, 194, 99 ),  RGB( 214, 195, 99 ),
    RGB( 215, 196, 98 ),  RGB( 216, 197, 97 ),  RGB( 217, 198, 97 ),  RGB( 219, 199, 96 ),
    RGB( 220, 200, 96 ),  RGB( 221, 201, 95 ),  RGB( 222, 202, 94 ),  RGB( 223, 203, 93 ),
    RGB( 224, 203, 93 ),  RGB( 225, 204, 92 ),  RGB( 227, 205, 91 ),  RGB( 228, 206, 91 ),
    RGB( 229, 207, 90 ),  RGB( 230, 208, 89 ),  RGB( 231, 209, 88 ),  RGB( 232, 210, 87 ),
    RGB( 233, 211, 86 ),  RGB( 235, 212, 86 ),  RGB( 236, 213, 85 ),  RGB( 237, 214, 84 ),
    RGB( 238, 215, 83 ),  RGB( 239, 216, 82 ),  RGB( 240, 217, 81 ),  RGB( 241, 218, 80 ),
    RGB( 243, 219, 79 ),  RGB( 244, 220, 78 ),  RGB( 245, 221, 77 ),  RGB( 246, 222, 76 ),
    RGB( 247, 223, 75 ),  RGB( 249, 224, 73 ),  RGB( 250, 224, 72 ),  RGB( 251, 225, 71 ),
    RGB( 252, 226, 70 ),  RGB( 253, 227, 69 ),  RGB( 255, 228, 67 ),  RGB( 255, 229, 66 ),
    RGB( 255, 230, 66 ),  RGB( 255, 231, 67 ),  RGB( 255, 232, 68 ),  RGB( 255, 233, 69 ) };
} // namespace _impl

static constexpr int NUM_SEGMENT_COLORS = 19;

/**
 * @brief Get a distinct color for a color segment. See NUM_SEGMENT_COLORS for the number of available colors.
 *
 * @param index The index of the color segment. Must be in the range [0, NUM_SEGMENT_COLORS).
 * @return RGB Color of the segment.
 */
inline RGB segmentColor( int index )
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
    assert( false && "hector_math only provides 19 distinct colors!" );
    return { 0, 0, 0 }; // Default to black for invalid index
  }
}

/**
 * @brief Obtain a color from a color gradient using the given method.
 *
 * @param value The value to colorize. Values outside of [min, max] are bound to the range [min, max].
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 * @param method The method to use for coloring. See GradientMethod for available methods. Default: Turbo
 * @return RGB The gradient color for the given value.
 */
inline RGB gradientColor( float value, float min = 0, float max = 1,
                          GradientMethod method = GradientMethod::Turbo )
{
  float scaled_value = max == min ? 1 : ( value - min ) / ( max - min );
  scaled_value = std::min<float>( scaled_value, 1 );
  scaled_value = std::max<float>( scaled_value, 0 );
  switch ( method ) {
  case GradientMethod::Grayscale:
    return RGB( 255 * scaled_value, 255 * scaled_value, 255 * scaled_value );
  case GradientMethod::Blue2Red:
    return RGB( 255 * scaled_value, 0, 255 * ( 1 - scaled_value ) );
  case GradientMethod::Red2Blue:
    return RGB( 255 * ( 1 - scaled_value ), 0, 255 * scaled_value );
  case GradientMethod::Turbo:
    return _impl::TURBO_COLORS[static_cast<int>( scaled_value * 255 )];
  case GradientMethod::Civides:
    return _impl::CIVIDES_COLORS[static_cast<int>( scaled_value * 255 )];
  default:
    assert( false && "Unknown gradient method!" );
    return { 0, 0, 0 };
  }
}

/**
 * @brief See gradientColor( float value, float min, float max, GradientMethod method )
 * This method uses the default range [0, 1].
 */
inline RGB gradientColor( float value, GradientMethod method = GradientMethod::Turbo )
{
  return gradientColor( value, 0, 1, method );
}
} // namespace coloring
} // namespace hector_math

#endif // HECTOR_MATH_COLORING_H
