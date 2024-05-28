/*  This file is part of the Toof Engine. */
/** @file physics_server.hpp */
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

#include <core/math/transform2d.hpp>
#include <core/memory/optional.hpp>
#include <physics/2d/physics_body_type.hpp>

#include <memory>
#include <unordered_map>

#if TOOF_PHYSICS_ENABLED

namespace Toof {

struct PhysicsWorld2D;
struct Physics2DBody;
class Physics2DContact;
class Physics2DShape;
class Physics2DShapeCapsule;
class Physics2DShapeCircle;
class Physics2DShapeConcavePolygon;
class Physics2DShapeConvexPolygon;
class Physics2DShapeRect;
class Physics2DShapeSegment;
class Physics2DShapeWorldBoundary;

template<class...>
class Signal;

class PhysicsServer2D {
public:
	class ContactInfo {
	private:
		bool entered;
		Vector2f local_position;
		int shape_id;
		uid body_uid;
		int body_shape_id;

		friend PhysicsServer2D;
 		ContactInfo() = default;
		ContactInfo(const Physics2DContact &contact);
	public:
		~ContactInfo() = default;

		constexpr bool has_entered() const {
			return entered;
		}

		constexpr Vector2f get_local_position() const {
			return local_position;
		}

		constexpr int get_shape_id() const {
			return shape_id;
		}

		constexpr uid get_body_uid() const {
			return body_uid;
		}

		constexpr int get_body_shape_id() const {
			return body_shape_id;
		}
	};
protected:
	using WorldType = PhysicsWorld2D;
	using BodyType = Physics2DBody;
	using ShapeType = Physics2DShape;
	using CapsuleShapeType = Physics2DShapeCapsule;
	using CircleShapeType = Physics2DShapeCircle;
	using ConcavePolygonShapeType = Physics2DShapeConcavePolygon;
	using ConvexPolygonShapeType = Physics2DShapeConvexPolygon;
	using RectShapeType = Physics2DShapeRect;
	using SegmentShapeType = Physics2DShapeSegment;
	using WorldBoundaryShapeType = Physics2DShapeWorldBoundary;
private:
	std::unordered_map<uid, std::unique_ptr<WorldType>> worlds;
	std::unordered_map<uid, std::unique_ptr<BodyType>> bodies;
	std::unordered_map<uid, std::unique_ptr<ShapeType>> shapes;
	std::unordered_map<uid, Signal<ContactInfo>> body_monitor_signals;

	using WorldsType = decltype(worlds)::mapped_type;
	using BodiesType = decltype(bodies)::mapped_type;
	using ShapesType = decltype(shapes)::mapped_type;

	Vector2f gravity;
	uid uid_index;
protected:
	virtual std::unique_ptr<WorldType> _create_world() =0;
	virtual std::unique_ptr<BodyType> _create_static_body(std::unique_ptr<WorldType> &world_type) =0;
	virtual std::unique_ptr<BodyType> _create_kinematic_body(std::unique_ptr<WorldType> &world_type) =0;
	virtual std::unique_ptr<BodyType> _create_dynamic_body(std::unique_ptr<WorldType> &world_type) =0;
	virtual std::unique_ptr<CapsuleShapeType> _create_capsule_shape(real height, real radius) =0;
	virtual std::unique_ptr<CircleShapeType> _create_circle_shape(real radius) =0;
	virtual std::unique_ptr<ConcavePolygonShapeType> _create_concave_polygon_shape(const std::vector<Vector2f> &segments) =0;
	virtual std::unique_ptr<ConvexPolygonShapeType> _create_convex_polygon_shape(const std::vector<Vector2f> &vertices) =0;
	virtual std::unique_ptr<RectShapeType> _create_rect_shape(const Vector2f &size) =0;
	virtual std::unique_ptr<SegmentShapeType> _create_segment_shape(const Vector2f &point_a, const Vector2f &point_b) =0;
	virtual std::unique_ptr<WorldBoundaryShapeType> _create_world_boundary_shape(real distance, const Vector2f &normal) =0;
private:
	constexpr uid assign_uid() {
		uid assigned_uid = uid_index++;
		return uid_index == 0 ? uid_index++ : assigned_uid;
	}

	void destroy_uid(uid object_uid);
	void tick_world(const WorldsType &world, real delta);
	void transfer_body_to_world(const BodiesType &physics_body, uid world_uid);

	Optional<WorldsType&> get_world_from_uid(uid world_uid);
	Optional<const WorldsType&> get_world_from_uid(uid world_uid) const;	
	Optional<BodiesType&> get_physics_body_from_uid(uid body_uid);
	Optional<const BodiesType&> get_physics_body_from_uid(uid body_uid) const;	
	Optional<ShapesType&> get_physics_shape_from_uid(uid shape_uid);
	Optional<const ShapesType&> get_physics_shape_from_uid(uid shape_uid) const;
	void _set_body_default_properties(const std::unique_ptr<Physics2DBody> &body, uid world_uid) const;
public:
	PhysicsServer2D();
	~PhysicsServer2D();

