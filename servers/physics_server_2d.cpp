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
#include <physics/2d/physics_world.hpp>
#include <physics/2d/physics_body.hpp>
#include <physics/2d/physics_shape.hpp>
#include <physics/2d/physics_info.hpp>
#include <servers/physics_server_2d.hpp>

#if TOOF_PHYSICS_ENABLED

using namespace Toof;

PhysicsServer2D::ContactInfo::ContactInfo(const Physics2DContact &contact) : entered(contact.touching),
    local_position(contact.local_position),
    shape_id(contact.shape_id),
    body_uid(contact.body->get_body_uid()),
    body_shape_id(contact.body_shape_id) {
}

void PhysicsServer2D::destroy_uid(uid object_uid) {
	auto world_iterator = worlds.find(object_uid);
	auto body_iterator = bodies.find(object_uid);
	auto shape_iterator = shapes.find(object_uid);

	if (world_iterator != worlds.end())
		worlds.erase(world_iterator);

	if (body_iterator != bodies.end()) {
		Physics2DBody *body = body_iterator->second.get();
		for (const auto &shape : body->get_shapes())
			shape->remove_body(body);
		bodies.erase(body_iterator);
	}

	if (shape_iterator != shapes.end()) {
		Physics2DShape *shape = shape_iterator->second.get();
		for (const auto &body : shape->get_bodies())
			body->remove_shape(shape);
		shapes.erase(shape_iterator);
	}
}

void PhysicsServer2D::tick_world(const std::unique_ptr<WorldType> &world, real delta) {
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

PhysicsServer2D::PhysicsServer2D(): gravity(TOOF_DEFAULT_GRAVITY), uid_index(1) {
}

PhysicsServer2D::~PhysicsServer2D() {
	worlds.clear();
	bodies.clear();
	shapes.clear();
}

void PhysicsServer2D::free_uid(uid object_uid) {
	destroy_uid(object_uid);
}

void PhysicsServer2D::tick(real delta) {
	for (const auto &iterator: worlds)
		tick_world(iterator.second, delta);
}

uid PhysicsServer2D::create_world() {
	uid assigned_uid = assign_uid();
	std::unique_ptr<WorldType> world = _create_world();

	world->set_gravity(gravity);
	world->set_position_iterations(6);
	world->set_velocity_iterations(2);

	worlds.insert_or_assign(assigned_uid, std::move(world));
	return assigned_uid;
}

void set_body_default_properties(const std::unique_ptr<Physics2DBody> &body, uid world_uid) {
	body->set_world_uid(world_uid);
	body->set_angular_damping(0);
	body->set_angular_velocity(0);
	body->set_linear_damping(0);
	body->set_linear_velocity(Vector2f::ZERO());
	body->set_awake(true);
	body->set_ccd_active(false);
	body->set_gravity_scale(1);
	body->set_rotation_fixed(false);
	body->set_transform(Transform2D::IDENTITY);
	body->set_sleeping_allowed(true);
	body->set_area(false);
	body->set_density(1);
	body->set_friction(1);
	body->set_restitution(0);
	body->set_restitution_threshold(0);
	body->set_rotation_fixed(false);
	body->set_constant_torque(0);
	body->set_constant_force(Vector2f::ZERO());
}

Optional<uid> PhysicsServer2D::static_body_create(uid world_uid) {
	Optional<WorldsType&> world = get_world_from_uid(world_uid);
	if (!world)
		return NullOption;

	uid assigned_uid = assign_uid();
	BodiesType body = _create_static_body(*world);

	set_body_default_properties(body, world_uid);

	bodies.insert_or_assign(assigned_uid, std::move(body));
	return assigned_uid;
}

Optional<uid> PhysicsServer2D::kinematic_body_create(uid world_uid) {
	Optional<WorldsType&> world = get_world_from_uid(world_uid);
	if (!world)
		return NullOption;

	uid assigned_uid = assign_uid();
	BodiesType body = _create_kinematic_body(*world);
	
	set_body_default_properties(body, world_uid);
	
	bodies.insert_or_assign(assigned_uid, std::move(body));
	return assigned_uid;
}

Optional<uid> PhysicsServer2D::dynamic_body_create(uid world_uid) {
	Optional<WorldsType&> world = get_world_from_uid(world_uid);
	if (!world)
		return NullOption;

	uid assigned_uid = assign_uid();
	BodiesType body = _create_dynamic_body(*world);
	
	set_body_default_properties(body, world_uid);

	bodies.insert_or_assign(assigned_uid, std::move(body));
	return assigned_uid;
}

uid PhysicsServer2D::capsule_shape_create(real height, real radius) {
	uid assigned_uid = assign_uid();
	std::unique_ptr<CapsuleShapeType> shape = _create_capsule_shape(height, radius);
	shapes.insert_or_assign(assigned_uid, std::move(shape));
	return assigned_uid;
}

uid PhysicsServer2D::circle_shape_create(real radius) {
	uid assigned_uid = assign_uid();
	std::unique_ptr<CircleShapeType> shape = _create_circle_shape(radius);
	shapes.insert_or_assign(assigned_uid, std::move(shape));
	return assigned_uid;
}

uid PhysicsServer2D::concave_polygon_shape_create(const std::vector<Vector2f> &segments) {
	uid assigned_uid = assign_uid();
	ShapesType shape = _create_concave_polygon_shape(segments);
	shapes.insert_or_assign(assigned_uid, std::move(shape));
	return assigned_uid;
}

uid PhysicsServer2D::convex_polygon_shape_create(const std::vector<Vector2f> &vertices) {
	uid assigned_uid = assign_uid();
	ShapesType shape = _create_convex_polygon_shape(vertices);
	shapes.insert_or_assign(assigned_uid, std::move(shape));
	return assigned_uid;
}

uid PhysicsServer2D::rect_shape_create(const Vector2f &size) {
	uid assigned_uid = assign_uid();
	std::unique_ptr<RectShapeType> shape = _create_rect_shape(size);
	shapes.insert_or_assign(assigned_uid, std::move(shape));
	return assigned_uid;
}

uid PhysicsServer2D::segment_shape_create(const Vector2f &point_a, const Vector2f &point_b) {
	uid assigned_uid = assign_uid();
	ShapesType shape = _create_segment_shape(point_a, point_b);
	shapes.insert_or_assign(assigned_uid, std::move(shape));
	return assigned_uid;
}

uid PhysicsServer2D::world_boundary_shape_create(real distance, const Vector2f &normal) {
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

void PhysicsServer2D::body_set_angular_damping(uid body_uid, real angular_damping) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		body.get_value()->set_angular_damping(angular_damping);
}

Optional<real> PhysicsServer2D::body_get_angular_damping(uid body_uid) const {
	Optional<const BodiesType&> body = get_physics_body_from_uid(body_uid);
	
	if (body)
		return body.get_value()->get_angular_damping();
	return NullOption;
}

void PhysicsServer2D::body_set_angular_velocity(uid body_uid, real angular_velocity) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		body.get_value()->set_angular_velocity(angular_velocity);
}

