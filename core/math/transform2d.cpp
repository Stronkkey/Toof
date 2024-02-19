#include "core/math/math_defs.hpp"
#include <box2d/b2_math.h>
#include <core/math/transform2d.hpp>

using namespace sdl;

const Transform2D Transform2D::IDENTITY = Transform2D(0, 0, 0, 1, 1);

#ifdef B2_INCLUDED
Transform2D::Transform2D(const b2Transform &b2_transform): rotation(Math::radians_to_degrees(b2_transform.q.GetAngle())), origin(b2_transform.p), scale(Vector2::ONE) {
}

b2Transform Transform2D::to_b2_transform() const {
	return b2Transform(origin.to_b2_vec2(), b2Rot(rotation.get_angle_radians()));
}
#endif

std::string Transform2D::to_string() const {
	return "[Scale: " + scale.to_string() + ", Origin: " + origin.to_string() + ", Rotation: " + std::to_string(rotation.get_angle_degrees()) + " degrees" + "]";
}
