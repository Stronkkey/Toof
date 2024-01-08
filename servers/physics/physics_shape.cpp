#include <core/math/geometry2d.hpp>
#include <servers/physics/physics_body.hpp>
#include <servers/physics/physics_shape.hpp>

bool sdl::Physics::box_shape_intersects_circle(const std::shared_ptr<PhysicsShape> &box_shape, const std::shared_ptr<PhysicsShape> &circle_shape) {
	const Rect2 box_rect = box_shape_get_rect(box_shape);
	const real_t circle_radius = circle_shape_get_radius(circle_shape);
	const Vector2 circle_position = shape_get_transform(circle_shape).origin;

	return Geometry2D::rect_intersects_circle(box_rect, circle_radius, circle_position);
}

bool sdl::Physics::box_shape_intersects_rect(const std::shared_ptr<PhysicsShape> &box_shape, const std::shared_ptr<PhysicsShape> &right_box_shape) {
	const Rect2 box_rect = box_shape_get_rect(box_shape);
	const Rect2 right_box_rect = box_shape_get_rect(right_box_shape);

	return box_rect.intersects(right_box_rect);
}

bool sdl::Physics::circle_shape_intersects_circle(const std::shared_ptr<PhysicsShape> &circle_shape, const std::shared_ptr<PhysicsShape> &right_circle_shape) {
	const real_t circle_radius = circle_shape_get_radius(circle_shape);
	const Vector2 circle_position = shape_get_transform(circle_shape).origin;
	const real_t right_circle_radius = circle_shape_get_radius(right_circle_shape);
	const Vector2 right_circle_position = shape_get_transform(right_circle_shape).origin;

	return Geometry2D::are_circles_intersecting(circle_radius, circle_position, right_circle_radius, right_circle_position);
}

sdl::Transform2D sdl::Physics::shape_get_transform(const std::shared_ptr<PhysicsShape> &shape) {
	return shape->body.expired() ? shape->local_transform : shape->local_transform * shape->body.lock()->transform;
}

bool sdl::Physics::shape_intersects_shape(const std::shared_ptr<PhysicsShape> &left_shape, const std::shared_ptr<PhysicsShape> &right_shape) {
	switch (left_shape->type) {
		case PHYSICS_SHAPE_TYPE_BOX:
			return box_shape_intersect_shape(left_shape, right_shape);
		case PHYSICS_SHAPE_TYPE_CIRCLE:
			return circle_shape_intersect_shape(left_shape, right_shape);
		default:
			return false;
	}
}

bool sdl::Physics::box_shape_intersect_shape(const std::shared_ptr<PhysicsShape> &box_shape, const std::shared_ptr<PhysicsShape> &shape) {
	switch (shape->type) {
		case PHYSICS_SHAPE_TYPE_BOX:
			return box_shape_intersects_rect(box_shape, shape);
		case PHYSICS_SHAPE_TYPE_CIRCLE:
			return box_shape_intersects_circle(box_shape, shape);
		default:
			return false;
	}
}

sdl::Rect2 sdl::Physics::box_shape_get_rect(const std::shared_ptr<PhysicsShape> &box_shape) {
	return box_shape->box.rect * shape_get_transform(box_shape);
}

bool sdl::Physics::circle_shape_intersect_shape(const std::shared_ptr<PhysicsShape> &circle_shape, const std::shared_ptr<PhysicsShape> &shape) {
	switch (shape->type) {
		case PHYSICS_SHAPE_TYPE_BOX:
			return box_shape_intersects_circle(shape, circle_shape);
		case PHYSICS_SHAPE_TYPE_CIRCLE:
			return circle_shape_intersects_circle(circle_shape, shape);
		default:
			return false;
	}
}

sdl::real_t sdl::Physics::circle_shape_get_radius(const std::shared_ptr<PhysicsShape> &circle_shape) {
	return circle_shape->circle.radius * shape_get_transform(circle_shape).scale.x;
}