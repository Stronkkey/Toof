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
#include <scene/2d/physics/collision_shape_2d.hpp>
#include <scene/2d/physics/physics_body_2d.hpp>
#include <scene/main/scene_tree.hpp>
#include <scene/resources/world2d.hpp>
#include <servers/physics_server_2d.hpp>

#if TOOF_PHYSICS_ENABLED

using namespace Toof;

#include <box2d/b2_fixture.h>

void PhysicsBody2D::_enter_tree() {
	Optional<PhysicsServer2D*> physics_server_2d = get_physics_server_2d();
	Optional<World2D*> world_2d = get_world_2d();

	if (!physics_server_2d || !world_2d)
		return;

	body_uid = _create_body(physics_server_2d.get_value(), world_2d.get_value()->get_space());
	world_2d.get_value()->add_body(this);
	_update_physics_properties();

	for (const auto &iterator : collision_shapes)
		if (iterator.second == 0)
			physics_server_2d.get_value()->body_add_shape(body_uid, iterator.first->get_shape_uid());

	Signal<PhysicsServer2D::ContactInfo> signal = physics_server_2d.get_value()->body_get_monitor_signal(body_uid);

	auto signal_callback = [this](const PhysicsServer2D::ContactInfo &contact_info) {
		current_contact.body = _get_body_from_uid_in_world(contact_info.get_body_uid());
		current_contact.body_shape_id = contact_info.get_body_shape_id();
		current_contact.shape_id = contact_info.get_shape_id();
		current_contact.has_entered = contact_info.has_entered();
		current_contact.local_position = contact_info.get_local_position();
	
		notification(NOTIFICATION_PHYSICS_CONTACT_CHANGED);
		if (contact_info.has_entered())
			notification(NOTIFICATION_PHYSICS_CONTACT_STARTED);
		else
			notification(NOTIFICATION_PHYSICS_CONTACT_ENDED);
	};

	signal.connect(signal_callback);
}

void PhysicsBody2D::_exit_tree() {
	Optional<PhysicsServer2D*> physics_server_2d = get_physics_server_2d();
	Optional<World2D*> world_2d = get_world_2d();

	if (physics_server_2d)
		physics_server_2d.get_value()->free_uid(body_uid);

	if (world_2d)
			world_2d.get_value()->remove_body(this);
}

PhysicsBody2D *PhysicsBody2D::_get_body_from_uid_in_world(uid body_uid) const {
	Optional<World2D*> world_2d = get_world_2d();
	if (world_2d)
		return world_2d.get_value()->get_body_from_uid(body_uid);
	return nullptr;
}

void PhysicsBody2D::_on_child_added(Node *child) {
	CollisionShape2D *collision_shape = dynamic_cast<CollisionShape2D*>(child);

	if (collision_shape) {
		Optional<PhysicsServer2D*> physics_server_2d = get_physics_server_2d();
		if (physics_server_2d)
			collision_shapes.insert_or_assign(collision_shape, physics_server_2d.get_value()->body_add_shape(body_uid, collision_shape->get_shape_uid()));
		else
			collision_shapes.insert_or_assign(collision_shape, 0);
	}
}

void PhysicsBody2D::_on_child_removing(Node *child) {
	auto iterator = collision_shapes.find(static_cast<CollisionShape2D*>(child));
	Optional<PhysicsServer2D*> physics_server_2d = get_physics_server_2d();

	if (iterator != collision_shapes.end() && physics_server_2d)
		physics_server_2d.get_value()->free_uid(iterator->first->get_shape_uid());

	collision_shapes.erase(iterator);

	for (auto &iterator : collision_shapes)
		iterator.second--;
}


void PhysicsBody2D::_on_physics_process() {
	Optional<PhysicsServer2D*> physics_server_2d = get_physics_server_2d();

	if (!physics_server_2d)
		return;

	if (physics_update_queued)
		_update_physics_properties();

	if (transform_set_queued) {
		transform_set_queued = false;
		physics_server_2d.get_value()->body_set_transform(body_uid, body_transform);
	} else {
		Optional<Transform2D> body_transform = physics_server_2d.get_value()->body_get_transform(body_uid);
		if (body_transform)
			_set_body_transform(body_transform.get_value());
	}
}

void PhysicsBody2D::_update_collision_shape(CollisionShape2D *collision_shape) {
	auto iterator = collision_shapes.find(collision_shape);
	Optional<PhysicsServer2D*> physics_server_2d = get_physics_server_2d();

	if (physics_server_2d) {
		if (iterator != collision_shapes.end())
			physics_server_2d.get_value()->body_remove_shape(body_uid, iterator->second);
		physics_server_2d.get_value()->body_add_shape(body_uid, collision_shape->get_shape_uid());
	}
}

