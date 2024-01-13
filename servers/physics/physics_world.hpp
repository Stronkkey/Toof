#pragma once

#include <memory>

class b2World;

namespace sdl {

class PhysicsWorld2D {
private:
	std::unique_ptr<b2World> b2_world;

public:
	PhysicsWorld2D();
	const std::unique_ptr<b2World> &get_world();
};

}