#ifdef B2_INCLUDED

#pragma once

#include <core/math/transform2d.hpp>

#include <memory>
#include <vector>

class b2Body;
class b2Shape;

namespace sdl {

struct PhysicsShape;
struct PhysicsWorld2D;


struct PhysicsBody {
	b2Body *body;
	std::weak_ptr<PhysicsWorld2D> world;

	void physics_tick(const double delta);
	bool collides_with(const std::shared_ptr<PhysicsBody> &body);
};

}

#endif // !B2_INCLUDED