	void free_uid(uid object_uid);
	void tick(real delta);

	uid create_world();
	Optional<uid> static_body_create(uid world_uid);
	Optional<uid> kinematic_body_create(uid world_uid);
	Optional<uid> dynamic_body_create(uid world_uid);
	uid capsule_shape_create(real height = 30, real radius = 10);
	uid circle_shape_create(real radius = 10);
	uid concave_polygon_shape_create(const std::vector<Vector2f> &segments = {});
	uid convex_polygon_shape_create(const std::vector<Vector2f> &vertices = {});
	uid rect_shape_create(const Vector2f &size = {20, 20});
	uid segment_shape_create(const Vector2f &point_a = {}, const Vector2f &point_b = {0, 10});
	uid world_boundary_shape_create(real distance = 0, const Vector2f &normal = {0, -1});

	void world_set_gravity(uid world_uid, const Vector2f &world_gravity);
	Optional<Vector2f> world_get_gravity(uid world_uid) const;

	void world_set_velocity_iterations(uid world_uid, int32_t velocity_iterations);
	Optional<int32_t> world_get_velocity_iterations(uid world_uid) const;

	void world_set_position_iterations(uid world_uid, int32_t position_iterations);
	Optional<int32_t> world_get_position_iterations(uid world_uid) const;

	void body_set_world(uid body_uid, uid world_uid);
	Optional<uid> body_get_world(uid body_uid) const;

	void body_set_angular_damping(uid body_uid, real angular_damping);
	Optional<real> body_get_angular_damping(uid body_uid) const;

	void body_set_angular_velocity(uid body_uid, real angular_velocity);
	Optional<real> body_get_angular_velocity(uid body_uid) const;

	void body_set_area(uid body_uid, bool area);
	Optional<bool> body_is_area(uid body_uid) const;
	
	void body_set_awake(uid body_uid, bool awake);
	Optional<bool> body_is_awake(uid body_uid) const;

	void body_set_ccd_active(uid body_uid, bool ccd_active);
	Optional<bool> body_is_ccd_active(uid body_uid) const;

	void body_set_density(uid body_uid, real density);
	Optional<real> body_get_density(uid body_uid) const;

	void body_set_friction(uid body_uid, real friction);
	Optional<real> body_get_friction(uid body_uid) const;

	void body_set_gravity_scale(uid body_uid, real gravity_scale);
	Optional<real> body_get_gravity_scale(uid body_uid) const;

	void body_set_linear_damping(uid body_uid, real linear_damping);
	Optional<real> body_get_linear_damping(uid body_uid) const;

	void body_set_linear_velocity(uid body_uid, const Vector2f &linear_velocity);
	Optional<Vector2f> body_get_linear_velocity(uid body_uid) const;

	void body_set_restitution(uid body_uid, real restitution);
	Optional<real> body_get_restitution(uid body_uid) const;

	void body_set_restitution_threshold(uid body_uid, real restitution_threshold);
	Optional<real> body_get_restitution_threshold(uid body_uid) const;

	void body_set_rotation_fixed(uid body_uid, bool rotation_fixed);
	Optional<bool> body_is_rotation_fixed(uid body_uid) const;

	void body_set_sleeping_allowed(uid body_uid, bool sleeping_allowed);
	Optional<bool> body_is_sleeping_allowed(uid body_uid) const;

	void body_set_transform(uid body_uid, const Transform2D &transform);
	Optional<Transform2D> body_get_transform(uid body_uid) const;

	void body_set_position(uid body_uid, const Vector2f &position);
	Optional<Vector2f> body_get_position(uid body_uid) const;

	void body_set_rotation(uid body_uid, const Angle &angle);
	Optional<Angle> body_get_rotation(uid body_uid) const;

	void body_set_scale(uid body_uid, const Vector2f &scale);
	Optional<Vector2f> body_get_scale(uid body_uid) const;

	void body_set_constant_torque(uid body_uid, real constant_torque);
	Optional<real> body_get_constant_torque(uid body_uid) const;

	void body_set_constant_force(uid body_uid, const Vector2f &constant_force);
	Optional<Vector2f> body_get_constant_force(uid body_uid) const;

	Optional<int> body_add_shape(uid body_uid, uid shape_uid);
	void body_remove_shape(uid body_uid, int shape_idx);
	Optional<PhysicsBodyType> body_get_type(uid body_uid) const;

	Signal<ContactInfo> &body_get_monitor_signal(uid body_uid);

	void _body_register_contact(uid body_uid, const Physics2DContact &contact);
};

}

#endif
