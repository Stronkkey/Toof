/*  This file is part of the Toof Engine. */
/** @file b2_physics_world.hpp */
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
#ifdef TOOF_B2_ENABLED

#pragma once

#include <physics/2d/physics_world.hpp>

#include <box2d/b2_world.h>

namespace Toof {

class B2PhysicsWorld : public PhysicsWorld2D {
private:
	b2World world;
	int32_t velocity_iterations;
	int32_t position_iterations;
public:
	B2PhysicsWorld();
	~B2PhysicsWorld() = default;

	constexpr b2World &get_world() {
		return world;
	}

	constexpr const b2World &get_world() const {
		return world;
	}

	void set_velocity_iterations(int32_t velocity_iterations) override;
	int32_t get_velocity_iterations() const override;

	void set_position_iterations(int32_t position_iterations) override;
	int32_t get_position_iterations() const override;

	void set_gravity(const Vector2f &gravity) override;
	Vector2f get_gravity() const override;

	void step(double delta) override;

	void destroy_body(PhysicsBody2D *body) override;
	void add_body(PhysicsBody2D *body) override;
};

}

#endif
