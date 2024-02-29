#ifdef B2_INCLUDED

#include <servers/physics/physics_world.hpp>

#include <box2d/b2_world.h>

sdl::PhysicsWorld2D::PhysicsWorld2D(const Vector2f &gravity, const int32_t velocity_iterations, const int32_t position_iterations) {
	b2_world = std::make_unique<b2World>(gravity.to_b2_vec2());
	this->velocity_iterations = velocity_iterations;
	this->position_iterations = position_iterations;
}

void sdl::PhysicsWorld2D::step(const double delta) const {
	b2_world->Step(delta, velocity_iterations, position_iterations);
}

#endif // !B2_INCLUDED