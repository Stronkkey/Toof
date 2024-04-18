#include <core/math/transform2d.hpp>

#ifdef B2_INCLUDED
#include <box2d/b2_math.h>
#endif

#include <core/string/string_def.hpp>
#include <stringify/format.hpp>

using namespace sdl;

const Transform2D Transform2D::IDENTITY = Transform2D(Angle::ZERO_ROTATION(), 0, 0, 1, 1);

#ifdef B2_INCLUDED

Transform2D::Transform2D(const b2Transform &b2_transform): rotation(Angle::from_radians(b2_transform.q.GetAngle())), origin(b2_transform.p), scale(Vector2(1, 1)) {
}

b2Transform Transform2D::to_b2_transform() const {
	return b2Transform(origin.to_b2_vec2(), b2Rot(rotation.get_angle_radians()));
}

#endif

Transform2D::operator String() const {
	return S_FORMAT("[Scale: ({}, {}), Origin: ({}, {}), Rotation: {}]", scale.x, scale.y, origin.x, origin.y, rotation);
}
