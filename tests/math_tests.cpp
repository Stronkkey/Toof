#include <tests/math_tests.hpp>

#include <core/math/math_defs.hpp>
#include <core/math/transform2d.hpp>
#include <core/math/rect2.hpp>
#include <core/math/color.hpp>

using namespace Toof::Tests;

using Transform2D = Toof::Transform2D;
using ColorV = Toof::ColorV;

using Toof::Math::CMP_EPSILON;
using Toof::Math::PI;
using Toof::Math::radians_to_degrees;
using Toof::Math::degrees_to_radians;
using Toof::Math::is_zero_approx;
using Toof::Math::is_equal_approx;

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

	return true;
}