#include <servers/physics/physics_world.hpp>

#include <box2d/b2_world.h>

sdl::PhysicsWorld2D::PhysicsWorld2D() {
	b2_world = std::make_unique<b2World>(b2Vec2());
}