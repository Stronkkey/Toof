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
#ifdef TOOF_PHYSICS_ENABLED
#pragma once

#include <core/math/transform2d.hpp>
#include <core/memory/optional.hpp>

#include <memory>
#include <unordered_map>

namespace Toof {

struct PhysicsWorld2D;
struct PhysicsBody2D;
class PhysicsShape2D;
class PhysicsShapeCapsule2D;
class PhysicsShapeCircle2D;
class PhysicsShapeConcavePolygon2D;
class PhysicsShapeConvexPolygon2D;
class PhysicsShapeRect2D;
class PhysicsShapeSegment2D;
class PhysicsShapeWorldBoundary2D;

class PhysicsServer2D {
protected:
	using WorldType = PhysicsWorld2D;
	using BodyType = PhysicsBody2D;
	using ShapeType = PhysicsShape2D;
	using CapsuleShapeType = PhysicsShapeCapsule2D;
	using CircleShapeType = PhysicsShapeCircle2D;
	using ConcavePolygonShapeType = PhysicsShapeConcavePolygon2D;
	using ConvexPolygonShapeType = PhysicsShapeConvexPolygon2D;
	using RectShapeType = PhysicsShapeRect2D;
	using SegmentShapeType = PhysicsShapeSegment2D;
	using WorldBoundaryShapeType = PhysicsShapeWorldBoundary2D;
private:
	std::unordered_map<uid, std::unique_ptr<WorldType>> worlds;
	std::unordered_map<uid, std::unique_ptr<BodyType>> bodies;
	std::unordered_map<uid, std::unique_ptr<PhysicsShape2D>> shapes;

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
	virtual std::unique_ptr<CapsuleShapeType> _create_capsule_shape(double height, double radius) =0;
	virtual std::unique_ptr<CircleShapeType> _create_circle_shape(double radius) =0;
	virtual std::unique_ptr<ConcavePolygonShapeType> _create_concave_polygon_shape(std::vector<Vector2f> &&segments) =0;
	virtual std::unique_ptr<ConvexPolygonShapeType> _create_convex_polygon_shape(std::vector<Vector2f> &&vertices) =0;
	virtual std::unique_ptr<RectShapeType> _create_rect_shape(const Vector2f &size) =0;
	virtual std::unique_ptr<SegmentShapeType> _create_segment_shape(const Vector2f &point_a, const Vector2f &point_b) =0;
	virtual std::unique_ptr<WorldBoundaryShapeType> _create_world_boundary_shape(double distance, const Vector2f &normal) =0;
private:
	constexpr uid assign_uid() {
		uid assigned_uid = uid_index++;
		return uid_index == 0 ? uid_index++ : assigned_uid;
	}

	void destroy_uid(uid object_uid);
	void tick_world(const WorldsType &world, double delta);
	void transfer_body_to_world(const BodiesType &physics_body, uid world_uid);

	Optional<WorldsType&> get_world_from_uid(uid world_uid);
	Optional<const WorldsType&> get_world_from_uid(uid world_uid) const;	
	Optional<BodiesType&> get_physics_body_from_uid(uid body_uid);
	Optional<const BodiesType&> get_physics_body_from_uid(uid body_uid) const;	
	Optional<ShapesType&> get_physics_shape_from_uid(uid shape_uid);
	Optional<const ShapesType&> get_physics_shape_from_uid(uid shape_uid) const;	
public:
	PhysicsServer2D();
	~PhysicsServer2D();
	
	void remove_uid(uid object_uid);
	void tick(double delta);

	uid create_world();
	Optional<uid> static_body_create(uid world_uid);
	Optional<uid> kinematic_body_create(uid world_uid);
	Optional<uid> dynamic_body_create(uid world_uid);
	uid capsule_shape_create(double height = 30, double radius = 10);
	uid circle_shape_create(double radius = 10);
	uid concave_polygon_shape_create(std::vector<Vector2f> &&segments = {});
	uid convex_polygon_shape_create(std::vector<Vector2f> &&vertices = {});
	uid rect_shape_create(const Vector2f &size = {20, 20});
	uid segment_shape_create(const Vector2f &point_a = {}, const Vector2f &point_b = {0, 10});
	uid world_boundary_shape_create(double distance = 0, const Vector2f &normal = {0, -1});

	void world_set_gravity(uid world_uid, const Vector2f &world_gravity);
	Optional<Vector2f> world_get_gravity(uid world_uid) const;

	void world_set_velocity_iterations(uid world_uid, int32_t velocity_iterations);
	Optional<int32_t> world_get_velocity_iterations(uid world_uid) const;

	void world_set_position_iterations(uid world_uid, int32_t position_iterations);
	Optional<int32_t> world_get_position_iterations(uid world_uid) const;

	void body_set_world(uid body_uid, uid world_uid);
	Optional<uid> body_get_world(uid body_uid) const;

	void body_set_transform(uid body_uid, const Transform2D &transform);
	Optional<Transform2D> body_get_transform(uid body_uid) const;
};

}

#endif