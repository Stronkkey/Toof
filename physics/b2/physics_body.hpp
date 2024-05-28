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
#pragma once

#include <core/math/vector2.hpp>
#include <physics/2d/physics_body.hpp>
#include <physics/b2/fixture_owner.hpp>

#include <box2d/b2_world_callbacks.h>

#include <unordered_map>

#if TOOF_B2_ENABLED

namespace Toof {

namespace detail {

Physics2DContact b2_contact_to_physics_contact(b2Contact *contact);

}

class B2PhysicsBody : public Physics2DBody {
private:
	b2Body *body;
	std::unordered_map<Physics2DShape*, FixtureOwner> fixtures;
	int shape_id_counter;

	real density;
	real friction;
	real restitution;
	real restitution_threshold;
	bool area;
	real constant_torque;
	Vector2f constant_force;

	void _update_density();
	void _update_friction();
	void _update_restitution();
	void _update_restitution_threshold();
	void _set_is_area();
	void _shape_removing(Physics2DShape *shape) override;
public:
	B2PhysicsBody();
	~B2PhysicsBody() = default;

	constexpr void set_body(b2Body *body) {
		this->body = body;
	}

	constexpr b2Body *get_body() const {
		return body;
	}

	constexpr int increment_shape_id_counter() {
		return shape_id_counter++;
	}

	constexpr int decrement_shape_id_counter() {
		return --shape_id_counter;
	}

	void add_fixtures(Physics2DShape *shape, FixtureOwner &&fixture_owner);
	void remove_fixture(Physics2DShape *shape);

	void set_transform(const Transform2D &transform) override;
	Transform2D get_transform() const override;

	void set_linear_velocity(const Vector2f &linear_velocity) override;
	Vector2f get_linear_velocity() const override;

	void set_angular_velocity(const real angular_velocity) override;
	real get_angular_velocity() const override;

	void set_linear_damping(real linear_damping) override;
	real get_linear_damping() const override;

	void set_angular_damping(real angular_damping) override;
	real get_angular_damping() const override;

	void set_sleeping_allowed(bool is_sleeping_allowed) override;
	bool is_sleeping_allowed() const override;

	void set_awake(bool awake) override;
	bool is_awake() const override;

	void set_rotation_fixed(bool rotation_fixed) override;
	bool is_rotation_fixed() const override;

	void set_ccd_active(bool ccd_active) override;
	bool is_ccd_active() const override;

	void set_gravity_scale(real gravity_scale) override;
	real get_gravity_scale() const override;

	void set_density(real density) override;
	real get_density() const override;

	void set_friction(real friction) override;
	real get_friction() const override;

	void set_restitution(real restitution) override;
	real get_restitution() const override;

	void set_restitution_threshold(real restitution_threshold) override;
	real get_restitution_threshold() const override;

	void set_area(bool is_area) override;
	bool is_area() const override;

	void set_constant_torque(real constant_torque) override;
	real get_constant_torque() const override;

	void set_constant_force(const Vector2f &constant_force) override;
	Vector2f get_constant_force() const override;

	PhysicsBodyType get_body_type() const override;
	int get_type() const override;
	void step(double delta) override;
	std::vector<Physics2DContact> get_contacts() const override;
};

}

#endif
