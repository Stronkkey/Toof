#pragma once

#include <core/math/vector2.hpp>
#include <core/math/angle.hpp>

#ifdef B2_INCLUDED
struct b2Transform;
#endif

namespace sdl {

struct Transform2D {
	constexpr Transform2D();
	constexpr Transform2D(const Angle rotation, const Vector2f &new_origin, const Vector2f &new_scale);
	constexpr Transform2D(const Angle rotation, const real origin_x, const real origin_y, const real scale_x, const real scale_y);
	constexpr Transform2D(const Transform2D &transform2d);
	#ifdef B2_INCLUDED
	Transform2D(const b2Transform &b2_transform);
	#endif

	Angle rotation;
	Vector2f origin;
	Vector2f scale;

	constexpr bool operator==(const Transform2D &right) const;
	constexpr bool operator!() const;

	constexpr Transform2D operator*(const Transform2D &right) const;

	#ifdef B2_INCLUDED
	[[nodiscard]] b2Transform to_b2_transform() const;
	#endif

	[[nodiscard]] operator String() const;
	[[nodiscard]] constexpr operator bool() const {
		return true;
	}

	constexpr void operator=(const Transform2D &right);
	constexpr void operator*=(const Transform2D &right);

	static const Transform2D IDENTITY;

	template<class Archive>
	void serialize(Archive &archive) {
		archive(REAL_IS_DOUBLE ? uint8_t(0x1) : uint8_t(0x0), rotation.get_angle_degrees(), origin.x, origin.y, scale.x, scale.y);
	}
};

constexpr Transform2D::Transform2D(): rotation(Angle::ZERO_ROTATION()), origin(), scale() {
}

constexpr Transform2D::Transform2D(const Angle rotation, const Vector2f &new_origin, const Vector2f &new_scale): rotation(rotation), origin(new_origin), scale(new_scale) {
}

constexpr Transform2D::Transform2D(const Angle rotation, const real origin_x, const real origin_y, const real scale_x, const real scale_y):
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
	return origin || rotation.get_angle_degrees();
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
