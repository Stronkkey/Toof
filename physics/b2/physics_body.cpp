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
#ifdef TOOF_B2_ENABLED

#include <core/math/transform2d.hpp>
#include <physics/b2/physics_body.hpp>

#include <physics/physics_object_interface.hpp>

#include <box2d/b2_body.h>

using namespace Toof;

void B2PhysicsBody::set_transform(const Transform2D &transform) {
	if (body)
		body->SetTransform(transform.origin, transform.rotation.get_angle_radians());
}

Transform2D B2PhysicsBody::get_transform() const {
	if (body)
		return body->GetTransform();
	return body->GetTransform();
}

void B2PhysicsBody::set_linear_velocity(const Vector2f &linear_velocity) {
	if (body)
		body->SetLinearVelocity(linear_velocity);
}

Vector2f B2PhysicsBody::get_linear_velocity() const {
	if (body)
		return body->GetLinearVelocity();
	return Vector2f::ZERO();
}

void B2PhysicsBody::set_angular_velocity(double angular_velocity) {
	if (body)
		body->SetAngularVelocity(angular_velocity);
}

double B2PhysicsBody::get_angular_velocity() const {
	return body ? body->GetAngularVelocity() : 0;
}

void B2PhysicsBody::set_linear_damping(double linear_damping) {
	if (body)
		body->SetLinearDamping(linear_damping);
}

double B2PhysicsBody::get_linear_damping() const {
	return body ? body->GetLinearDamping() : 0;
}

void B2PhysicsBody::set_angular_damping(double angular_damping) {
	if (body)
		body->SetAngularDamping(angular_damping);
}

double B2PhysicsBody::get_angular_damping() const {
	return body ? body->GetAngularDamping() : 0;
}

void B2PhysicsBody::set_sleeping_allowed(bool is_sleeping_allowed) {
	if (body)
		body->SetSleepingAllowed(is_sleeping_allowed);
}

bool B2PhysicsBody::is_sleeping_allowed() const {
	return body ? body->IsSleepingAllowed() : false;
}

void B2PhysicsBody::set_awake(bool awake) {
	if (body)
		body->SetAwake(awake);
}

bool B2PhysicsBody::is_awake() const {
	return body ? body->IsAwake() : true;
}

void B2PhysicsBody::set_rotation_fixed(bool rotation_fixed) {
	if (body)
		body->SetFixedRotation(rotation_fixed);
}

bool B2PhysicsBody::is_rotation_fixed() const {
	return body ? body->IsFixedRotation() : false;
}

void B2PhysicsBody::set_ccd_active(bool ccd_active) {
	if (body)
		body->SetBullet(ccd_active);
}

bool B2PhysicsBody::is_ccd_active() const {
	return body ? body->IsBullet() : false;
}

void B2PhysicsBody::set_gravity_scale(double gravity_scale) {
	if (body)
		body->SetGravityScale(gravity_scale);
}

double B2PhysicsBody::get_gravity_scale() const {
	return body ? body->GetGravityScale() : 1;
}

int B2PhysicsBody::get_type() const {
	return PHYSICS_OBJECT_INTERFACE_B2;
}

PhysicsBody2D::BodyType B2PhysicsBody::get_body_type() const {
	if (!body)
		return BodyType::NONE;

	switch (body->GetType()) {
		case b2_staticBody:
			return BodyType::STATIC;
		case b2_dynamicBody:
			return BodyType::DYNAMIC;
		case b2_kinematicBody:
			return BodyType::KINEMATIC;
	}

	return BodyType::NONE;
}

#endif
