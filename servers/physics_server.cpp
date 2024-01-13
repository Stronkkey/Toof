#ifdef B2_INCLUDED

#include <servers/physics/physics_world.hpp>
#include <servers/physics/physics_body.hpp>
#include <servers/physics/physics_shape.hpp>
#include <servers/physics/physics_info.hpp>
#include <servers/physics_server.hpp>

#include <box2d/b2_world.h>
#include <box2d/b2_body.h>

sdl::uid sdl::PhysicsServer2D::assign_uid() {
	uid_index++;
	return uid_index - 1;
}

void sdl::PhysicsServer2D::destroy_uid(const uid destroy_uid) {
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

void sdl::PhysicsServer2D::tick_world(const std::unique_ptr<PhysicsWorld2D> &world, const double delta) {
	world->step(delta);
}

sdl::PhysicsServer2D::PhysicsServer2D(): gravity(Physics::default_gravity), uid_index(1) {
}

sdl::PhysicsServer2D::~PhysicsServer2D() {
	for (const auto &iterator: bodies)
		destroy_uid(iterator.first);

	for (const auto &iterator: shapes)
		destroy_uid(iterator.first);
	worlds.clear();
}

void sdl::PhysicsServer2D::tick(const double delta) {
	for (const auto &iterator: worlds)
		tick_world(iterator.second, delta);
}

void sdl::PhysicsServer2D::remove_uid(const uid remove_uid) {
	destroy_uid(remove_uid);
}

void sdl::PhysicsServer2D::set_gravity(const Vector2 &new_gravity) {
	gravity = new_gravity;

	for (const auto &iterator: worlds)
		iterator.second->get_world()->SetGravity(new_gravity.to_b2_vec2());
}

sdl::Vector2 sdl::PhysicsServer2D::get_gravity() const {
	return gravity;
}

sdl::uid sdl::PhysicsServer2D::create_world() {
	uid assigned_uid = assign_uid();
	worlds.insert({assigned_uid, std::make_unique<PhysicsWorld2D>(gravity)});
	return assigned_uid;
}

void sdl::PhysicsServer2D::world_set_gravity(const uid world_uid, const Vector2 &new_world_gravity) {
	auto iterator = worlds.find(world_uid);
	if (iterator != worlds.end())
		iterator->second->get_world()->SetGravity(new_world_gravity.to_b2_vec2());
}

std::optional<sdl::Vector2> sdl::PhysicsServer2D::world_get_gravity(const uid world_uid) const {
	auto iterator = worlds.find(world_uid);

	if (iterator != worlds.end())
		return iterator->second->get_world()->GetGravity();

	return std::nullopt;
}

void sdl::PhysicsServer2D::world_set_velocity_iterations(const uid world_uid, const int32_t velocity_iterations) {
	auto iterator = worlds.find(world_uid);

	if (iterator != worlds.end())
		iterator->second->velocity_iterations = velocity_iterations;
}

std::optional<int32_t> sdl::PhysicsServer2D::world_get_velocity_iterations(const uid world_uid) const {
	auto iterator = worlds.find(world_uid);

	if (iterator != worlds.end())
		return iterator->second->velocity_iterations;

	return std::nullopt;
}

void sdl::PhysicsServer2D::world_set_position_iterations(const uid world_uid, const int32_t position_iterations) {
	auto iterator = worlds.find(world_uid);

	if (iterator != worlds.end())
		iterator->second->position_iterations = position_iterations;
}

std::optional<int32_t> sdl::PhysicsServer2D::world_get_position_iterations(const uid world_uid) {
	auto iterator = worlds.find(world_uid);

	if (iterator != worlds.end())
		return iterator->second->position_iterations;

	return std::nullopt;
}


#endif // !B2_INCLUDED