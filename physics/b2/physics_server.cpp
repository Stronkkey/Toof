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

#include <physics/b2/physics_server.hpp>

#include <physics/physics_object_interface.hpp>
#include <physics/b2/physics_world.hpp>
#include <physics/b2/physics_body.hpp>
#include <physics/b2/physics_shape.hpp>

#include <box2d/b2_body.h>

using namespace Toof;

std::unique_ptr<PhysicsServer2D::WorldType> B2PhysicsServer::_create_world() {
	std::unique_ptr<B2PhysicsWorld> world = std::make_unique<B2PhysicsWorld>();
	return world;
}

std::unique_ptr<PhysicsServer2D::BodyType> B2PhysicsServer::_create_static_body(std::unique_ptr<WorldType> &world) {
	B2PhysicsWorld *physics_world = reinterpret_cast<B2PhysicsWorld*>(world.get());
	std::unique_ptr<B2PhysicsBody> body = std::make_unique<B2PhysicsBody>();
	b2BodyDef body_definition = {};

	body_definition.type = b2_staticBody;
	body->set_body(physics_world->get_world().CreateBody(&body_definition));

	return body;
}

std::unique_ptr<PhysicsServer2D::BodyType> B2PhysicsServer::_create_kinematic_body(std::unique_ptr<WorldType> &world) {
	B2PhysicsWorld *physics_world = reinterpret_cast<B2PhysicsWorld*>(world.get());
	std::unique_ptr<B2PhysicsBody> body = std::make_unique<B2PhysicsBody>();
	b2BodyDef body_definition = {};

	body_definition.type = b2_kinematicBody;
	body->set_body(physics_world->get_world().CreateBody(&body_definition));

	return body;
}

std::unique_ptr<PhysicsServer2D::BodyType> B2PhysicsServer::_create_dynamic_body(std::unique_ptr<WorldType> &world) {
	B2PhysicsWorld *physics_world = reinterpret_cast<B2PhysicsWorld*>(world.get());
	std::unique_ptr<B2PhysicsBody> body = std::make_unique<B2PhysicsBody>();
	b2BodyDef body_definition = {};

	body_definition.type = b2_dynamicBody;
	body->set_body(physics_world->get_world().CreateBody(&body_definition));

	return body;
}

std::unique_ptr<PhysicsServer2D::CapsuleShapeType> B2PhysicsServer::_create_capsule_shape(double height, double radius) {
	std::unique_ptr<B2PhysicsCapsuleShape> capsule_shape = std::make_unique<B2PhysicsCapsuleShape>();
	capsule_shape->set_height(height);
	capsule_shape->set_radius(radius);
	return capsule_shape;
}

std::unique_ptr<PhysicsServer2D::CircleShapeType> B2PhysicsServer::_create_circle_shape(double radius) {
	std::unique_ptr<B2PhysicsCircleShape> circle_shape = std::make_unique<B2PhysicsCircleShape>();
	circle_shape->set_radius(radius);
	return circle_shape;
}

std::unique_ptr<PhysicsServer2D::ConcavePolygonShapeType> B2PhysicsServer::_create_concave_polygon_shape(std::vector<Vector2f> &&segments) {
	std::unique_ptr<B2PhysicsConcavePolygonShape> concave_shape = std::make_unique<B2PhysicsConcavePolygonShape>();
	concave_shape->set_segments(std::move(segments));
	return concave_shape;
}

std::unique_ptr<PhysicsServer2D::ConvexPolygonShapeType> B2PhysicsServer::_create_convex_polygon_shape(std::vector<Vector2f> &&vertices) {
	std::unique_ptr<B2PhysicsConvexPolygonShape> convex_shape = std::make_unique<B2PhysicsConvexPolygonShape>();
	convex_shape->set_vertices(std::move(vertices));
	return convex_shape;
}

std::unique_ptr<PhysicsServer2D::RectShapeType> B2PhysicsServer::_create_rect_shape(const Vector2f &size) {
	std::unique_ptr<B2PhysicsRectShape> rect_shape = std::make_unique<B2PhysicsRectShape>();
	rect_shape->set_size(size);
	return rect_shape;
}

std::unique_ptr<PhysicsServer2D::SegmentShapeType> B2PhysicsServer::_create_segment_shape(const Vector2f &point_a, const Vector2f &point_b) {
	std::unique_ptr<B2PhysicsSegmentShape> segment_shape = std::make_unique<B2PhysicsSegmentShape>();
	segment_shape->set_a(point_a);
	segment_shape->set_b(point_b);
	return segment_shape;
}

std::unique_ptr<PhysicsServer2D::WorldBoundaryShapeType> B2PhysicsServer::_create_world_boundary_shape(double distance, const Vector2f &normal) {
	std::unique_ptr<B2PhysicsWorldBoundaryShape> world_boundary = std::make_unique<B2PhysicsWorldBoundaryShape>();
	world_boundary->set_distance(distance);
	world_boundary->set_normal(normal);
	return world_boundary;
}

#endif
