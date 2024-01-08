#pragma once

#include <core/math/math_defs.hpp>

#include <unordered_map>
#include <memory>

namespace sdl {

struct PhysicsBody;
struct PhysicsShape;

class PhysicsServer2D {

private:
	std::unordered_map<uid, std::shared_ptr<PhysicsBody>> bodies;
	std::unordered_map<uid, std::shared_ptr<PhysicsShape>> shapes;

public:
	void tick(const double delta);

};

}