void PhysicsBody2D::_update_physics_properties() {
	PhysicsServer2D *physics_server_2d = get_physics_server_2d().value_or(nullptr);

	if (physics_server_2d) {
		physics_server_2d->body_set_angular_damping(body_uid, angular_damping);
		physics_server_2d->body_set_angular_velocity(body_uid, angular_velocity);
		physics_server_2d->body_set_area(body_uid, area);
		physics_server_2d->body_set_awake(body_uid, awake);
		physics_server_2d->body_set_ccd_active(body_uid, ccd_active);
		physics_server_2d->body_set_density(body_uid, density);
		physics_server_2d->body_set_friction(body_uid, friction);
		physics_server_2d->body_set_gravity_scale(body_uid, gravity_scale);
		physics_server_2d->body_set_linear_damping(body_uid, linear_damping);
		physics_server_2d->body_set_linear_velocity(body_uid, linear_velocity);
		physics_server_2d->body_set_restitution(body_uid, restitution);
		physics_server_2d->body_set_rotation_fixed(body_uid, rotation_fixed);
		physics_server_2d->body_set_sleeping_allowed(body_uid, sleeping_allowed);
		physics_server_2d->body_set_constant_torque(body_uid, constant_torque);
		physics_server_2d->body_set_constant_force(body_uid, constant_force);
	}
}

void PhysicsBody2D::_queue_physics_update() {
	physics_update_queued = true;
}

void PhysicsBody2D::_set_body_transform(const Transform2D &transform) {
	body_transform = transform;
	set_transform(transform);
}

void PhysicsBody2D::_body_contact_started(PhysicsBody2D*) {
}

void PhysicsBody2D::_body_contact_changed(bool, PhysicsBody2D*, int, int, const Vector2f&) {
}

void PhysicsBody2D::_body_contact_ended(PhysicsBody2D*) {
}

void PhysicsBody2D::_notification(int what) {
	Node2D::_notification(what);

	switch (what) {
		case NOTIFICATION_CHILD_ADDED:
			_on_child_added(get_last_child_modified());
			break;
		case NOTIFICATION_CHILD_REMOVING:
			_on_child_removing(get_last_child_modified());
			break;
		case NOTIFICATION_ENTER_TREE:
			_enter_tree();
			break;
		case NOTIFICATION_EXIT_TREE:
			_exit_tree();
			break;
		case NOTIFICATION_PHYSICS_CONTACT_ENDED:
			body_exited(current_contact.body);
			break;
		case NOTIFICATION_PHYSICS_CONTACT_CHANGED:
			body_contact_changed(current_contact.has_entered, current_contact.body, current_contact.body_shape_id, current_contact.shape_id, current_contact.local_position);
			break;
		case NOTIFICATION_PHYSICS_PROCESS:
			_on_physics_process();
			break;
		case NOTIFICATION_PHYSICS_CONTACT_STARTED:
			body_entered(current_contact.body);
			break;
		default:
			break;
	}
}

PhysicsBody2D::PhysicsBody2D() : body_uid(0),
    body_transform(Transform2D::IDENTITY),
    linear_velocity(),
    angular_velocity(0),
    linear_damping(0),
    angular_damping(0),
    sleeping_allowed(true),
    awake(true),
    rotation_fixed(false),
    ccd_active(false),
    area(false),
    transform_set_queued(false),
    physics_update_queued(false),
    gravity_scale(1),
    density(1),
    friction(0.5),
    restitution(0),
    constant_torque(0),
    constant_force() {
}

void PhysicsBody2D::queue_set_transform(const Transform2D &transform) {
	if (transform_set_queued)
		return;
	transform_set_queued = true;
	_set_body_transform(transform);
}

Transform2D PhysicsBody2D::get_transform() const {
	return body_transform;
}

void PhysicsBody2D::set_linear_velocity(const Vector2f &linear_velocity) {
	this->linear_velocity = linear_velocity;
	_queue_physics_update();
}

void PhysicsBody2D::set_angular_velocity(real angular_velocity) {
	this->angular_velocity = angular_velocity;
	_queue_physics_update();
}

void PhysicsBody2D::set_angular_damping(real angular_damping) {
	this->angular_damping = angular_damping;
	_queue_physics_update();
}

void PhysicsBody2D::set_linear_damping(real linear_damping) {
	this->linear_damping = linear_damping;
	_queue_physics_update();
}

void PhysicsBody2D::set_sleeping_allowed(bool sleeping_allowed) {
	this->sleeping_allowed = sleeping_allowed;
	_queue_physics_update();
}

void PhysicsBody2D::set_awake(bool awake) {
	this->awake = awake;
	_queue_physics_update();
}

void PhysicsBody2D::set_rotation_fixed(bool rotation_fixed) {
	this->rotation_fixed = rotation_fixed;
	_queue_physics_update();
}

void PhysicsBody2D::set_ccd_active(bool ccd_active) {
	this->ccd_active = ccd_active;
	_queue_physics_update();
}

#endif
