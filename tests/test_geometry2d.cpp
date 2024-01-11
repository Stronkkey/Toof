#include <core/utility_functions.hpp>
#include <core/math/geometry2d.hpp>
#include <tests/test_geometry2d.hpp>

using sdl::Vector2;
using sdl::Math::is_equal_approx;

#define LAZY_POINT_COMPARE(point1, point2) ;

bool compare_point(const Vector2 &point1, const Vector2 &point2) {
	if (is_equal_approx(point1, point2))
		return true;
}

bool point_rotation() {
	Vector2 point1 = sdl::Geometry2D::rotate_point_around(90, Vector2(100, 0)); 
	Vector2 point2 = sdl::Geometry2D::rotate_point_around(45, Vector2(100, 0)); 
	Vector2 point3 = sdl::Geometry2D::rotate_point_around(180, Vector2(100, 100)); 
	Vector2 point4 = sdl::Geometry2D::rotate_point_around(250, Vector2(-20, 500)); 
	return is_equal_approx(point1, Vector2(0, -100)) &&
	    is_equal_approx(point2, Vector2(-70.71068, -70.71068)) &&
	    is_equal_approx(point3, Vector2(-100, 2-100)) &&
	    is_equal_approx(point4, Vector2(-476.6867, 152.2162));
}

bool sdl::Tests::test_geometry2d() {
	return point_rotation();
}