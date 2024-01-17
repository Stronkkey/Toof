#ifdef B2_INCLUDED

#pragma once

#ifndef PHYSICS_PX_METER_RATIO
#define PHYSICS_PX_METER_RATIO 100
#endif

#ifndef DEFAULT_GRAVITY_X
#define DEFAULT_GRAVITY_X 0
#endif

#ifndef DEFAULT_GRAVITY_Y
#define DEFAULT_GRAVITY_Y 9.8
#endif

#include <ratio>

#include <core/math/vector2.hpp>

namespace sdl {

namespace Physics {

const Vector2 default_gravity = Vector2(DEFAULT_GRAVITY_X, DEFAULT_GRAVITY_Y);
const std::ratio px_to_meter_ratio = std::ratio<1, PHYSICS_PX_METER_RATIO>();
#ifdef B2_INCLUDED
const bool physics_enabled = true;
#else
const bool physics_enabled = false;
#endif

}

}

#endif // !B2_INCLUDED