#pragma once

#include <core/math/vector2.hpp>
#include <core/math/angle.hpp>

#ifdef B2_INCLUDED
struct b2Transform;
#endif

namespace sdl {

struct Transform2D {
	constexpr Transform2D();
	constexpr Transform2D(const Angle rotation, const Vector2 &new_origin, const Vector2 &new_scale);
	constexpr Transform2D(const Angle rotation, const real_t origin_x, const real_t origin_y, const real_t scale_x, const real_t scale_y);
	constexpr Transform2D(const Transform2D &transform2d);
	#ifdef B2_INCLUDED
	Transform2D(const b2Transform &b2_transform);
	#endif

	Angle rotation;
	Vector2 origin;
	Vector2 scale;

	constexpr bool operator==(const Transform2D &right) const;
	constexpr bool operator!() const;

	constexpr Transform2D operator*(const Transform2D &right) const;

	#ifdef B2_INCLUDED
	[[nodiscard]] b2Transform to_b2_transform() const;
	#endif
	[[nodiscard]] std::string to_string() const;

	constexpr void operator=(const Transform2D &right);
	constexpr void operator*=(const Transform2D &right);

	static const Transform2D IDENTITY;
};

constexpr Transform2D::Transform2D(): rotation(0.0), origin(Vector2()), scale(Vector2()) {
}

constexpr Transform2D::Transform2D(const Angle rotation, const Vector2 &new_origin, const Vector2 &new_scale): rotation(rotation), origin(new_origin), scale(new_scale) {
}

constexpr Transform2D::Transform2D(const Angle rotation, const real_t origin_x, const real_t origin_y, const real_t scale_x, const real_t scale_y):
    rotation(rotation),
    origin(Vector2(origin_x, origin_y)),
    scale(Vector2(scale_x, scale_y)) {
}

constexpr Transform2D::Transform2D(const Transform2D &transform2d): rotation(transform2d.rotation), origin(transform2d.origin), scale(transform2d.scale) {
}

constexpr bool Transform2D::operator==(const Transform2D &right) const {
	return origin == right.origin && rotation == right.rotation;
}

constexpr bool Transform2D::operator!() const {
	return origin == Vector2::ZERO || rotation == 0.0;
}

constexpr Transform2D Transform2D::operator*(const Transform2D &right) const {
	return Transform2D(rotation + right.rotation, origin + right.origin, scale * right.scale);
}

constexpr void Transform2D::operator=(const Transform2D &right) {
	origin = right.origin;
	rotation = right.rotation;
	scale = right.scale;
}

constexpr void Transform2D::operator*=(const Transform2D &right) {
	origin += right.origin;
	rotation += right.rotation;
	scale *= right.scale;
}


}
