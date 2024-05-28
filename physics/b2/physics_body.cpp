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
#include <core/math/transform2d.hpp>
#include <physics/b2/physics_body.hpp>
#include <physics/b2/physics_world.hpp>

#include <physics/physics_object_interface.hpp>

#include <box2d/b2_body.h>
#include <box2d/b2_contact.h>
#include <box2d/b2_fixture.h>

#if TOOF_B2_ENABLED

using namespace Toof;

Physics2DContact detail::b2_contact_to_physics_contact(b2Contact *contact) {
	Physics2DContact contact_info;

	contact_info.touching = contact->IsTouching();
	contact_info.local_position = contact->GetManifold()->localPoint;
	contact_info.shape_id = contact->GetFixtureA()->GetUserData().shape_id;
	contact_info.body = contact->GetFixtureB()->GetBody()->GetUserData().physics_body;
	contact_info.body_shape_id = contact->GetFixtureB()->GetUserData().shape_id;

	return contact_info;
}

void B2PhysicsBody::_update_density() {
	for (const auto &iterator : fixtures)
		for (const auto &fixture : iterator.second.get_fixtures())
			fixture->SetDensity(density);
	body->ResetMassData();
}

void B2PhysicsBody::_update_friction() {
	for (const auto &iterator : fixtures)
		for (const auto &fixture : iterator.second.get_fixtures())
			fixture->SetFriction(density);
}

void B2PhysicsBody::_update_restitution() {
	for (const auto &iterator : fixtures)
		for (const auto &fixture : iterator.second.get_fixtures())
			fixture->SetRestitution(restitution);
}

void B2PhysicsBody::_update_restitution_threshold() {
	for (const auto &iterator : fixtures)
		for (const auto &fixture : iterator.second.get_fixtures())
			fixture->SetRestitutionThreshold(restitution_threshold);
}

void B2PhysicsBody::_set_is_area() {
	for (const auto &iterator : fixtures)
		for (const auto &fixture : iterator.second.get_fixtures())
			fixture->SetSensor(area);
}

void B2PhysicsBody::_shape_removing(Physics2DShape*) {
	for (const auto &iterator : fixtures)
		for (auto &fixture : iterator.second.get_fixtures())
			fixture->GetUserData().shape_id--;
}

B2PhysicsBody::B2PhysicsBody() : body(nullptr),
    fixtures(),
    shape_id_counter(0) {
}

void B2PhysicsBody::add_fixtures(Physics2DShape *shape, FixtureOwner &&fixture_owner) {
	fixtures.insert_or_assign(shape, std::move(fixture_owner));
}

void B2PhysicsBody::remove_fixture(Physics2DShape *shape) {
	auto iterator = fixtures.find(shape);
	if (iterator == fixtures.end())
		return;

	iterator->second.remove_fixtures_from(body);
	fixtures.erase(iterator);
}

void B2PhysicsBody::set_transform(const Transform2D &transform) {
	if (body)
		body->SetTransform(transform.origin, transform.rotation.get_angle_radians());
}

Transform2D B2PhysicsBody::get_transform() const {
	if (body)
		return body->GetTransform();
	return Transform2D::IDENTITY;
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

void B2PhysicsBody::set_angular_velocity(real angular_velocity) {
	if (body)
		body->SetAngularVelocity(angular_velocity);
}

real B2PhysicsBody::get_angular_velocity() const {
	return body ? body->GetAngularVelocity() : 0;
}

void B2PhysicsBody::set_linear_damping(real linear_damping) {
	if (body)
		body->SetLinearDamping(linear_damping);
}

real B2PhysicsBody::get_linear_damping() const {
	return body ? body->GetLinearDamping() : 0;
}

void B2PhysicsBody::set_angular_damping(real angular_damping) {
	if (body)
		body->SetAngularDamping(angular_damping);
}

real B2PhysicsBody::get_angular_damping() const {
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

void B2PhysicsBody::set_gravity_scale(real gravity_scale) {
	if (body)
		body->SetGravityScale(gravity_scale);
}

real B2PhysicsBody::get_gravity_scale() const {
	return body ? body->GetGravityScale() : 1;
}

void B2PhysicsBody::set_density(real density) {
	this->density = density;
	_update_density();
}

real B2PhysicsBody::get_density() const {
	return density;
}

void B2PhysicsBody::set_friction(real friction) {
	this->friction = friction;
	_update_friction();
}

real B2PhysicsBody::get_friction() const {
	return friction;
}

void B2PhysicsBody::set_restitution(real restitution) {
	this->restitution = restitution;
	_update_restitution();
}

real B2PhysicsBody::get_restitution() const {
	return restitution;
}

void B2PhysicsBody::set_restitution_threshold(real restitution_threshold) {
	this->restitution_threshold = restitution_threshold;
	_update_restitution_threshold();
}

real B2PhysicsBody::get_restitution_threshold() const {
	return restitution_threshold;
}

int B2PhysicsBody::get_type() const {
	return PHYSICS_OBJECT_INTERFACE_B2;
}

void B2PhysicsBody::set_area(bool is_area) {
	this->area = is_area;
	_set_is_area();
}

bool B2PhysicsBody::is_area() const {
	return area;
}

void B2PhysicsBody::set_constant_torque(real constant_torque) {
	this->constant_torque = constant_torque;
}

real B2PhysicsBody::get_constant_torque() const {
	return constant_torque;
}

void B2PhysicsBody::set_constant_force(const Vector2f &constant_force) {
	this->constant_force = constant_force;
}

Vector2f B2PhysicsBody::get_constant_force() const {
	return constant_force;
}

PhysicsBodyType B2PhysicsBody::get_body_type() const {
	if (!body)
		return PhysicsBodyType::NONE;

	switch (body->GetType()) {
		case b2_staticBody:
			return PhysicsBodyType::STATIC;
		case b2_dynamicBody:
			return PhysicsBodyType::DYNAMIC;
		case b2_kinematicBody:
			return PhysicsBodyType::KINEMATIC;
	}

	return PhysicsBodyType::NONE;
}

void B2PhysicsBody::step(double delta) {
	if (!body)
		return;

	body->SetLinearVelocity(body->GetLinearVelocity() + (constant_force * delta));
	body->SetAngularVelocity(body->GetAngularVelocity() + (constant_torque * delta));
}

std::vector<Physics2DContact> B2PhysicsBody::get_contacts() const {
	if (!body)
		return {};

	std::vector<Physics2DContact> contacts = {};
	b2ContactEdge *contact_edge = body->GetContactList();
	b2ContactEdge *first_contact_edge = contact_edge;

	while (contact_edge->next != first_contact_edge) {
		contacts.push_back(detail::b2_contact_to_physics_contact(contact_edge->contact));
		contact_edge = contact_edge->next;
	}

	return contacts;
}

#endif
