#pragma once

#include <core/math/rect2.hpp>
#include <core/math/transform2d.hpp>

#include <memory>

class b2Shape;

namespace Toof {

struct PhysicsBody;

struct PhysicsShape {
	b2Shape *shape;
};

}