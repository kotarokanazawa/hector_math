// Copyright (c) 2022 Stefan Fabian. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef HECTOR_MATH_OPERATIONS_H
#define HECTOR_MATH_OPERATIONS_H

#include <cmath>

namespace hector_math
{

/*!
 * Clamps the given value to the range [min, max]. Propagates NaN values.
 * @param val The input value.
 * @param min The minimum value of the return value.
 * @param max The maximum value of the return value.
 * @return val if it is within min and max, min if val is smaller or equal to min, max if val is larger or equal to max.
 */
template<typename T>
constexpr T clamp( const T &val, const T &min, const T &max )
{
  return val < min ? min : val > max ? max : val;
}

template<typename T>
constexpr T square( const T &x )
{
  return x * x;
}

/*!
 * Ensures the result value will be finite.
 * @return value if value is finite, otherwise the provided finite_value.
 */
template<typename T>
constexpr T ensureFinite( const T &value, const T &finite_value )
{
#if __cplusplus >= 201402L
  assert( std::isfinite( finite_value ) &&
          "The finite_value passed to ensureFinite should be finite!" );
#endif
  return std::isfinite( value ) ? value : finite_value;
}

//! Rounds the given value to the nearest multiple of the increment.
template<typename T>
constexpr T makeMultipleRound( const T &value, const T &increment )
{
  return increment * static_cast<T>( std::round( value / static_cast<double>( increment ) ) );
}

//! Returns the smallest multiple of the increment that is larger or equal to the given value.
template<typename T>
constexpr T makeMultipleCeil( const T &value, const T &increment )
{
  return increment * static_cast<T>( std::ceil( value / static_cast<double>( increment ) ) );
}

//! Returns the largest multiple of the increment that is smaller or equal to the given value.
template<typename T>
constexpr T makeMultipleFloor( const T &value, const T &increment )
{
  return increment * static_cast<T>( std::floor( value / static_cast<double>( increment ) ) );
}

} // namespace hector_math

#endif // HECTOR_MATH_OPERATIONS_H
