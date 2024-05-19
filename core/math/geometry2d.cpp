#include <core/math/geometry2d.hpp>
#include <core/math/rect2.hpp>

bool Toof::Geometry2D::rect_intersects_circle(const Rect2f &rect, const real circle_radius, const Vector2f &circle_position) {
	const real circle_radius_squared = circle_radius * circle_radius;
	const bool position_intersection = circle_position.distance_to_squared(rect.get_position()) <= circle_radius_squared;
	const bool size_intersection = circle_position.distance_to_squared(rect.get_position() + rect.get_size()) <= circle_radius_squared;
	return position_intersection || size_intersection;
}

Toof::Vector2f Toof::Geometry2D::rotate_point_around(const double rotation_degrees, const Vector2f &point)  {
	real rotation_radians = Math::degrees_to_radians(rotation_degrees);
	real x_rot = -(point.x * cos(rotation_radians)) + (point.y * cos(rotation_radians));
	real y_rot = -(point.x * sin(rotation_radians)) + (point.y * sin(rotation_radians));
	
	return Vector2f(x_rot, y_rot);
}