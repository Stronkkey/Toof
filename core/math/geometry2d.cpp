#include <core/math/geometry2d.hpp>
#include <core/math/rect2.hpp>

bool sdl::Geometry2D::rect_intersects_circle(const Rect2f &rect, const real_t circle_radius, const Vector2f &circle_position) {
	const real_t circle_radius_squared = circle_radius * circle_radius;
	const bool position_intersection = circle_position.distance_to_squared(rect.get_position()) <= circle_radius_squared;
	const bool size_intersection = circle_position.distance_to_squared(rect.get_position() + rect.get_size()) <= circle_radius_squared;
	return position_intersection || size_intersection;
}

sdl::Vector2f sdl::Geometry2D::rotate_point_around(const double rotation_degrees, const Vector2f &point)  {
	real_t rotation_radians = Math::degrees_to_radians(rotation_degrees);
	real_t x_rot = -(point.x * cos(rotation_radians)) + (point.y * cos(rotation_radians));
	real_t y_rot = -(point.x * sin(rotation_radians)) + (point.y * sin(rotation_radians));
	
	return Vector2f(x_rot, y_rot);
}