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

#include <physics/2d/physics_world.hpp>
#include <physics/2d/physics_body.hpp>
#include <physics/2d/physics_shape.hpp>
#include <physics/2d/physics_info.hpp>
#include <servers/physics_server_2d.hpp>

using namespace Toof;

void PhysicsServer2D::destroy_uid(uid object_uid) {
	auto world_iterator = worlds.find(object_uid);
	auto body_iterator = bodies.find(object_uid);
	auto shape_iterator = shapes.find(object_uid);

	if (world_iterator != worlds.end())
		worlds.erase(world_iterator);

	if (body_iterator != bodies.end())
		bodies.erase(body_iterator);

	if (shape_iterator != shapes.end())
		shapes.erase(shape_iterator);
}

void PhysicsServer2D::tick_world(const std::unique_ptr<WorldType> &world, double delta) {
	world->step(delta);
}

void PhysicsServer2D::transfer_body_to_world(const BodiesType &physics_body, uid world_uid) {
	Optional<WorldsType&> world = get_world_from_uid(world_uid);
	if (!world)
		return;

	physics_body->set_world_uid(world_uid);
	world.get_value()->add_body(physics_body.get());
}

Optional<PhysicsServer2D::WorldsType&> PhysicsServer2D::get_world_from_uid(uid world_uid) {
	auto iterator = worlds.find(world_uid);

	if (iterator != worlds.end())
		return iterator->second;
	return NullOption;
}

Optional<const PhysicsServer2D::WorldsType&> PhysicsServer2D::get_world_from_uid(uid world_uid) const {
	auto iterator = worlds.find(world_uid);

	if (iterator != worlds.end())
		return iterator->second;
	return NullOption;
}

Optional<PhysicsServer2D::BodiesType&> PhysicsServer2D::get_physics_body_from_uid(uid body_uid) {
	auto iterator = bodies.find(body_uid);

	if (iterator != bodies.end())
		return iterator->second;
	return NullOption;
}

Optional<const PhysicsServer2D::BodiesType&> PhysicsServer2D::get_physics_body_from_uid(uid body_uid) const {
	auto iterator = bodies.find(body_uid);

	if (iterator != bodies.end())
		return iterator->second;
	return NullOption;
}

Optional<PhysicsServer2D::ShapesType&> PhysicsServer2D::get_physics_shape_from_uid(uid world_uid) {
	auto iterator = shapes.find(world_uid);

	if (iterator != shapes.end())
		return iterator->second;
	return NullOption;
}

Optional<const PhysicsServer2D::ShapesType&> PhysicsServer2D::get_physics_shape_from_uid(uid world_uid) const {
	auto iterator = shapes.find(world_uid);

	if (iterator != shapes.end())
		return iterator->second;
	return NullOption;
}

PhysicsServer2D::PhysicsServer2D(): gravity(PhysicsInfo::default_gravity), uid_index(1) {
}

PhysicsServer2D::~PhysicsServer2D() {
	for (const auto &iterator: bodies)
		destroy_uid(iterator.first);

	for (const auto &iterator: shapes)
		destroy_uid(iterator.first);
	worlds.clear();
}

void PhysicsServer2D::remove_uid(uid object_uid) {
	destroy_uid(object_uid);
}

void PhysicsServer2D::tick(double delta) {
	for (const auto &iterator: worlds)
		tick_world(iterator.second, delta);
}

uid PhysicsServer2D::create_world() {
	uid assigned_uid = assign_uid();
	std::unique_ptr<WorldType> world = _create_world();
	worlds.insert_or_assign(assigned_uid, std::move(world));
	return assigned_uid;
}

Optional<uid> PhysicsServer2D::static_body_create(uid world_uid) {
	Optional<WorldsType&> world = get_world_from_uid(world_uid);
	if (!world)
		return NullOption;

	uid assigned_uid = assign_uid();
	BodiesType body = _create_static_body(*world);
	bodies.insert_or_assign(assigned_uid, std::move(body));
	return assigned_uid;
}

Optional<uid> PhysicsServer2D::kinematic_body_create(uid world_uid) {
	Optional<WorldsType&> world = get_world_from_uid(world_uid);
	if (!world)
		return NullOption;

	uid assigned_uid = assign_uid();
	BodiesType body = _create_kinematic_body(*world);
	bodies.insert_or_assign(assigned_uid, std::move(body));
	return assigned_uid;
}

Optional<uid> PhysicsServer2D::dynamic_body_create(uid world_uid) {
	Optional<WorldsType&> world = get_world_from_uid(world_uid);
	if (!world)
		return NullOption;

	uid assigned_uid = assign_uid();
	BodiesType body = _create_dynamic_body(*world);
	bodies.insert_or_assign(assigned_uid, std::move(body));
	return assigned_uid;
}

