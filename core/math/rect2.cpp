#include <core/math/rect2.hpp>
#include <core/math/transform2d.hpp>

using namespace sdl;

Rect2f sdl::rect2f_add_transform(const Rect2f &rect2f, const Transform2D &transform2d) {
	Rect2f rect = rect2f;
	rect.x += transform2d.origin.x;
	rect.y += transform2d.origin.y;
	rect.w *= transform2d.scale.x;
	rect.h *= transform2d.scale.y;
	return rect;
}