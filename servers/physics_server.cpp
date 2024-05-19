#include "core/math/math_defs.hpp"
#ifdef B2_INCLUDED

#include <servers/physics/physics_world.hpp>
#include <servers/physics/physics_body.hpp>
#include <servers/physics/physics_shape.hpp>
#include <servers/physics/physics_info.hpp>
#include <servers/physics_server.hpp>

#include <box2d/b2_world.h>

Toof::uid Toof::PhysicsServer2D::assign_uid() {
	uid_index++;
	return uid_index - 1;
}

void Toof::PhysicsServer2D::destroy_uid(const uid destroy_uid) {
	auto body_iterator = bodies.find(destroy_uid);

	if (body_iterator != bodies.end()) {
		body_iterator->second->body = nullptr;
		body_iterator->second->world_uid = 0;
		bodies.erase(body_iterator);
	}

	auto shape_iterator = shapes.find(destroy_uid);

	if (shape_iterator != shapes.end())
		shape_iterator->second->shape = nullptr;
}

void Toof::PhysicsServer2D::tick_world(const std::unique_ptr<PhysicsWorld2D> &world, const double delta) {
	world->step(delta);
}

std::unique_ptr<b2BodyDef> Toof::PhysicsServer2D::get_body_def_from_body(const b2Body *body) const {
	auto body_def = std::make_unique<b2BodyDef>();

	body_def->angle = body->GetAngle();
	body_def->allowSleep = body->IsSleepingAllowed();
	body_def->angularDamping = body->GetAngularDamping();
	body_def->angularVelocity = body->GetAngularVelocity();
	body_def->bullet = body->IsBullet();
	body_def->fixedRotation = body->IsFixedRotation();
	body_def->enabled = body->IsEnabled();
	body_def->awake = body->IsAwake();
	body_def->linearVelocity = body->GetLinearVelocity();
	body_def->type = body->GetType();

	return body_def;
}

void Toof::PhysicsServer2D::create_physics_body_from_def(const std::unique_ptr<PhysicsBody> &physics_body, const uid world_uid, const b2BodyDef *body_def) {
	auto iterator = worlds.find(world_uid);
	if (iterator == worlds.end())
		return;

	std::unique_ptr<PhysicsWorld2D> &world = iterator->second;
	physics_body->body = world->get_world()->CreateBody(body_def ? body_def : &default_body_definition);
	physics_body->world_uid = world_uid;
}

void Toof::PhysicsServer2D::transfer_body_to_world(const std::unique_ptr<PhysicsBody> &physics_body, const uid world_uid) {
	auto iterator = worlds.find(physics_body->world_uid);
	b2Body *old_body = physics_body->body;
	bool clean_body = false;

	if (iterator != worlds.end() && physics_body->body)
		clean_body = true;
	
	create_physics_body_from_def(physics_body, world_uid);
	if (clean_body)
		iterator->second->get_world()->DestroyBody(old_body);
}


Toof::PhysicsServer2D::PhysicsServer2D(): gravity(Physics::default_gravity), uid_index(1), default_body_definition() {
}

Toof::PhysicsServer2D::~PhysicsServer2D() {
	for (const auto &iterator: bodies)
		destroy_uid(iterator.first);

	for (const auto &iterator: shapes)
		destroy_uid(iterator.first);
	worlds.clear();
}

void Toof::PhysicsServer2D::tick(const double delta) {
	for (const auto &iterator: worlds)
		tick_world(iterator.second, delta);
}

void Toof::PhysicsServer2D::remove_uid(const uid remove_uid) {
	destroy_uid(remove_uid);
}

void Toof::PhysicsServer2D::set_gravity(const Vector2f &new_gravity) {
	gravity = new_gravity;

	for (const auto &iterator: worlds)
		iterator.second->get_world()->SetGravity(new_gravity.to_b2_vec2());
}

const Toof::Vector2f &Toof::PhysicsServer2D::get_gravity() const {
	return gravity;
}

Toof::uid Toof::PhysicsServer2D::create_world() {
	uid assigned_uid = assign_uid();
	worlds.insert({assigned_uid, std::make_unique<PhysicsWorld2D>(gravity)});
	return assigned_uid;
}

Toof::uid Toof::PhysicsServer2D::body_create() {
	uid assigned_uid = assign_uid();
	bodies.insert({assigned_uid, std::make_unique<PhysicsBody>()});
	return assigned_uid;
}

void Toof::PhysicsServer2D::world_set_gravity(const uid world_uid, const Vector2f &new_world_gravity) {
	auto iterator = worlds.find(world_uid);
	if (iterator != worlds.end())
		iterator->second->get_world()->SetGravity(new_world_gravity.to_b2_vec2());
}

Toof::Optional<Toof::Vector2f> Toof::PhysicsServer2D::world_get_gravity(const uid world_uid) const {
	auto iterator = worlds.find(world_uid);

	if (iterator != worlds.end())
		return Vector2f(iterator->second->get_world()->GetGravity());

	return NullOption;
}

void Toof::PhysicsServer2D::world_set_velocity_iterations(const uid world_uid, const int32_t velocity_iterations) {
	auto iterator = worlds.find(world_uid);

	if (iterator != worlds.end())
		iterator->second->velocity_iterations = velocity_iterations;
}

Toof::Optional<int32_t> Toof::PhysicsServer2D::world_get_velocity_iterations(const uid world_uid) const {
	auto iterator = worlds.find(world_uid);

	if (iterator != worlds.end())
		return iterator->second->velocity_iterations;

	return NullOption;
}

void Toof::PhysicsServer2D::world_set_position_iterations(const uid world_uid, const int32_t position_iterations) {
	auto iterator = worlds.find(world_uid);

	if (iterator != worlds.end())
		iterator->second->position_iterations = position_iterations;
}

Toof::Optional<int32_t> Toof::PhysicsServer2D::world_get_position_iterations(const uid world_uid) const {
	auto iterator = worlds.find(world_uid);

	if (iterator != worlds.end())
		return iterator->second->position_iterations;

	return NullOption;
}

void Toof::PhysicsServer2D::body_set_world(const uid body_uid, const uid world_uid) {
	auto iterator = bodies.find(body_uid);
	if (iterator != bodies.end())
		transfer_body_to_world(iterator->second, world_uid);
}

Toof::Optional<Toof::uid> Toof::PhysicsServer2D::body_get_world(const uid body_uid) const {
	auto iterator = bodies.find(body_uid);

	if (iterator != bodies.end())
		return iterator->second->world_uid;
	
	return NullOption;
}

void body_set_state_transform(const std::unique_ptr<Toof::PhysicsBody> &body, const Toof::PhysicsServer2D::body_state_variant &state_value) {
	try {
		const Toof::Transform2D transform = std::get<Toof::Transform2D>(state_value);
		body->body->SetTransform(transform.origin.to_b2_vec2(), transform.rotation.get_angle_radians());
	} catch(const std::bad_variant_access &ex) {
	}
}

void Toof::PhysicsServer2D::body_set_state(const uid body_uid, const BodyState body_state, const body_state_variant &state_value) {
	auto iterator = bodies.find(body_uid);
	if (iterator == bodies.end() || body_state == BODY_STATE_NONE)
		return;

	switch (body_state) {
		case BODY_STATE_TRANSFORM:
			body_set_state_transform(iterator->second, state_value);
		default:
			break;
	}
}

#endif // !B2_INCLUDED