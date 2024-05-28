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

#include <core/math/angle.hpp>
#include <core/math/transform2d.hpp>

#include <physics/2d/physics_body.hpp>
#include <physics/physics_object_interface.hpp>

using namespace Toof;

void PhysicsBody2D::set_transform(const Transform2D&) {
}

Transform2D PhysicsBody2D::get_transform() const {
	return Transform2D::IDENTITY;
}

void PhysicsBody2D::set_linear_velocity(const Vector2f&) {
}

Vector2f PhysicsBody2D::get_linear_velocity() const {
	return Vector2f::ZERO();
}

void PhysicsBody2D::set_angular_velocity(double) {
}

double PhysicsBody2D::get_angular_velocity() const {
	return 0;
}

void PhysicsBody2D::set_linear_damping(double) {
}

double PhysicsBody2D::get_linear_damping() const {
	return 0;
}

void PhysicsBody2D::set_angular_damping(double) {
}

double PhysicsBody2D::get_angular_damping() const {
	return 0;
}

void PhysicsBody2D::set_sleeping_allowed(bool) {
}

bool PhysicsBody2D::is_sleeping_allowed() const {
	return false;
}

void PhysicsBody2D::set_awake(bool) {
}

bool PhysicsBody2D::is_awake() const {
	return true;
}

void PhysicsBody2D::set_rotation_fixed(bool) {
}

bool PhysicsBody2D::is_rotation_fixed() const {
	return false;
}

void PhysicsBody2D::set_ccd_active(bool) {
}

bool PhysicsBody2D::is_ccd_active() const {
	return false;
}

void PhysicsBody2D::set_gravity_scale(double) {
}

double PhysicsBody2D::get_gravity_scale() const {
	return 0;
}

PhysicsBody2D::BodyType PhysicsBody2D::get_body_type() const {
	return BodyType::NONE;
}

int PhysicsBody2D::get_type() const {
	return PHYSICS_OBJECT_INTERFACE_NONE;
}

void PhysicsBody2D::set_position(const Vector2f &position) {
	Transform2D transform = get_transform();
	transform.origin = position;
	set_transform(transform);
}

Vector2f PhysicsBody2D::get_position() const {
	return get_transform().origin;
}

void PhysicsBody2D::set_scale(const Vector2f &scale) {
	Transform2D transform = get_transform();
	transform.scale = scale;
	set_transform(transform);
}

Vector2f PhysicsBody2D::get_scale() const {
	return Vector2f::ONE();
}

void PhysicsBody2D::set_rotation(const Angle &angle) {
	Transform2D transform = get_transform();
	transform.rotation = angle;
	set_transform(transform);
}

Angle PhysicsBody2D::get_rotation() const {
	return Angle::ZERO_ROTATION();
}

#endif