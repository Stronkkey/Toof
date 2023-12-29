#pragma once

#include <types/vector2.hpp>

namespace sdl {

struct Transform2D {
	Transform2D();
	Transform2D(const double new_rotation, const Vector2 &new_origin, const Vector2 &new_scale);
	Transform2D(const double new_rotation, const real_t origin_x, const real_t origin_y, const real_t scale_x, const real_t scale_y);
	Transform2D(const Transform2D &transform2d);

	double rotation;
	Vector2 origin;
	Vector2 scale;

	bool operator==(const Transform2D &right) const;
	bool operator!() const;

	Transform2D operator*(const Transform2D &right) const;

	void operator=(const Transform2D &right);
	void operator*=(const Transform2D &right);

	static const Transform2D IDENTITY;
};

}
