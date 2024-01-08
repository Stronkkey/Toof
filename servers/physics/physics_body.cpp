#include <servers/physics/physics_body.hpp>
#include <servers/physics/physics_shape.hpp>

void sdl::Physics::rigid_body_physics_tick(const std::shared_ptr<PhysicsBody> &body, const double delta) {
	(void)body;
	(void)delta;
}

void sdl::Physics::static_body_physics_tick(const std::shared_ptr<PhysicsBody> &body, const double delta) {
	(void)body;
	(void)delta;
}

void sdl::Physics::area_body_physics_tick(const std::shared_ptr<PhysicsBody> &body, const double delta) {
	(void)body;
	(void)delta;
}

void sdl::Physics::physics_body_physics_tick(const std::shared_ptr<PhysicsBody> &body, const double delta) {
	switch (body->type) {
		case PHYSICS_BODY_TYPE_AREA:
			Physics::area_body_physics_tick(body, delta);
			break;
		case PHYSICS_BODY_TYPE_RIGID:
			Physics::rigid_body_physics_tick(body, delta);
			break;
		case PHYSICS_BODY_TYPE_STATIC:
			Physics::static_body_physics_tick(body, delta);
			break;
		default:
			break;
	}
}

bool physics_shape_collison(const std::weak_ptr<sdl::PhysicsShape> &left_shape, const std::weak_ptr<sdl::PhysicsShape> &right_shape) {
	if (left_shape.expired() || right_shape.expired())
		return false;
	return sdl::Physics::shape_intersects_shape(left_shape.lock(), right_shape.lock());
}

bool loop_through_body_physics_shape(const std::weak_ptr<sdl::PhysicsShape> &shape, const std::shared_ptr<sdl::PhysicsBody> &body) {
	for (const std::weak_ptr<sdl::PhysicsShape> &right_shape: body->shapes)
		if (physics_shape_collison(shape, right_shape))
			return true;

	return false;
}

bool sdl::Physics::physics_body_collides_against(const std::shared_ptr<PhysicsBody> &body, const std::shared_ptr<PhysicsBody> &right_body) {
	for (const std::weak_ptr<PhysicsShape> &shape: body->shapes)
		if (loop_through_body_physics_shape(shape, right_body))
			return true;

	return false;
}