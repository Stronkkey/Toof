#pragma once

#include <core/math/rect2.hpp>
#include <core/math/transform2d.hpp>

#include <memory>

namespace sdl {

struct PhysicsBody;

enum PhysicsShapeType {
	PHYSICS_SHAPE_TYPE_BOX,
	PHYSICS_SHAPE_TYPE_CIRCLE
};

struct PhysicsShapeBox {
	Rect2 rect;
};

struct PhysicsShapeCircle {
	real_t radius;
};

struct PhysicsShape {
	union {
		PhysicsShapeBox box;
		PhysicsShapeCircle circle;
	};

	PhysicsShapeType type;
	std::weak_ptr<PhysicsBody> body;
	Transform2D local_transform;
};

namespace Physics {

bool box_shape_intersects_circle(const std::shared_ptr<PhysicsShape> &box_shape, const std::shared_ptr<PhysicsShape> &circle_shape);
bool box_shape_intersects_rect(const std::shared_ptr<PhysicsShape> &box_shape, const std::shared_ptr<PhysicsShape> &right_box_shape);
bool circle_shape_intersects_circle(const std::shared_ptr<PhysicsShape> &circle_shape, const std::shared_ptr<PhysicsShape> &right_circle_shape);

Transform2D shape_get_transform(const std::shared_ptr<PhysicsShape> &shape);
bool shape_intersects_shape(const std::shared_ptr<PhysicsShape> &left_shape, const std::shared_ptr<PhysicsShape> &right_shape);

bool box_shape_intersect_shape(const std::shared_ptr<PhysicsShape> &box_shape, const std::shared_ptr<PhysicsShape> &shape);
Rect2 box_shape_get_rect(const std::shared_ptr<PhysicsShape> &box_shape);

bool circle_shape_intersect_shape(const std::shared_ptr<PhysicsShape> &circle_shape, const std::shared_ptr<PhysicsShape> &shape);
real_t circle_shape_get_radius(const std::shared_ptr<PhysicsShape> &circle_shape);

}

}