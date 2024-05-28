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
#include <core/math/angle.hpp>
#include <core/math/transform2d.hpp>

#include <physics/2d/physics_body.hpp>
#include <physics/physics_object_interface.hpp>

#if TOOF_PHYSICS_ENABLED

using namespace Toof;

void Physics2DBody::_shape_added(Physics2DShape*) {
}

void Physics2DBody::_shape_removing(Physics2DShape*) {
}

void Physics2DBody::set_transform(const Transform2D&) {
}

Transform2D Physics2DBody::get_transform() const {
	return Transform2D::IDENTITY;
}

void Physics2DBody::set_linear_velocity(const Vector2f&) {
}

Vector2f Physics2DBody::get_linear_velocity() const {
	return Vector2f::ZERO();
}

void Physics2DBody::set_angular_velocity(real) {
}

real Physics2DBody::get_angular_velocity() const {
	return 0;
}

void Physics2DBody::set_linear_damping(real) {
}

real Physics2DBody::get_linear_damping() const {
	return 0;
}

void Physics2DBody::set_angular_damping(real) {
}

real Physics2DBody::get_angular_damping() const {
	return 0;
}

void Physics2DBody::set_sleeping_allowed(bool) {
}

bool Physics2DBody::is_sleeping_allowed() const {
	return false;
}

void Physics2DBody::set_awake(bool) {
}

bool Physics2DBody::is_awake() const {
	return true;
}

void Physics2DBody::set_rotation_fixed(bool) {
}

bool Physics2DBody::is_rotation_fixed() const {
	return false;
}

void Physics2DBody::set_ccd_active(bool) {
}

bool Physics2DBody::is_ccd_active() const {
	return false;
}

void Physics2DBody::set_gravity_scale(real) {
}

real Physics2DBody::get_gravity_scale() const {
	return 0;
}

void Physics2DBody::set_density(real) {
}

real Physics2DBody::get_density() const {
	return 0;
}

void Physics2DBody::set_friction(real) {
}

real Physics2DBody::get_friction() const {
	return 0;
}

void Physics2DBody::set_restitution(real) {
}

real Physics2DBody::get_restitution() const {
	return 0;
}

void Physics2DBody::set_restitution_threshold(real) {
}

real Physics2DBody::get_restitution_threshold() const {
	return 0;
}

void Physics2DBody::set_area(bool) {
}

bool Physics2DBody::is_area() const {
	return false;
}

void Physics2DBody::set_constant_torque(real) {
}

real Physics2DBody::get_constant_torque() const {
	return 0;
}

void Physics2DBody::set_constant_force(const Vector2f&) {
}

Vector2f Physics2DBody::get_constant_force() const {
	return Vector2f::ZERO();
}

PhysicsBodyType Physics2DBody::get_body_type() const {
	return PhysicsBodyType::NONE;
}

int Physics2DBody::get_type() const {
	return PHYSICS_OBJECT_INTERFACE_NONE;
}

void Physics2DBody::step(double) {
}

std::vector<Physics2DContact> Physics2DBody::get_contacts() const {
	return {};
}

void Physics2DBody::register_contact(const Physics2DContact &contact) {
	contact_listener.register_contact(contact);
}

void Physics2DBody::set_position(const Vector2f &position) {
	Transform2D transform = get_transform();
	transform.origin = position;
	set_transform(transform);
}

Vector2f Physics2DBody::get_position() const {
	return get_transform().origin;
}

void Physics2DBody::set_scale(const Vector2f &scale) {
	Transform2D transform = get_transform();
	transform.scale = scale;
	set_transform(transform);
}

Vector2f Physics2DBody::get_scale() const {
	return Vector2f::ONE();
}

void Physics2DBody::set_rotation(const Angle &angle) {
	Transform2D transform = get_transform();
	transform.rotation = angle;
	set_transform(transform);
}

Angle Physics2DBody::get_rotation() const {
	return Angle::ZERO_ROTATION();
}

size_t Physics2DBody::add_shape(Physics2DShape *shape) {
	shapes.push_back(shape);
	_shape_added(shape);
	return shapes.size() - 1;
}

void Physics2DBody::remove_shape_id(size_t shape_id) {
	if (shapes.size() >= shape_id)
		return;
	auto iterator = shapes.begin() + shape_id;
	_shape_removing(*iterator);
	shapes.erase(iterator);
}

void Physics2DBody::remove_shape(Physics2DShape *shape) {
	for (size_t i = 0; i < shapes.size(); i++)
		if (shapes[i] == shape) {
			shapes.erase(shapes.begin() + i);
			i--;
		}
}

Physics2DShape *Physics2DBody::get_shape(size_t shape_idx) {
	if (shapes.size() >= shape_idx)
		return nullptr;
	return *(shapes.begin() + shape_idx);
}

#endif
