#pragma once

#include <core/math/transform2d.hpp>

#include <memory>
#include <vector>

namespace sdl {

struct PhysicsShape;

enum PhysicsBodyTypes {
	PHYSICS_BODY_TYPE_STATIC,
	PHYSICS_BODY_TYPE_RIGID,
	PHYSICS_BODY_TYPE_AREA
};

struct PhysicsBody {
	PhysicsBodyTypes type;
	Transform2D transform;
	std::vector<std::weak_ptr<PhysicsShape>> shapes;
};

namespace Physics {

void rigid_body_physics_tick(const std::shared_ptr<PhysicsBody> &body, const double delta);
void static_body_physics_tick(const std::shared_ptr<PhysicsBody> &body, const double delta);
void area_body_physics_tick(const std::shared_ptr<PhysicsBody> &body, const double delta);
void physics_body_physics_tick(const std::shared_ptr<PhysicsBody> &body, const double delta);
bool physics_body_collides_against(const std::shared_ptr<PhysicsBody> &body, const std::shared_ptr<PhysicsBody> &right_body);

};

}