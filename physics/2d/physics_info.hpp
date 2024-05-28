/*  This file is part of the Toof Engine. */
/** @file physics_info.hpp */
/*
  BSD 3-Clause License

  Copyright (c) 2024-present, Stronkkey and Contributors

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
      list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <ratio>
#ifdef TOOF_PHYSICS_ENABLED

#pragma once

#ifndef TOOF_PHYSICS_PX_METER_RATIO
#define TOOF_PHYSICS_PX_METER_RATIO 100
#endif

#ifndef TOOF_DEFAULT_GRAVITY_X
#define TOOF_DEFAULT_GRAVITY_X 0
#endif

#ifndef TOOF_DEFAULT_GRAVITY_Y
#define TOOF_DEFAULT_GRAVITY_Y 9.8
#endif

#include <core/math/vector2.hpp>

namespace Toof {

#ifdef TOOF_PHYSICS_ENABLED
#define TOOF_DETAIL_PHYSICS_ENABLED true
#else
#define TOOF_DETOOF_DETAIL_PHYSICS_ENABLED false
#endif


struct PhysicsInfo {
public:
	PhysicsInfo() = delete;
	~PhysicsInfo() = delete;

	/**
	* @details @b true if physics are enabled or @b false if physics are disabled.
	*/
	static constexpr const bool is_physics_enabled = TOOF_DETAIL_PHYSICS_ENABLED;

	/**
	* @brief Gravity used by the PhysicsServer.
	* @details The x value equals to @b TOOF_DEFAULT_GRAVITY_X while the y value equals to @b TOOF_DEFAULT_GRAVITY_Y.
	*/
	static constexpr const Vector2f default_gravity = Vector2f(TOOF_DEFAULT_GRAVITY_X, TOOF_DEFAULT_GRAVITY_Y);

	/**
	* @brief The ratio of pixels to meters.
	* @details The numerator is usually 1 while the denominator is equals to @b TOOF_PHYSICS_PX_METER_RATIO.
	*/
	using px_to_meter_ratio = std::ratio<1, TOOF_PHYSICS_PX_METER_RATIO>;
};

}

#endif