Optional<real> PhysicsServer2D::body_get_angular_velocity(uid body_uid) const {
	Optional<const BodiesType&> body = get_physics_body_from_uid(body_uid);
	
	if (body)
		return body.get_value()->get_angular_velocity();
	return NullOption;
}

void PhysicsServer2D::body_set_area(uid body_uid, bool area) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		body.get_value()->set_area(area);
}

Optional<bool> PhysicsServer2D::body_is_area(uid body_uid) const {
	Optional<const BodiesType&> body = get_physics_body_from_uid(body_uid);
	
	if (body)
		return body.get_value()->is_area();
	return NullOption;
}

void PhysicsServer2D::body_set_awake(uid body_uid, bool awake) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		body.get_value()->set_awake(awake);
}

Optional<bool> PhysicsServer2D::body_is_awake(uid body_uid) const {
	Optional<const BodiesType&> body = get_physics_body_from_uid(body_uid);
	
	if (body)
		return body.get_value()->is_awake();
	return NullOption;
}

void PhysicsServer2D::body_set_ccd_active(uid body_uid, bool ccd_active) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		body.get_value()->set_ccd_active(ccd_active);
}

Optional<bool> PhysicsServer2D::body_is_ccd_active(uid body_uid) const {
	Optional<const BodiesType&> body = get_physics_body_from_uid(body_uid);
	
	if (body)
		return body.get_value()->is_ccd_active();
	return NullOption;
}

void PhysicsServer2D::body_set_density(uid body_uid, real density) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		body.get_value()->set_density(density);
}

Optional<real> PhysicsServer2D::body_get_density(uid body_uid) const {
	Optional<const BodiesType&> body = get_physics_body_from_uid(body_uid);
	
	if (body)
		return body.get_value()->get_density();
	return NullOption;
}

void PhysicsServer2D::body_set_friction(uid body_uid, real friction) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		body.get_value()->set_friction(friction);
}

Optional<real> PhysicsServer2D::body_get_friction(uid body_uid) const {
	Optional<const BodiesType&> body = get_physics_body_from_uid(body_uid);
	
	if (body)
		return body.get_value()->get_friction();
	return NullOption;
}

void PhysicsServer2D::body_set_gravity_scale(uid body_uid, real gravity_scale) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		body.get_value()->set_gravity_scale(gravity_scale);
}

Optional<real> PhysicsServer2D::body_get_gravity_scale(uid body_uid) const {
	Optional<const BodiesType&> body = get_physics_body_from_uid(body_uid);
	
	if (body)
		return body.get_value()->get_gravity_scale();
	return NullOption;
}

void PhysicsServer2D::body_set_linear_damping(uid body_uid, real linear_damping) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		body.get_value()->set_linear_damping(linear_damping);
}

Optional<real> PhysicsServer2D::body_get_linear_damping(uid body_uid) const {
	Optional<const BodiesType&> body = get_physics_body_from_uid(body_uid);
	
	if (body)
		return body.get_value()->get_linear_damping();
	return NullOption;
}

void PhysicsServer2D::body_set_linear_velocity(uid body_uid, const Vector2f &linear_velocity) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		body.get_value()->set_linear_velocity(linear_velocity);
}

