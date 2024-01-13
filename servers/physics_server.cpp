#include <servers/physics/physics_world.hpp>
#include <servers/physics/physics_body.hpp>
#include <servers/physics/physics_shape.hpp>
#include <servers/physics_server.hpp>

#include <box2d/b2_world.h>

sdl::PhysicsServer2D::PhysicsServer2D() {
	world = std::make_unique<PhysicsWorld2D>();
}

void sdl::PhysicsServer2D::tick(const double delta) {
	world->b2_world->Step(float timeStep, int32 velocityIterations, int32 positionIterations);
}
