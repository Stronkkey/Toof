#include <servers/physics/physics_body.hpp>

void sdl::PhysicsBody::physics_tick(const double delta) {
}

bool sdl::PhysicsBody::collides_against(const std::shared_ptr<PhysicsBody> &physics_body) const {
	return false;
}