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
	PhysicsWorld2D(const Vector2 &gravity = Vector2::ZERO);
	std::unique_ptr<b2World> &get_world();
};

}

#endif // !B2_INCLUDED