#include <core/utility_functions.hpp>
#include <core/math/vector2.hpp>
#include <core/math/rect2.hpp>
#include <core/math/transform2d.hpp>

#include <SDL_timer.h>

#include <iostream>

using namespace sdl;

real_t UtilityFunctions::get_passed_time() {
	real_t time = SDL_GetTicks64();
	time *= 0.001;
	return time;
}

void UtilityFunctions::print(const std::string &string) {
	std::cout << string + "\n";
}

void UtilityFunctions::prints(const std::string &string) {
	std::cout << string + "\n";
}

bool UtilityFunctions::is_equal_approx(const real_t left, const real_t right) {
	return left >= (right - EPSILON) && left <= (right + EPSILON);
}

bool UtilityFunctions::is_equal_approx(const Vector2 &left, const Vector2 &right) {
	return is_equal_approx(left.x, right.x) && is_equal_approx(left.y, right.y);
}

bool UtilityFunctions::is_equal_approx(const Rect2 &left, const Rect2 &right) {
	return is_equal_approx(left.get_position(), right.get_position()) && is_equal_approx(left.get_size(), right.get_size());
}

bool UtilityFunctions::is_equal_approx(const Transform2D &left, const Transform2D &right) {
	return is_equal_approx(left.origin, right.origin) && is_equal_approx(left.rotation, right.rotation) && is_equal_approx(left.scale, right.scale);
}

bool UtilityFunctions::is_zero_approx(const real_t number) {
	return number >= (0.0 - EPSILON) && number <= (0.0 + EPSILON);
}

bool UtilityFunctions::is_zero_approx(const Vector2 &vector2) {
	return is_zero_approx(vector2.x) && is_zero_approx(vector2.y);
}

bool UtilityFunctions::is_zero_approx(const Rect2 &rect2) {
	return is_zero_approx(rect2.get_position()) && is_zero_approx(rect2.get_size());
}

bool UtilityFunctions::is_zero_approx(const Transform2D &transform2d) {
	return is_zero_approx(transform2d.rotation) && is_zero_approx(transform2d.origin) && is_zero_approx(transform2d.scale);
}