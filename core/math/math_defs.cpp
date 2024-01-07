#include <core/math/math_defs.hpp>

#include <core/math/transform2d.hpp>
#include <core/math/rect2.hpp>

sdl::real_t sdl::Math::radians_to_degrees(const real_t rotation_radians) {
	return rotation_radians * DEGREES_RADIAN_SCALAR;
}

sdl::real_t sdl::Math::degrees_to_radians(const real_t rotation_degrees) {
	return rotation_degrees / DEGREES_RADIAN_SCALAR;
}

bool sdl::Math::is_equal_approx(const real_t left, const real_t right) {
	return left >= (right - CMP_EPSILON) && left <= (right + CMP_EPSILON);
}

bool sdl::Math::is_equal_approx(const Vector2 &left, const Vector2 &right) {
	return is_equal_approx(left.x, right.x) && is_equal_approx(left.y, right.y);
}

bool sdl::Math::is_equal_approx(const Rect2 &left, const Rect2 &right) {
	return is_equal_approx(left.get_position(), right.get_position()) && is_equal_approx(left.get_size(), right.get_size());
}

bool sdl::Math::is_equal_approx(const Transform2D &left, const Transform2D &right) {
	return is_equal_approx(left.origin, right.origin) && is_equal_approx(left.rotation, right.rotation) && is_equal_approx(left.scale, right.scale);
}

bool sdl::Math::is_zero_approx(const real_t number) {
	return number >= (0.0 - CMP_EPSILON) && number <= (0.0 + CMP_EPSILON);
}

bool sdl::Math::is_zero_approx(const Vector2 &vector2) {
	return is_zero_approx(vector2.x) && is_zero_approx(vector2.y);
}

bool sdl::Math::is_zero_approx(const Rect2 &rect2) {
	return is_zero_approx(rect2.get_position()) && is_zero_approx(rect2.get_size());
}

bool sdl::Math::is_zero_approx(const Transform2D &transform2d) {
	return is_zero_approx(transform2d.rotation) && is_zero_approx(transform2d.origin) && is_zero_approx(transform2d.scale);
}