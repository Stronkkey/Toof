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
#include <core/math/vector2.hpp>
#include <physics/physics_object_interface.hpp>
#include <physics/2d/physics_shape.hpp>

#if TOOF_PHYSICS_ENABLED

using namespace Toof;

void Physics2DShape::_add_body(Physics2DBody*) {
}

void Physics2DShape::_remove_body(Physics2DBody*) {
}

Physics2DShape::ShapeType Physics2DShape::get_shape_type() const {
	return ShapeType::NONE;
}

int Physics2DShape::get_type() const {
	return PHYSICS_OBJECT_INTERFACE_NONE;
}

void Physics2DShape::add_body(Physics2DBody *body) {
	bodies.insert(body);
	_add_body(body);
}

void Physics2DShape::remove_body(Physics2DBody *body) {
	_remove_body(body);
	bodies.erase(body);
}

Physics2DShape::ShapeType Physics2DShapeCapsule::get_shape_type() const {
	return ShapeType::CAPSULE;
}

void Physics2DShapeCapsule::set_height(real) {
}

void Physics2DShapeCapsule::set_radius(real) {
}

real Physics2DShapeCapsule::get_height() const {
	return 0;
}

real Physics2DShapeCapsule::get_radius() const {
	return 0;
}

Physics2DShape::ShapeType Physics2DShapeCircle::get_shape_type() const {
	return ShapeType::CIRCLE;
}

void Physics2DShapeCircle::set_radius(real) {
}

real Physics2DShapeCircle::get_radius() const {
	return 0;
}

Physics2DShape::ShapeType Physics2DShapeConcavePolygon::get_shape_type() const {
	return ShapeType::CONCAVE_POLYGON;
}

void Physics2DShapeConcavePolygon::set_segments(const SegmentType&) {
}

Physics2DShapeConcavePolygon::SegmentType Physics2DShapeConcavePolygon::get_segments() const {
	return {};
}

Physics2DShape::ShapeType Physics2DShapeRect::get_shape_type() const {
	return ShapeType::RECT;
}

Physics2DShape::ShapeType Physics2DShapeConvexPolygon::get_shape_type() const {
	return ShapeType::CONVEX_POLYGON;
}

void Physics2DShapeConvexPolygon::set_vertices(const VerticesType&) {
}

Physics2DShapeConvexPolygon::VerticesType Physics2DShapeConvexPolygon::get_vertices() const {
	return {};
}

void Physics2DShapeRect::set_size(const Vector2f&) {
}

void Physics2DShapeRect::set_width(real width) {
	set_size({width, get_size().y});
}

void Physics2DShapeRect::set_height(real height) {
	set_size({get_size().x, height});
}

Vector2f Physics2DShapeRect::get_size() const {
	return Vector2f::ZERO();
}

real Physics2DShapeRect::get_width() const {
	return 0;
}

real Physics2DShapeRect::get_height() const {
	return 0;
}

Physics2DShape::ShapeType Physics2DShapeSegment::get_shape_type() const {
	return ShapeType::SEGMENT;
}

void Physics2DShapeSegment::set_a(const Vector2f&) {
}

void Physics2DShapeSegment::set_b(const Vector2f&) {
}

Vector2f Physics2DShapeSegment::get_a() const {
	return Vector2f::ZERO();
}

Vector2f Physics2DShapeSegment::get_b() const {
	return Vector2f::ZERO();
}

Physics2DShape::ShapeType Physics2DShapeWorldBoundary::get_shape_type() const {
	return ShapeType::WORLD_BOUNDARY;
}

void Physics2DShapeWorldBoundary::set_distance(real) {
}

void Physics2DShapeWorldBoundary::set_normal(const Vector2f&) {
}

real Physics2DShapeWorldBoundary::get_distance() const {
	return 0;
}

Vector2f Physics2DShapeWorldBoundary::get_normal() const {
	return Vector2f::ZERO();
}

#endif
