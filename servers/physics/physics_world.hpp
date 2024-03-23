#ifdef B2_INCLUDED
#pragma once

#include <core/math/vector2.hpp>

#include <memory>

class b2World;

namespace sdl {

class PhysicsWorld2D {
private:
	std::unique_ptr<b2World> b2_world;

public:
	int32_t velocity_iterations = 6;
	int32_t position_iterations = 2;

	PhysicsWorld2D(const Vector2f &gravity = Vector2f::ZERO(), const int32_t velocity_iterations = 6, const int32_t position_iterations = 2);
	constexpr const std::unique_ptr<b2World> &get_world() {
		return b2_world;
	}

	void step(const double delta) const;
};

}

#endif // !B2_INCLUDED