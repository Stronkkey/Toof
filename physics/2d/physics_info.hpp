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
#pragma once

#include <core/math/math_defs.hpp>
#include <physics/physics_features.hpp>

#if TOOF_PHYSICS_ENABLED

#define TOOF_DEFAULT_GRAVITY (Vector2f(TOOF_DEFAULT_GRAVITY_X, TOOF_DEFAULT_GRAVITY_Y))

namespace Toof {

#if TOOF_PHYSICS_ENABLED
#define TOOF_DETAIL_PHYSICS_ENABLED true
#else
#define TOOF_DETAIL_PHYSICS_ENABLED false
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
	* @brief Default gravity strength (x axis) used by the PhysicsServer.
	* @details This value may be changed by defining the @b TOOF_DEFAULT_GRAVITY_X macro.
	*/
	static constexpr real default_gravity_x = TOOF_DEFAULT_GRAVITY_X;

	/**
	* @brief Default gravity strength (y axis) used by the PhysicsServer. Equal to @b TOOF_DEFAULT_GRAVITY_Y macro.
	* @details This value may be changed by defining the @b TOOF_DEFAULT_GRAVITY_Y macro.
	*/
	static constexpr real default_gravity_y = TOOF_DEFAULT_GRAVITY_Y;
};

}

#endif