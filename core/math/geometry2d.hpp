#pragma once

#include <core/math/math_defs.hpp>
#include <core/math/vector2.hpp>

#include <optional>

namespace sdl {

template<class>
struct Rect2;
typedef Rect2<real> Rect2f;

namespace Geometry2D {

/**
* @returns true if the @param point is inside the circle.
* @param circle_radius describes the radius of the circle.
* @param circle_position describes the position of the circle.
*/
constexpr bool is_point_inside_circle(const real circle_radius, const Vector2f &point, const Vector2f &circle_position = Vector2f(1, 1)) {
	return point.distance_to_squared(circle_position) <= circle_radius * circle_radius;
}

/**
* @returns true if the left circle intersects the right circle.
* @param left_circle_radius describes the radius of the left circle.
* @param left_circle_position describes the position of the left circle.
* @param right_circle_radius describes the radius of the right circle.
* @param right_circle_position describes the position of the right circle.
*/
constexpr bool are_circles_intersecting(const real left_circle_radius, const Vector2f &left_circle_position, const real right_circle_radius, const Vector2f &right_circle_position) {
	return left_circle_position.distance_to_squared(right_circle_position) <= (left_circle_radius * left_circle_radius) + (right_circle_radius * right_circle_radius);
}

/**
* Checks if the two lines @param from_a, @param dir_a and @param from_b, @param dir_b intersect.
* @returns the point of intersection as a Vector2f if the lines intersect.
* @note the lines are specified using direction vectors, not end points.
*/
constexpr std::optional<Vector2f> line_intersects_line(const Vector2f &from_a, const Vector2f &dir_a, const Vector2f &from_b, const Vector2f &dir_b) {
	// See http://paulbourke.net/geometry/pointlineplane/

	const real denom = dir_b.y * dir_a.x - dir_b.x * dir_a.y;
	if (Math::is_zero_approx(denom))
		return std::nullopt;

	const Vector2f v = from_a - from_b;
	const real t = (dir_b.x * v.y - dir_b.y * v.x) / denom;
	return std::optional<Vector2f>(from_a + (dir_a * t));
}

/**
* @returns true if the directions @param dir_a and @param dir_b intersect.
*/
constexpr bool is_direction_intersecting_direction(const Vector2f &dir_a, const Vector2f &dir_b) {
	const real denom = dir_b.y * dir_a.x - dir_b.x * dir_a.y;
	return !Math::is_zero_approx(denom);
}

/**
* @returns true if the @param rect intersects with the circle.
* @param circle_radius describes the radius of the circle.
* @param circle_position describes the position of the circle.
*/
bool rect_intersects_circle(const Rect2f &rect, const real circle_radius, const Vector2f &circle_position);

/**
* @returns a Vector (in global position) that represents the @param point rotated by @param rotation_degrees.
* If you want to get a point's rotation relative to a another point then
* simply subtract the point's position by the other point. Note: The value returned is in global coordinates.
*/
Vector2f rotate_point_around(const double rotation_degrees, const Vector2f &point);

}

}
