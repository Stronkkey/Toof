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

#include <core/math/vector2.hpp>
#include <physics/physics_object_interface.hpp>
#include <physics/2d/physics_shape.hpp>

using namespace Toof;

PhysicsShape2D::ShapeType PhysicsShape2D::get_shape_type() const {
	return ShapeType::NONE;
}

int PhysicsShape2D::get_type() const {
	return PHYSICS_OBJECT_INTERFACE_NONE;
}

PhysicsShape2D::ShapeType PhysicsShapeCapsule2D::get_shape_type() const {
	return ShapeType::CAPSULE;
}

void PhysicsShapeCapsule2D::set_height(double) {
}

void PhysicsShapeCapsule2D::set_radius(double) {
}

double PhysicsShapeCapsule2D::get_height() const {
	return 0;
}

double PhysicsShapeCapsule2D::get_radius() const {
	return 0;
}

PhysicsShape2D::ShapeType PhysicsShapeCircle2D::get_shape_type() const {
	return ShapeType::CIRCLE;
}

void PhysicsShapeCircle2D::set_radius(double) {
}

double PhysicsShapeCircle2D::get_radius() const {
	return 0;
}

PhysicsShape2D::ShapeType PhysicsShapeConcavePolygon2D::get_shape_type() const {
	return ShapeType::CONCAVE_POLYGON;
}

void PhysicsShapeConcavePolygon2D::set_segments(SegmentType&&) {
}

PhysicsShapeConcavePolygon2D::SegmentType PhysicsShapeConcavePolygon2D::get_segments() const {
	return {};
}

PhysicsShape2D::ShapeType PhysicsShapeRect2D::get_shape_type() const {
	return ShapeType::RECT;
}

PhysicsShape2D::ShapeType PhysicsShapeConvexPolygon2D::get_shape_type() const {
	return ShapeType::CONVEX_POLYGON;
}

void PhysicsShapeConvexPolygon2D::set_vertices(VerticesType&&) {
}

PhysicsShapeConvexPolygon2D::VerticesType PhysicsShapeConvexPolygon2D::get_vertices() const {
	return {};
}

void PhysicsShapeRect2D::set_size(const Vector2f&) {
}

void PhysicsShapeRect2D::set_width(real width) {
	set_size({width, get_size().y});
}

void PhysicsShapeRect2D::set_height(real height) {
	set_size({get_size().x, height});
}

Vector2f PhysicsShapeRect2D::get_size() const {
	return Vector2f::ZERO();
}

real PhysicsShapeRect2D::get_width() const {
	return 0;
}

real PhysicsShapeRect2D::get_height() const {
	return 0;
}

PhysicsShape2D::ShapeType PhysicsShapeSegment2D::get_shape_type() const {
	return ShapeType::SEGMENT;
}

void PhysicsShapeSegment2D::set_a(const Vector2f&) {
}

void PhysicsShapeSegment2D::set_b(const Vector2f&) {
}

Vector2f PhysicsShapeSegment2D::get_a() const {
	return Vector2f::ZERO();
}

Vector2f PhysicsShapeSegment2D::get_b() const {
	return Vector2f::ZERO();
}

PhysicsShape2D::ShapeType PhysicsShapeWorldBoundary2D::get_shape_type() const {
	return ShapeType::WORLD_BOUNDARY;
}

void PhysicsShapeWorldBoundary2D::set_distance(double) {
}

void PhysicsShapeWorldBoundary2D::set_normal(const Vector2f&) {
}

double PhysicsShapeWorldBoundary2D::get_distance() const {
	return 0;
}

Vector2f PhysicsShapeWorldBoundary2D::get_normal() const {
	return Vector2f::ZERO();
}

#endif