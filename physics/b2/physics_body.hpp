/*  This file is part of the Toof Engine. */
/** @file b2_physics_body.hpp */
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

#include <physics/2d/physics_body.hpp>

class b2Body;

namespace Toof {

class B2PhysicsBody : public PhysicsBody2D {
private:
	b2Body *body;
public:
	constexpr void set_body(b2Body *body) {
		this->body = body;
	}

	constexpr b2Body *get_body() const {
		return body;
	}

	void set_transform(const Transform2D &transform) override;
	Transform2D get_transform() const override;

	void set_linear_velocity(const Vector2f &linear_velocity) override;
	Vector2f get_linear_velocity() const override;

	void set_angular_velocity(const double angular_velocity) override;
	double get_angular_velocity() const override;

	void set_linear_damping(double linear_damping) override;
	double get_linear_damping() const override;

	void set_angular_damping(double angular_damping) override;
	double get_angular_damping() const override;

	void set_sleeping_allowed(bool is_sleeping_allowed) override;
	bool is_sleeping_allowed() const override;

	void set_awake(bool awake) override;
	bool is_awake() const override;

	void set_rotation_fixed(bool rotation_fixed) override;
	bool is_rotation_fixed() const override;

	void set_ccd_active(bool ccd_active) override;
	bool is_ccd_active() const override;

	void set_gravity_scale(double gravity_scale) override;
	double get_gravity_scale() const override;

	BodyType get_body_type() const override;
	int get_type() const override;
};

}

#endif
