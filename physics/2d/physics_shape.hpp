/*  This file is part of the Toof Engine. */
/** @file physics_shape.hpp */
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

#include <core/math/math_defs.hpp>
#include <physics/physics_features.hpp>

#include <unordered_set>
#include <vector>

#if TOOF_PHYSICS_ENABLED

namespace Toof {

template<class>
class Vector2;
class Physics2DBody;

using Vector2f = Vector2<real>;

class Physics2DShape {
private:
	std::unordered_set<Physics2DBody*> bodies;

	virtual void _add_body(Physics2DBody *body);
	virtual void _remove_body(Physics2DBody *body);
public:
	enum class ShapeType {
		NONE = 0,
		CAPSULE = 1,
		CIRCLE = 2,
		CONCAVE_POLYGON = 3,
		CONVEX_POLYGON = 4,
		RECT = 5,
		SEGMENT = 6,
		WORLD_BOUNDARY = 7,
	};

	virtual ShapeType get_shape_type() const;
	virtual int get_type() const;

	void add_body(Physics2DBody *body);
	void remove_body(Physics2DBody *body);

	constexpr std::unordered_set<Physics2DBody*> &get_bodies() {
		return bodies;
	}

	constexpr const std::unordered_set<Physics2DBody*> &get_bodies() const {
		return bodies;
	}
};

class Physics2DShapeCapsule : public Physics2DShape {
public:
	ShapeType get_shape_type() const override;

	virtual void set_height(real height);
	virtual void set_radius(real radius);

	virtual real get_height() const;
	virtual real get_radius() const;
};

class Physics2DShapeCircle : public Physics2DShape {
public:
	ShapeType get_shape_type() const override;

	virtual void set_radius(real radius);
	virtual real get_radius() const;
};

class Physics2DShapeConcavePolygon : public Physics2DShape {
public:
	using SegmentType = std::vector<Vector2f>;

	ShapeType get_shape_type() const override;

	virtual void set_segments(const SegmentType &segments);
	virtual SegmentType get_segments() const;
};

class Physics2DShapeConvexPolygon : public Physics2DShape {
public:
	using VerticesType = std::vector<Vector2f>;

	ShapeType get_shape_type() const override;

	virtual void set_vertices(const VerticesType &vertices);
	virtual VerticesType get_vertices() const;
};

class Physics2DShapeRect : public Physics2DShape {
public:
	ShapeType get_shape_type() const override;

	virtual void set_size(const Vector2f &size);
	void set_width(real width);
	void set_height(real height);

	virtual Vector2f get_size() const;
	real get_width() const;
	real get_height() const;
};

class Physics2DShapeSegment : public Physics2DShape {
public:
	ShapeType get_shape_type() const override;

	virtual void set_a(const Vector2f &a_position);
	virtual void set_b(const Vector2f &b_position);

	virtual Vector2f get_a() const;
	virtual Vector2f get_b() const;
};

class Physics2DShapeWorldBoundary : public Physics2DShape {
public:
	ShapeType get_shape_type() const override;

	virtual void set_distance(real distance);
	virtual void set_normal(const Vector2f &normal);

	virtual real get_distance() const;
	virtual Vector2f get_normal() const;
};

}

#endif
