#include <tests/math_tests.hpp>

#include <core/math/math_defs.hpp>
#include <core/math/transform2d.hpp>
#include <core/math/rect2.hpp>
#include <core/math/color.hpp>

using namespace sdl::Tests;

using Transform2D = sdl::Transform2D;
using Color = sdl::Color;

using sdl::Math::CMP_EPSILON;
using sdl::Math::PI;
using sdl::Math::radians_to_degrees;
using sdl::Math::degrees_to_radians;
using sdl::Math::is_zero_approx;
using sdl::Math::is_equal_approx;

constexpr Transform2D add_transform(const Transform2D &left, const Transform2D &right) {
	Transform2D transform;
	transform.origin = (left.origin + right.origin);
	transform.rotation = (left.rotation + right.rotation);
	transform.scale = (left.scale + right.scale);
	return transform;
}

constexpr Transform2D subtract_transform(const Transform2D &left, const Transform2D &right) {
	Transform2D transform;
	transform.origin = (left.origin - right.origin);
	transform.rotation = (left.rotation - right.rotation);
	transform.scale = (left.scale - right.scale);
	return transform;
}

bool ColorTest::_test() {
//	TEST_CASE(Color(182, 44, 125, 157).blend(Color(241, 208, 27, 23)) == Color(193, 73, 107, 168));
	return true;
}

bool MathTest::_test() {
	TEST_CASE(radians_to_degrees(PI) == 180.0);
	TEST_CASE(degrees_to_radians(180.0) == PI);

	TEST_CASE(is_zero_approx(0.0 - CMP_EPSILON));
	TEST_CASE(is_zero_approx(0.0 + CMP_EPSILON));
	TEST_CASE(is_equal_approx(1, 1.0 - CMP_EPSILON));
	TEST_CASE(is_equal_approx(1, 1.0 + CMP_EPSILON));

	constexpr const Vector2 v2epsilon = Vector2(CMP_EPSILON, CMP_EPSILON);
	TEST_CASE(is_zero_approx(Vector2::ZERO - v2epsilon));
	TEST_CASE(is_zero_approx(Vector2::ZERO + v2epsilon));
	TEST_CASE(is_equal_approx(Vector2::ONE, Vector2::ONE - v2epsilon));
	TEST_CASE(is_equal_approx(Vector2::ONE, Vector2::ONE + v2epsilon));

	constexpr const Rect2 r2epsilon = Rect2(CMP_EPSILON, CMP_EPSILON, CMP_EPSILON, CMP_EPSILON);
	TEST_CASE(is_zero_approx(Rect2::EMPTY - r2epsilon));
	TEST_CASE(is_zero_approx(Rect2::EMPTY + r2epsilon));
	TEST_CASE(is_equal_approx(Rect2::ONE, Rect2::ONE - r2epsilon));
	TEST_CASE(is_equal_approx(Rect2::ONE, Rect2::ONE + r2epsilon));

	constexpr const Transform2D trans_epsilon = Transform2D(CMP_EPSILON, CMP_EPSILON, CMP_EPSILON, CMP_EPSILON, CMP_EPSILON);
	constexpr const Transform2D trans_zero = Transform2D(0, 0, 0, 0, 0);
	constexpr const Transform2D trans_one = Transform2D(1, 1, 1, 1, 1);
	TEST_CASE(is_zero_approx(subtract_transform(trans_zero, trans_epsilon)))
	TEST_CASE(is_zero_approx(add_transform(trans_zero, trans_epsilon)));
	TEST_CASE(is_equal_approx(trans_one, subtract_transform(trans_one, trans_epsilon)));
	TEST_CASE(is_equal_approx(trans_one, add_transform(trans_one, trans_epsilon)));

	return true;
}