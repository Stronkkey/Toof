#ifdef B2_INCLUDED

#pragma once

#include <core/math/math_defs.hpp>

#include <memory>
#include <vector>

class b2Body;
class b2Shape;

namespace Toof {

struct PhysicsShape;
struct PhysicsWorld2D;

struct PhysicsBody {
	b2Body *body;
	uid world_uid;
};

}

#endif // !B2_INCLUDED