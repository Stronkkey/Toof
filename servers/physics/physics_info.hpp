#ifdef B2_INCLUDED

#pragma once

#ifndef __PHYSICS_PX_METER_RATIO__
#define __PHYSICS_PX_METER_RATIO__ 100
#endif

#ifndef __DEFAULT_GRAVITY_X__
#define __DEFAULT_GRAVITY_X__ 0
#endif

#ifndef __DEFAULT_GRAVITY_Y__
#define __DEFAULT_GRAVITY_Y__ 9.8
#endif

#include <ratio>

#include <core/math/vector2.hpp>

namespace Toof {

namespace Physics {

const Vector2f default_gravity = Vector2f(__DEFAULT_GRAVITY_X__, __DEFAULT_GRAVITY_Y__);
const std::ratio px_to_meter_ratio = std::ratio<1, __PHYSICS_PX_METER_RATIO__>();
#ifdef B2_INCLUDED
const bool physics_enabled = true;
#else
const bool physics_enabled = false;
#endif

}

}

#endif // !B2_INCLUDED