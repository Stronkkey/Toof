#pragma once

#include <core/math/math_defs.hpp>

#include <unordered_map>
#include <memory>

namespace sdl {

struct PhysicsWorld2D;

class PhysicsServer2D {

private:
	std::unique_ptr<PhysicsWorld2D> world;

public:
	PhysicsServer2D();
	
	void tick(const double delta);

};

}