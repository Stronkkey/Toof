#pragma once

#include <core/math/math_defs.hpp>
#include <core/math/vector2.hpp>

#include <optional>

namespace sdl {

struct Rect2;

namespace Geometry2D {

/**
* @returns true if the @param point is inside the circle.
* @param circle_radius describes the radius of the circle.
* @param circle_position describes the position of the circle.
*/
bool is_point_inside_circle(const real_t circle_radius, const Vector2 &point, const Vector2 &circle_position = Vector2::ZERO);

/**
* @returns true if the left circle intersects the right circle.
* @param left_circle_radius describes the radius of the left circle.
* @param left_circle_position describes the position of the left circle.
* @param right_circle_radius describes the radius of the right circle.
* @param right_circle_position describes the position of the right circle.
*/
bool are_circles_intersecting(const real_t left_circle_radius, const Vector2 &left_circle_position, const real_t right_circle_radius, const Vector2 &right_circle_position);

/**
* Checks if the two lines @param from_a, @param dir_a and @param from_b, @param dir_b intersect.
* @returns the point of intersection as a Vector2 if the lines intersect.
* @note the lines are specified using direction vectors, not end points.
*/
std::optional<Vector2> line_intersects_line(const Vector2 &from_a, const Vector2 &dir_a, const Vector2 &from_b, const Vector2 &dir_b);

/**
* @returns true if the directions @param dir_a and @param dir_b intersect.
*/
bool is_direction_intersecting_direction(const Vector2 &dir_a, const Vector2 &dir_b);

/**
* @returns true if the @param rect intersects with the circle.
* @param circle_radius describes the radius of the circle.
* @param circle_position describes the position of the circle.
*/
bool rect_intersects_circle(const Rect2 &rect, const real_t circle_radius, const Vector2 &circle_position);

/**
* @returns a Vector (in global position) that represents the @param point rotated by @param rotation_degrees.
* If you want to get a point's rotation relative to a another point then
* simply subtract the point's position by the other point. Note: The value returned is in global coordinates.
*/
Vector2 rotate_point_around(const double rotation_degrees, const Vector2 &point);

}

}