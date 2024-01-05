#pragma once

#include <core/math/rect2.hpp>

namespace sdl {

enum PhysicsShapeType {
	PHYSICS_SHAPE_TYPE_BOX,
	PHYSICS_SHAPE_TYPE_CIRCLE
};

struct PhysicsShape {
	PhysicsShapeType type;

	bool collides_against(const PhysicsShape *shape) const;
};

struct PhysicsShapeBox : public PhysicsShape {
	Rect2 rect;

	bool _collides_against(const PhysicsShape *shape) const;
};

struct PhysicsShapeCircle : public PhysicsShape {
	real_t radius;

	bool _collides_against(const PhysicsShape *shape) const;
};

}