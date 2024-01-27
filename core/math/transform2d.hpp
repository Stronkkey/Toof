#pragma once

#include <core/math/vector2.hpp>

#ifdef B2_INCLUDED
struct b2Transform;
#endif

namespace sdl {

struct Transform2D {
	Transform2D();
	Transform2D(const double new_rotation, const Vector2 &new_origin, const Vector2 &new_scale);
	Transform2D(const double new_rotation, const real_t origin_x, const real_t origin_y, const real_t scale_x, const real_t scale_y);
	Transform2D(const Transform2D &transform2d);
	#ifdef B2_INCLUDED
	Transform2D(const b2Transform &b2_transform);
	#endif

	double rotation;
	Vector2 origin;
	Vector2 scale;

	bool operator==(const Transform2D &right) const;
	bool operator!() const;

	Transform2D operator*(const Transform2D &right) const;

	#ifdef B2_INCLUDED
	[[nodiscard]] b2Transform to_b2_transform() const;
	#endif
	[[nodiscard]] std::string to_string() const;

	void operator=(const Transform2D &right);
	void operator*=(const Transform2D &right);

	static const Transform2D IDENTITY;
};

}