Optional<Vector2f> PhysicsServer2D::body_get_linear_velocity(uid body_uid) const {
	Optional<const BodiesType&> body = get_physics_body_from_uid(body_uid);
	
	if (body)
		return body.get_value()->get_linear_velocity();
	return NullOption;
}

void PhysicsServer2D::body_set_restitution(uid body_uid, real restitution) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		body.get_value()->set_restitution(restitution);
}

Optional<real> PhysicsServer2D::body_get_restitution(uid body_uid) const {
	Optional<const BodiesType&> body = get_physics_body_from_uid(body_uid);
	
	if (body)
		return body.get_value()->get_restitution();
	return NullOption;
}

void PhysicsServer2D::body_set_restitution_threshold(uid body_uid, real restitution_threshold) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		body.get_value()->set_restitution_threshold(restitution_threshold);
}

Optional<real> PhysicsServer2D::body_get_restitution_threshold(uid body_uid) const {
	Optional<const BodiesType&> body = get_physics_body_from_uid(body_uid);
	
	if (body)
		return body.get_value()->get_restitution_threshold();
	return NullOption;
}

void PhysicsServer2D::body_set_rotation_fixed(uid body_uid, bool rotation_fixed) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		body.get_value()->set_rotation_fixed(rotation_fixed);
}

Optional<bool> PhysicsServer2D::body_is_rotation_fixed(uid body_uid) const {
	Optional<const BodiesType&> body = get_physics_body_from_uid(body_uid);
	
	if (body)
		return body.get_value()->is_rotation_fixed();
	return NullOption;
}

void PhysicsServer2D::body_set_sleeping_allowed(uid body_uid, bool sleeping_allowed) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		body.get_value()->set_sleeping_allowed(sleeping_allowed);
}

Optional<bool> PhysicsServer2D::body_is_sleeping_allowed(uid body_uid) const {
	Optional<const BodiesType&> body = get_physics_body_from_uid(body_uid);
	
	if (body)
		return body.get_value()->is_sleeping_allowed();
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

void PhysicsServer2D::body_set_position(uid body_uid, const Vector2f &position) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		body.get_value()->set_position(position);
}

Optional<Vector2f> PhysicsServer2D::body_get_position(uid body_uid) const {
	Optional<const BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		return body.get_value()->get_position();
	return NullOption;
}

void PhysicsServer2D::body_set_rotation(uid body_uid, const Angle &rotation) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		body.get_value()->set_rotation(rotation);
}

Optional<Angle> PhysicsServer2D::body_get_rotation(uid body_uid) const {
	Optional<const BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		return body.get_value()->get_rotation();
	return NullOption;
}

void PhysicsServer2D::body_set_scale(uid body_uid, const Vector2f &scale) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		body.get_value()->set_scale(scale);
}

Optional<Vector2f> PhysicsServer2D::body_get_scale(uid body_uid) const {
	Optional<const BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		return body.get_value()->get_scale();
	return NullOption;
}

void PhysicsServer2D::body_set_constant_torque(uid body_uid, real constant_torque) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		body.get_value()->set_constant_torque(constant_torque);
}

Optional<real> PhysicsServer2D::body_get_constant_torque(uid body_uid) const {
	Optional<const BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		return body.get_value()->get_constant_torque();
	return NullOption;
}

void PhysicsServer2D::body_set_constant_force(uid body_uid, const Vector2f &constant_force) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		body.get_value()->set_constant_force(constant_force);
}

Optional<Vector2f> PhysicsServer2D::body_get_constant_force(uid body_uid) const {
	Optional<const BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		return body.get_value()->get_constant_force();
	return NullOption;
}

Optional<int> PhysicsServer2D::body_add_shape(uid body_uid, uid shape_uid) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);
	Optional<ShapesType&> shape = get_physics_shape_from_uid(shape_uid);

	if (!body || !shape)
		return NullOption;

	body.get_value()->add_shape(shape->get());
	shape.get_value()->add_body(body->get());
	return body.get_value()->get_shapes().size() - 1;
}

void PhysicsServer2D::body_remove_shape(uid body_uid, int shape_idx) {
	Optional<BodiesType&> body = get_physics_body_from_uid(body_uid);
	if (!body)
		return;

	Physics2DShape *shape = body.get_value()->get_shape(shape_idx);
	if (!shape)
		return;

	shape->remove_body(body->get());
	body.get_value()->remove_shape(shape);
}

Optional<PhysicsBodyType> PhysicsServer2D::body_get_type(uid body_uid) const {
	Optional<const BodiesType&> body = get_physics_body_from_uid(body_uid);

	if (body)
		return body.get_value()->get_body_type();
	return NullOption;
}

Signal<PhysicsServer2D::ContactInfo> &PhysicsServer2D::body_get_monitor_signal(uid body_uid) {
	return body_monitor_signals.insert({body_uid, {}}).first->second;
}

void PhysicsServer2D::_body_register_contact(uid body_uid, const Physics2DContact &contact) {
	auto iterator = body_monitor_signals.find(body_uid);

	if (iterator != body_monitor_signals.end())
		iterator->second(contact);
}

#endif