uid PhysicsServer2D::capsule_shape_create(double height, double radius) {
	uid assigned_uid = assign_uid();
	ShapesType shape = _create_capsule_shape(height, radius);
	shapes.insert_or_assign(assigned_uid, std::move(shape));
	return assigned_uid;
}

uid PhysicsServer2D::circle_shape_create(double radius) {
	uid assigned_uid = assign_uid();
	ShapesType shape = _create_circle_shape(radius);
	shapes.insert_or_assign(assigned_uid, std::move(shape));
	return assigned_uid;
}

uid PhysicsServer2D::concave_polygon_shape_create(std::vector<Vector2f> &&segments) {
	uid assigned_uid = assign_uid();
	ShapesType shape = _create_concave_polygon_shape(std::move(segments));
	shapes.insert_or_assign(assigned_uid, std::move(shape));
	return assigned_uid;
}

uid PhysicsServer2D::convex_polygon_shape_create(std::vector<Vector2f> &&vertices) {
	uid assigned_uid = assign_uid();
	ShapesType shape = _create_convex_polygon_shape(std::move(vertices));
	shapes.insert_or_assign(assigned_uid, std::move(shape));
	return assigned_uid;
}

uid PhysicsServer2D::rect_shape_create(const Vector2f &size) {
	uid assigned_uid = assign_uid();
	ShapesType shape = _create_rect_shape(size);
	shapes.insert_or_assign(assigned_uid, std::move(shape));
	return assigned_uid;
}

uid PhysicsServer2D::segment_shape_create(const Vector2f &point_a, const Vector2f &point_b) {
	uid assigned_uid = assign_uid();
	ShapesType shape = _create_segment_shape(point_a, point_b);
	shapes.insert_or_assign(assigned_uid, std::move(shape));
	return assigned_uid;
}

uid PhysicsServer2D::world_boundary_shape_create(double distance, const Vector2f &normal) {
	uid assigned_uid = assign_uid();
	ShapesType shape = _create_world_boundary_shape(distance, normal);
	shapes.insert_or_assign(assigned_uid, std::move(shape));
	return assigned_uid;
}

void PhysicsServer2D::world_set_gravity(uid world_uid, const Vector2f &world_gravity) {
	Optional<WorldsType&> world = get_world_from_uid(world_uid); 
	
	if (world)
		world.get_value()->set_gravity(world_gravity);
}

Optional<Vector2f> PhysicsServer2D::world_get_gravity(uid world_uid) const {
	Optional<const WorldsType&> world = get_world_from_uid(world_uid);

	if (world)
		return world.get_value()->get_gravity();
	return NullOption;
}

void PhysicsServer2D::world_set_velocity_iterations(uid world_uid, int32_t velocity_iterations) {
	Optional<WorldsType&> world = get_world_from_uid(world_uid);

	if (world)
		world.get_value()->set_velocity_iterations(velocity_iterations);
}

Optional<int32_t> PhysicsServer2D::world_get_velocity_iterations(uid world_uid) const {
	Optional<const WorldsType&> world = get_world_from_uid(world_uid);

	if (world)
		return world.get_value()->get_velocity_iterations();
	return NullOption;
}

void PhysicsServer2D::world_set_position_iterations(uid world_uid, int32_t position_iterations) {
	Optional<WorldsType&> world = get_world_from_uid(world_uid);

	if (world)
		world.get_value()->set_position_iterations(position_iterations);
}

Optional<int32_t> PhysicsServer2D::world_get_position_iterations(uid world_uid) const {
	Optional<const WorldsType&> world = get_world_from_uid(world_uid);

	if (world)
		return world.get_value()->get_position_iterations();
	return NullOption;
}

void PhysicsServer2D::body_set_world(uid body_uid, uid world_uid) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);
	Optional<WorldsType&> world = get_world_from_uid(world_uid);

	if (body && world)
		transfer_body_to_world(body.get_value(), world_uid);
}

Optional<uid> PhysicsServer2D::body_get_world(uid body_uid) const {
	Optional<const BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		return body.get_value()->get_world_uid();	
	return NullOption;
}

void PhysicsServer2D::body_set_transform(uid body_uid, const Transform2D &transform) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		body.get_value()->set_transform(transform);
}

Optional<Transform2D> PhysicsServer2D::body_get_transform(uid body_uid) const {
	Optional<const BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		return body.get_value()->get_transform();
	return NullOption;
}


#endif