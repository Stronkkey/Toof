#include <box2d/b2_math.h>
#include <core/math/transform2d.hpp>
#include <core/string_funcs.hpp>

using namespace sdl;

const Transform2D Transform2D::IDENTITY = Transform2D(Angle(), 0, 0, 0, 0);

#ifdef B2_INCLUDED

Transform2D::Transform2D(const b2Transform &b2_transform): rotation(Angle::from_radians(b2_transform.q.GetAngle())), origin(b2_transform.p), scale(Vector2(1, 1)) {
}

b2Transform Transform2D::to_b2_transform() const {
	return b2Transform(origin.to_b2_vec2(), b2Rot(rotation.get_angle_radians()));
}
#endif

String Transform2D::to_string() const {
	return vformat("[Scale: ({}, {}), Origin: ({}, {}), Rotation: {}]", scale.x, scale.y, origin.x, origin.y, rotation.to_string());
}

Transform2D::operator String() const {
	return vformat("[Scale: ({}, {}), Origin: ({}, {}), Rotation: {}]", scale.x, scale.y, origin.x, origin.y, rotation.to_string());
}
