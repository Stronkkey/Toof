/*  This file is part of the Toof Engine. */
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
#ifdef TOOF_PHYSICS_ENABLED

#include <servers/physics/physics_world.hpp>

#include <box2d/b2_world.h>

Toof::PhysicsWorld2D::PhysicsWorld2D(const Vector2f &gravity, const int32_t velocity_iterations, const int32_t position_iterations) {
	b2_world = std::make_unique<b2World>(gravity.to_b2_vec2());
	this->velocity_iterations = velocity_iterations;
	this->position_iterations = position_iterations;
}

void Toof::PhysicsWorld2D::step(const double delta) const {
	b2_world->Step(delta, velocity_iterations, position_iterations);
}

#endif // !TOOF_PHYSICS_ENABLED