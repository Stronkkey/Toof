#pragma once

#include <core/math/math_defs.hpp>

#include <unordered_map>

namespace sdl {

struct PhysicsBody;

class PhysicsServer2D {

private:
	std::unordered_map<uid, PhysicsBody> bodies;
};

}