#ifdef B2_INCLUDED

#include <servers/physics/physics_world.hpp>

#include <box2d/b2_world.h>

sdl::PhysicsWorld2D::PhysicsWorld2D(const Vector2 &gravity) {
	b2_world = std::make_unique<b2World>(gravity.to_b2_vec2());
}

std::unique_ptr<b2World> &sdl::PhysicsWorld2D::get_world() {
	return b2_world;
}

#endif // !B2_INCLUDED