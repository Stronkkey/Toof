#include <core/math/math_defs.hpp>

#include <core/math/transform2d.hpp>
#include <core/math/rect2.hpp>

bool sdl::Math::is_equal_approx(const Vector2 &left, const Vector2 &right) {
	return is_equal_approx(left.x, right.x) && is_equal_approx(left.y, right.y);
}

bool sdl::Math::is_equal_approx(const Rect2 &left, const Rect2 &right) {
	return is_equal_approx(left.get_position(), right.get_position()) && is_equal_approx(left.get_size(), right.get_size());
}

bool sdl::Math::is_equal_approx(const Transform2D &left, const Transform2D &right) {
	return is_equal_approx(left.origin, right.origin) && is_equal_approx(left.rotation.get_angle_degrees(), right.rotation.get_angle_degrees()) && is_equal_approx(left.scale, right.scale);
}

bool sdl::Math::is_zero_approx(const Vector2 &vector2) {
	return is_zero_approx(vector2.x) && is_zero_approx(vector2.y);
}

bool sdl::Math::is_zero_approx(const Rect2 &rect2) {
	return is_zero_approx(rect2.get_position()) && is_zero_approx(rect2.get_size());
}

bool sdl::Math::is_zero_approx(const Transform2D &transform2d) {
	return is_zero_approx(transform2d.rotation.get_angle_degrees()) && is_zero_approx(transform2d.origin) && is_zero_approx(transform2d.scale);
}