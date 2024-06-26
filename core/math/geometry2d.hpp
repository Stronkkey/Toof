/*  This file is part of the Toof Engine. */
/** @file geometry2d.hpp */
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
#include <core/math/vector2.hpp>
#include <core/memory/optional.hpp>

namespace Toof {

template<class>
struct Rect2;
typedef Rect2<real> Rect2f;

namespace Geometry2D {

/**
* @brief Returns @b true if the @b point is inside the circle.
*/
constexpr bool is_point_inside_circle(const real circle_radius, const Vector2f &point, const Vector2f &circle_position = Vector2f::ONE()) {
	return point.distance_to_squared(circle_position) <= circle_radius * circle_radius;
}

/**
* @brief Returns @b true if the left circle intersects the right circle.
*/
constexpr bool are_circles_intersecting(const real left_circle_radius, const Vector2f &left_circle_position, const real right_circle_radius, const Vector2f &right_circle_position) {
	return left_circle_position.distance_to_squared(right_circle_position) <= (left_circle_radius * left_circle_radius) + (right_circle_radius * right_circle_radius);
}

/**
* @brief Checks if the two lines @b from_a, @b dir_a and @b from_b, @b dir_b intersect.
* @returns The point of intersection as a Vector2f if the lines intersect.
* @note The lines are specified using direction vectors, not end points.
*/
constexpr Optional<Vector2f> line_intersects_line(const Vector2f &from_a, const Vector2f &dir_a, const Vector2f &from_b, const Vector2f &dir_b) {
	// See http://paulbourke.net/geometry/pointlineplane/

	const real denom = dir_b.y * dir_a.x - dir_b.x * dir_a.y;
	if (Math::is_zero_approx(denom))
		return NullOption;

	const Vector2f v = from_a - from_b;
	const real t = (dir_b.x * v.y - dir_b.y * v.x) / denom;
	return from_a + (dir_a * t);
}

/**
* @brief Returns @b true if the directions @b dir_a and @b dir_b intersect.
*/
constexpr bool is_direction_intersecting_direction(const Vector2f &dir_a, const Vector2f &dir_b) {
	const real denom = dir_b.y * dir_a.x - dir_b.x * dir_a.y;
	return !Math::is_zero_approx(denom);
}

/**
* @brief Returns @b true if the @b rect intersects with the circle.
*/
bool rect_intersects_circle(const Rect2f &rect, const real circle_radius, const Vector2f &circle_position);

/**
* @brief Returns a Vector (in global position) that represents the @b point rotated by @b rotation_degrees.
* @details If you want to get a point's rotation relative to a another point then
* simply subtract the point's position by the other point.
* @note The value returned is in global coordinates.
*/
Vector2f rotate_point_around(const double rotation_degrees, const Vector2f &point);

}

}
