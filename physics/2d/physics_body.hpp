/*  This file is part of the Toof Engine. */
/** @file physics_body.hpp */
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

#include <core/memory/signal.hpp>
#include <physics/2d/physics_body_type.hpp>
#include <physics/2d/physics_contact.hpp>
#include <physics/2d/physics_contact_listener.hpp>

#include <vector>

#if TOOF_PHYSICS_ENABLED

namespace Toof {

class Transform2D;
class Angle;
class Physics2DShape;
class PhysicsWorld2D;

class Physics2DBody {
private:
	uid world_uid;
	std::vector<Physics2DShape*> shapes;
	Physics2DContactListener contact_listener;

	virtual void _shape_added(Physics2DShape *shape);
	virtual void _shape_removing(Physics2DShape *shape);
public:
	Physics2DBody() = default;
	~Physics2DBody() = default;

	constexpr uid get_body_uid() const {
		return contact_listener.get_body_uid();
	}

	constexpr void set_world_uid(uid world_uid) {
		this->world_uid = world_uid;
	}

	constexpr uid get_world_uid() const {
		return world_uid;
	}

	constexpr Physics2DContactListener &_get_contact_listener() {
		return contact_listener;
	}

	virtual void set_transform(const Transform2D &transform);
	virtual Transform2D get_transform() const;

	virtual void set_linear_velocity(const Vector2f &linear_velocity);
	virtual Vector2f get_linear_velocity() const;

	virtual void set_angular_velocity(const real angular_velocity);
	virtual real get_angular_velocity() const;

	virtual void set_linear_damping(real linear_damping);
	virtual real get_linear_damping() const;

	virtual void set_angular_damping(real angular_damping);
	virtual real get_angular_damping() const;

	virtual void set_sleeping_allowed(bool is_sleeping_allowed);
	virtual bool is_sleeping_allowed() const;

	virtual void set_awake(bool awake);
	virtual bool is_awake() const;

	virtual void set_rotation_fixed(bool rotation_fixed);
	virtual bool is_rotation_fixed() const;

	virtual void set_ccd_active(bool ccd_active);
	virtual bool is_ccd_active() const;

	virtual void set_gravity_scale(real gravity_scale);
	virtual real get_gravity_scale() const;

	virtual void set_density(real density);
	virtual real get_density() const;

	virtual void set_friction(real friction);
	virtual real get_friction() const;

	virtual void set_restitution(real restitution);
	virtual real get_restitution() const;

	virtual void set_restitution_threshold(real restitution_threshold);
	virtual real get_restitution_threshold() const;

	virtual void set_area(bool is_area);
	virtual bool is_area() const;

	virtual void set_constant_torque(real constant_torque);
	virtual real get_constant_torque() const;

	virtual void set_constant_force(const Vector2f &constant_force);
	virtual Vector2f get_constant_force() const;

	virtual PhysicsBodyType get_body_type() const;
	virtual int get_type() const;
	virtual void step(double delta);
	virtual std::vector<Physics2DContact> get_contacts() const;

	void register_contact(const Physics2DContact &contact);

	void set_position(const Vector2f &position);
	Vector2f get_position() const;

	void set_scale(const Vector2f &scale);
	Vector2f get_scale() const;

	void set_rotation(const Angle &angle);
	Angle get_rotation() const;

	size_t add_shape(Physics2DShape *shape);
	void remove_shape_id(size_t shape_id);
	void remove_shape(Physics2DShape *shape);
	Physics2DShape *get_shape(size_t shape_idx);

	constexpr std::vector<Physics2DShape*> &get_shapes() {
		return shapes;
	}

	constexpr const std::vector<Physics2DShape*> &get_shapes() const {
		return shapes;
	}
};

}

#endif
