/*  This file is part of the Toof Engine. */
/** @file physics_body_2d.hpp */
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

#include <scene/2d/node2d.hpp>
#include <physics/2d/physics_body.hpp>

#if TOOF_PHYSICS_ENABLED

namespace Toof {

class CollisionShape2D;
class PhysicsServer2D;
class Shape2D;
class World2D;

class PhysicsBody2D : public Node2D {
public:
	enum {
		NOTIFICATION_PHYSICS_CONTACT_STARTED = 2000,
		NOTIFICATION_PHYSICS_CONTACT_ENDED = 2001,
		NOTIFICATION_PHYSICS_CONTACT_CHANGED = 2002,
	};
private:
	uid body_uid;
	Transform2D body_transform;
	Vector2f linear_velocity;
	real angular_velocity;
	real linear_damping;
	real angular_damping;
	bool sleeping_allowed;
	bool awake;
	bool rotation_fixed;
	bool ccd_active;
	bool area;
	bool transform_set_queued;
	bool physics_update_queued;
	real gravity_scale;
	real density;
	real friction;
	real restitution;
	real constant_torque;
	Vector2f constant_force;
	std::unordered_map<CollisionShape2D*, int> collision_shapes;
	struct _ContactInfo {
		bool has_entered;
		PhysicsBody2D *body;
		int body_shape_id;
		int shape_id;
		Vector2f local_position;
	} current_contact;

	void _enter_tree();
	void _exit_tree();
	PhysicsBody2D *_get_body_from_uid_in_world(uid body_uid) const;
	void _on_child_added(Node *child);
	void _on_child_removing(Node *child);
	void _on_physics_process();
	void _update_collision_shape(CollisionShape2D *collision_shape);
	void _update_physics_properties();
	void _queue_physics_update();
	void _set_body_transform(const Transform2D &transform);

	virtual uid _create_body(PhysicsServer2D *physics_server_2d, uid world_uid) const =0;
	virtual PhysicsBodyType _get_body_type() const =0;

	virtual void _body_contact_started(PhysicsBody2D *body);
	virtual void _body_contact_changed(bool has_entered, PhysicsBody2D *body, int body_shape_id, int shape_id, const Vector2f &local_position);
	virtual void _body_contact_ended(PhysicsBody2D *body);
protected:
	void _notification(int what) override;
	constexpr const _ContactInfo _get_current_contact() const {
		return current_contact;
	}
public:
	PhysicsBody2D();
	~PhysicsBody2D() = default;

	constexpr uid get_uid() const {
		return body_uid;
	}

	Signal<PhysicsBody2D*> body_entered;
	Signal<PhysicsBody2D*> body_exited;
	Signal<bool, PhysicsBody2D*, int, int, Vector2f> body_contact_changed;

	void queue_set_transform(const Transform2D &transform);
	Transform2D get_transform() const override;

	void set_linear_velocity(const Vector2f &linear_velocity);
	constexpr const Vector2f &get_linear_velocity() const & { return linear_velocity; }
	constexpr const Vector2f &&get_linear_velocity() const && { return std::move(linear_velocity); }

	void set_angular_velocity(real angular_velocity);
	constexpr real get_angular_velocity() const { return angular_velocity; }

	void set_angular_damping(real angular_damping);
	constexpr real get_angular_damping() const { return angular_damping; }

	void set_linear_damping(real linear_damping);
	constexpr real get_linear_damping() const { return linear_damping; }

	void set_sleeping_allowed(bool sleeping_allowed);
	constexpr bool is_sleeping_allowed() const { return sleeping_allowed; }

	void set_awake(bool awake);
	constexpr bool is_awake() const { return awake; }

	void set_rotation_fixed(bool rotation_fixed);
	constexpr bool is_rotation_fixed() const { return rotation_fixed; }

	void set_ccd_active(bool ccd_active);
	constexpr bool is_ccd_active() const { return ccd_active; }

	void set_gravity_scale(real gravity_scale);
	constexpr real get_gravity_scale() const { return gravity_scale; }

	void set_density(real density);
	constexpr real get_density() const { return density; }

	void set_friction(real friction);
	constexpr real get_friction() const { return friction; }

	void set_restitution(real restitution);
	constexpr real get_restitution() const { return restitution; }

	void set_is_area(bool is_area);
	constexpr bool is_area() const { return area; }

	void set_constant_torque(real constant_torque);
	constexpr real get_constant_torque() const { return constant_torque; }

	void set_constant_force(const Vector2f &constant_force);
	constexpr const Vector2f &get_constant_force() const & { return constant_force; }
	constexpr const Vector2f &&get_constant_force() const && { return std::move(constant_force); }

	PhysicsBodyType get_body_type() const;
};

}

#endif
