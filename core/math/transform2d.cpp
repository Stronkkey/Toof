#include "core/math/math_defs.hpp"
#include <box2d/b2_math.h>
#include <core/math/transform2d.hpp>

using namespace sdl;

const Transform2D Transform2D::IDENTITY = Transform2D(0, 0, 0, 1, 1);

Transform2D::Transform2D(): rotation(0.0), origin(Vector2::ZERO), scale(Vector2::ONE) {
}

Transform2D::Transform2D(const double new_rotation, const Vector2 &new_origin, const Vector2 &new_scale): rotation(new_rotation), origin(new_origin), scale(new_scale) {
}

Transform2D::Transform2D(const double new_rotation, const real_t origin_x, const real_t origin_y, const real_t scale_x, const real_t scale_y):
    rotation(new_rotation),
    origin(Vector2(origin_x, origin_y)),
    scale(Vector2(scale_x, scale_y)) {
}

Transform2D::Transform2D(const Transform2D &transform2d): rotation(transform2d.rotation), origin(transform2d.origin), scale(transform2d.scale) {
}

bool Transform2D::operator==(const Transform2D &right) const {
	return origin == right.origin && rotation == right.rotation;
}

bool Transform2D::operator!() const {
	return origin == Vector2::ZERO || rotation == 0.0;
}

Transform2D Transform2D::operator*(const Transform2D &right) const {
	return Transform2D(rotation + right.rotation, origin + right.origin, scale * right.scale);
}

#ifdef B2_INCLUDED
b2Transform Transform2D::to_b2_transform() const {
	return b2Transform(origin.to_b2_vec2(), b2Rot(Math::degrees_to_radians(rotation)));
}
#endif

void Transform2D::operator=(const Transform2D &right) {
	origin = right.origin;
	rotation = right.rotation;
	scale = right.scale;
}

void Transform2D::operator*=(const Transform2D &right) {
	origin += right.origin;
	rotation += right.rotation;
	scale *= right.scale;
}
