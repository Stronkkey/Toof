/*  This file is part of the Toof Engine. */
/** @file b2_physics_shape.hpp */
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

#include <core/math/vector2.hpp>
#include <physics/2d/physics_shape.hpp>

#include <box2d/b2_chain_shape.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_polygon_shape.h>

#if TOOF_B2_ENABLED

#define TOOF_DETAIL_B2_PHYSICS_SHAPE_TRAIT \
private: \
	void _remove_body(Physics2DBody *body) override { \
		detail::remove_b2_body(this, body); \
	} \
public: \
	int get_type() const override { \
		return detail::b2_get_type(); \
	}

namespace Toof {

namespace detail {

void remove_b2_body(Physics2DShape *shape, Physics2DBody *body);
int b2_get_type();

}

class B2PhysicsCapsuleShape : public Physics2DShapeCapsule {
	TOOF_DETAIL_B2_PHYSICS_SHAPE_TRAIT
private:
	b2CircleShape top_circle = {};
	b2CircleShape bottom_circle = {};
	b2PolygonShape rect_shape = {};

	real height = 20;
	real radius = 10;
	real x = 0;
	real y = 0;

	void _add_body(Physics2DBody *body) override;

	void update_shapes();
public:
	B2PhysicsCapsuleShape();

	void set_height(real height) override;
	void set_radius(real radius) override;

	real get_height() const override;
	real get_radius() const override;
};

class B2PhysicsCircleShape : public Physics2DShapeCircle {
	TOOF_DETAIL_B2_PHYSICS_SHAPE_TRAIT
private:
	b2CircleShape circle_shape = {};

	void _add_body(Physics2DBody *body) override;
public:
	void set_radius(real radius) override;
	real get_radius() const override;
};

class B2PhysicsConcavePolygonShape : public Physics2DShapeConcavePolygon {
	TOOF_DETAIL_B2_PHYSICS_SHAPE_TRAIT
private:
	b2ChainShape concave_shape = {};

	void _add_body(Physics2DBody *body) override;
public:
	void set_segments(const SegmentType &segments) override;
	SegmentType get_segments() const override;
};

class B2PhysicsConvexPolygonShape : public Physics2DShapeConvexPolygon {
	TOOF_DETAIL_B2_PHYSICS_SHAPE_TRAIT
private:
	b2PolygonShape polygon_shape = {};

	void _add_body(Physics2DBody *body) override;
public:
	void set_vertices(const VerticesType&) override;
	VerticesType get_vertices() const override;
};

class B2PhysicsRectShape : public Physics2DShapeRect {
	TOOF_DETAIL_B2_PHYSICS_SHAPE_TRAIT
private:
	b2PolygonShape polygon_shape = {};
	Vector2f size = {10, 10};

	void _add_body(Physics2DBody *body) override;
public:
	void set_size(const Vector2f &size) override;
	Vector2f get_size() const override;
};

class B2PhysicsSegmentShape : public Physics2DShapeSegment {
	TOOF_DETAIL_B2_PHYSICS_SHAPE_TRAIT
private:
	b2PolygonShape segment_shape = {};
	Vector2f a = {};
	Vector2f b = {};

	void _add_body(Physics2DBody *body) override;

	void update_shapes();
public:
	void set_a(const Vector2f &a_position) override;
	void set_b(const Vector2f &b_position) override;

	Vector2f get_a() const override;
	Vector2f get_b() const override;
};

class B2PhysicsWorldBoundaryShape : public Physics2DShapeWorldBoundary {
	TOOF_DETAIL_B2_PHYSICS_SHAPE_TRAIT
private:
	b2PolygonShape world_shape = {};
	Vector2f normal = {0, -1.0};
	real distance = 0;

	void _add_body(Physics2DBody *body) override;

	void update_shape();
public:
	void set_normal(const Vector2f &normal) override;
	Vector2f get_normal() const override;

	void set_distance(real distance) override;
	real get_distance() const override;
};

}

#endif
