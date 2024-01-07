#include "core/math/math_defs.hpp"
#include <core/math/geometry2d.hpp>
#include <core/math/rect2.hpp>

bool sdl::Geometry2D::is_point_inside_circle(const real_t circle_radius, const Vector2 &point, const Vector2 &circle_position) {
	return point.distance_to_squared(circle_position) <= circle_radius * circle_radius;
}

bool sdl::Geometry2D::are_circles_intersecting(const real_t left_circle_radius, const Vector2 &left_circle_position, const real_t right_circle_radius, const Vector2 &right_circle_position) {
	return left_circle_position.distance_to_squared(right_circle_position) <= (left_circle_radius * left_circle_radius) + (right_circle_radius * right_circle_radius);
}

std::optional<sdl::Vector2> sdl::Geometry2D::line_intersects_line(const Vector2 &from_a, const Vector2 &dir_a, const Vector2 &from_b, const Vector2 &dir_b) {
	// See http://paulbourke.net/geometry/pointlineplane/

	const real_t denom = dir_b.y * dir_a.x - dir_b.x * dir_a.y;
	if (Math::is_zero_approx(denom))
		return std::nullopt;

	const Vector2 v = from_a - from_b;
	const real_t t = (dir_b.x * v.y - dir_b.y * v.x) / denom;
	return std::optional<Vector2>(from_a + (dir_a * t));
}

bool sdl::Geometry2D::is_direction_intersecting_direction(const Vector2 &dir_a, const Vector2 &dir_b) {
	const real_t denom = dir_b.y * dir_a.x - dir_b.x * dir_a.y;
	return !Math::is_zero_approx(denom);
}

bool sdl::Geometry2D::rect_intersects_circle(const Rect2 &rect, const real_t circle_radius, const Vector2 &circle_position) {
	const real_t circle_radius_squared = circle_radius * circle_radius;
	const bool position_intersection = circle_position.distance_to_squared(rect.get_position()) <= circle_radius_squared;
	const bool size_intersection = circle_position.distance_to_squared(rect.get_position() + rect.get_size()) <= circle_radius_squared;
	return position_intersection || size_intersection;
}

sdl::Vector2 sdl::Geometry2D::rotate_point_around(const double rotation_degrees, const Vector2 &point, const Vector2 &center)  {
	real_t rotation_radians = Math::degrees_to_radians(rotation_degrees);
	Vector2 final_point = center - point;
	real_t x_rot = -(final_point.x * cos(rotation_radians)) + (final_point.y * cos(rotation_radians));
	real_t y_rot = -(final_point.x * sin(rotation_radians)) + (final_point.y * sin(rotation_radians));
	
	return Vector2(x_rot, y_rot);
}