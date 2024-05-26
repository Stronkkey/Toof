/*  This file is part of the Toof Engine. */
/** @file math_funcs.hpp */
/*
  BSD 3-Clause License

  Copyright (c) 2024-present, Stronkkey and Contributors

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
      list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#pragma once

#include <core/math/math_defs.hpp>

#include <algorithm>
#include <type_traits>

namespace Toof {

namespace Math {

template<class T>
using enable_if_arithmetic = typename std::enable_if<std::is_arithmetic<T>::value, bool>::type;

/**
* @brief Converts the rotation in radians to degrees.
* @see DEGREES_RADIAN_SCALAR constant.
*/
template<class T, enable_if_arithmetic<T> = true>
constexpr auto radians_to_degrees(T rotation_radians) {
	return rotation_radians * DEGREES_RADIAN_SCALAR;
}

/**
* @brief Converts the rotation in degrees to radians.
* @see DEGREES_RADIAN_SCALAR constant.
*/
template<class T, enable_if_arithmetic<T> = true>
constexpr auto degrees_to_radians(T rotation_degrees) {
	return rotation_degrees / DEGREES_RADIAN_SCALAR;
}

/**
* @brief Returns @b true if the left number approximately equals the right number.
*/
template<class T, enable_if_arithmetic<T> = true>
constexpr bool is_equal_approx(T left, T right) {
	return left >= (right - CMP_EPSILON) && left <= (right + CMP_EPSILON);
}

/**
* @brief Returns @b true if the left number approximately equals the right number. 
*/
template<class T, class T2, enable_if_arithmetic<T> = true, enable_if_arithmetic<T2> = true>
constexpr bool is_equal_approx(T left, T2 right) {
	return left >= (right - CMP_EPSILON) && left <= (right + CMP_EPSILON);
}

/**
* @brief Returns true if the number is approximately equal to 0. 
*/
template<class T, enable_if_arithmetic<T> = true>
constexpr bool is_zero_approx(T number) {
	return number >= (0.0 - CMP_EPSILON) && number <= (0.0 + CMP_EPSILON);
}

/**
* @brief Linearly interpolates between @b from and @b to by the factor defined by the @b weight.
* @note Values outside of 0.0 and 1.0 are allowed and can be used to perform extrapolation.
*/
template<class T, enable_if_arithmetic<T> = true>
constexpr T lerp(T from, T to, T weight) {
	return from + (to - from) * weight;
}

/**
* @brief Linearly interpolates between @b from and @b to by the factor defined by the @b weight.
* @note Values outside of 0.0 and 1.0 are allowed and can be used to perform extrapolation.
*/
template<class T, class T2, class T3, enable_if_arithmetic<T> = true, enable_if_arithmetic<T2> = true, enable_if_arithmetic<T3> = true>
constexpr auto lerp(T from, T2 to, T3 weight) {
	return from + (to - from) * weight;
}

/**
* @brief Behaves like @b lerp, with the weight argument clamped.
* @details The weight is clamped between 0.0 and 1.0 to prevent extrapolation. If you need extrapolation, then use @b lerp.
*/
template<class T, enable_if_arithmetic<T> = true>
constexpr auto lerpc(T from, T to, T weight) {
	return from + (to - from) * std::clamp<double>(weight, 0.0, 1.0);
}

/**
* @brief Behaves like @b lerp, with the weight argument clamped.
* @details The weight is clamped between 0.0 and 1.0 to prevent extrapolation. If you need extrapolation, then use @b lerp.
*/
template<class T, class T2, class T3, enable_if_arithmetic<T> = true, enable_if_arithmetic<T2> = true, enable_if_arithmetic<T3> = true>
constexpr auto lerpc(T from, T2 to, T3 weight) {
	return from + (to - from) * std::clamp<double>(weight, 0.0, 1.0);
}

}

}
