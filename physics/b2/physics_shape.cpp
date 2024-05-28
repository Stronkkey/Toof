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

#include <physics/b2/physics_shape.hpp>
#include <physics/b2/physics_body.hpp>
#include <physics/physics_object_interface.hpp>

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>

#if TOOF_B2_ENABLED

using namespace Toof;

void detail::remove_b2_body(Physics2DShape *shape, Physics2DBody *body) {
	if (body->get_type() == PHYSICS_OBJECT_INTERFACE_B2)
		reinterpret_cast<B2PhysicsBody*>(body)->remove_fixture(shape);
}

int detail::b2_get_type() {
	return PHYSICS_OBJECT_INTERFACE_B2;
}

b2Fixture *create_fixture_from_body_and_shape(b2Shape *shape, B2PhysicsBody *body, bool set_shape_id = true) {
	b2FixtureDef fixture;

	fixture.shape = shape;
	fixture.density = body->get_density();
	fixture.friction = body->get_friction();
	fixture.isSensor = body->is_area();
	fixture.restitution = body->get_restitution();
	fixture.restitutionThreshold = body->get_restitution_threshold();
	fixture.userData = {};

	if (set_shape_id)
		fixture.userData.shape_id = body->increment_shape_id_counter();

	return body->get_body()->CreateFixture(&fixture);
}

B2PhysicsCapsuleShape::B2PhysicsCapsuleShape(): top_circle(), bottom_circle(), rect_shape() {
	update_shapes();
}

void B2PhysicsCapsuleShape::_add_body(Physics2DBody *body) {
	if (body->get_type() != PHYSICS_OBJECT_INTERFACE_B2)
		return;

	B2PhysicsBody *b_body = reinterpret_cast<B2PhysicsBody*>(body);
	FixtureOwner fixtures = {};

	int shape_id = b_body->increment_shape_id_counter();
	b2Fixture *top_circle_fixture = create_fixture_from_body_and_shape(&top_circle, b_body, false);
	b2Fixture *bottom_circle_fixture = create_fixture_from_body_and_shape(&bottom_circle, b_body, false);
	b2Fixture *rect_fixture = create_fixture_from_body_and_shape(&rect_shape, b_body, false);

	top_circle_fixture->GetUserData().shape_id = shape_id;
	bottom_circle_fixture->GetUserData().shape_id = shape_id;
	rect_fixture->GetUserData().shape_id = shape_id;

	fixtures.add_fixture(top_circle_fixture);
	fixtures.add_fixture(bottom_circle_fixture);
	fixtures.add_fixture(rect_fixture);

	b_body->add_fixtures(this, std::move(fixtures));
}

void B2PhysicsCapsuleShape::update_shapes() {
	top_circle.m_radius = radius;
	bottom_circle.m_radius = radius;

	real half_height = height / 2;
	real circle_y_position = half_height - radius;

	top_circle.m_p.y = circle_y_position;
	bottom_circle.m_p.y = -circle_y_position;

	rect_shape.SetAsBox(radius * 2, half_height);
}

void B2PhysicsCapsuleShape::set_radius(real radius) {
	if (radius < 0 || Math::is_zero_approx(radius))
		return;

	if (2 > (height / radius))
		this->height = radius * 2;
	this->radius = radius;
	update_shapes();
}

void B2PhysicsCapsuleShape::set_height(real height) {
	if (height < 0 || Math::is_zero_approx(height))
		return;

	if (2 > (height / radius))
		this->height = radius * 2;
	else
		this->height = height;
	update_shapes();
}

real B2PhysicsCapsuleShape::get_height() const {
	return height;
}

real B2PhysicsCapsuleShape::get_radius() const {
	return radius;
}

void B2PhysicsCircleShape::_add_body(Physics2DBody *body) {
	if (body->get_type() != PHYSICS_OBJECT_INTERFACE_B2)
		return;

	B2PhysicsBody *b_body = reinterpret_cast<B2PhysicsBody*>(body);
	FixtureOwner fixture_owner = {};

	fixture_owner.add_fixture(create_fixture_from_body_and_shape(&circle_shape, b_body));
	b_body->add_fixtures(reinterpret_cast<Physics2DShape*>(this), std::move(fixture_owner));
}

void B2PhysicsCircleShape::set_radius(real radius) {
	circle_shape.m_radius = radius;
}

real B2PhysicsCircleShape::get_radius() const {
	return circle_shape.m_radius;
}

void B2PhysicsConcavePolygonShape::_add_body(Physics2DBody *body) {
	if (body->get_type() != PHYSICS_OBJECT_INTERFACE_B2)
		return;

	B2PhysicsBody *b_body = reinterpret_cast<B2PhysicsBody*>(body);
	FixtureOwner fixture_owner = {};

	fixture_owner.add_fixture(create_fixture_from_body_and_shape(&concave_shape, b_body));
	b_body->add_fixtures(reinterpret_cast<Physics2DShape*>(this), std::move(fixture_owner));
}

void B2PhysicsConcavePolygonShape::set_segments(const SegmentType &segments) {
	size_t segment_count = {};
	if (segment_count < 2) {
		concave_shape.m_count = 0;
		concave_shape.m_vertices = nullptr;
		return;
	}

	b2Vec2 *segment_vecs = new b2Vec2[segment_count];
	for (size_t i = 0; i < segment_count; i++)
		segment_vecs[i] = segments.at(i);

	concave_shape.m_prevVertex = segment_vecs[segment_count - 2];
	concave_shape.m_nextVertex = segment_vecs[1];
	concave_shape.m_count = segment_count;
	concave_shape.m_vertices = segment_vecs;
}

Physics2DShapeConcavePolygon::SegmentType B2PhysicsConcavePolygonShape::get_segments() const {
	if (!concave_shape.m_vertices)
		return {};

	SegmentType segments = SegmentType(concave_shape.m_count);
	for (size_t i = 0; i < segments.size(); i++)
		segments[i] = concave_shape.m_vertices[i];

	return segments;
} 

void B2PhysicsConvexPolygonShape::_add_body(Physics2DBody *body) {
	if (body->get_type() != PHYSICS_OBJECT_INTERFACE_B2)
		return;

	B2PhysicsBody *b_body = reinterpret_cast<B2PhysicsBody*>(body);
	FixtureOwner fixture_owner = {};

	fixture_owner.add_fixture(create_fixture_from_body_and_shape(&polygon_shape, b_body));
	b_body->add_fixtures(reinterpret_cast<Physics2DShape*>(this), std::move(fixture_owner));
}

void B2PhysicsConvexPolygonShape::set_vertices(const VerticesType &vertices) {
	size_t vertice_count = vertices.size();

	if (vertice_count < 2) {
		polygon_shape.m_count = 0;
		return;
	}

	for (size_t i = 0; i < vertice_count; i++)
		polygon_shape.m_vertices[i] = vertices.at(i);
}

Physics2DShapeConvexPolygon::VerticesType B2PhysicsConvexPolygonShape::get_vertices() const {
	VerticesType vertices = VerticesType(polygon_shape.m_count);

	for (int32 i = 0; i < polygon_shape.m_count; i++)
		vertices[i] = polygon_shape.m_vertices[i];

	return vertices;
}

void B2PhysicsRectShape::_add_body(Physics2DBody *body) {
	if (body->get_type() != PHYSICS_OBJECT_INTERFACE_B2)
		return;

	B2PhysicsBody *b_body = reinterpret_cast<B2PhysicsBody*>(body);
	FixtureOwner fixture_owner = {};

	fixture_owner.add_fixture(create_fixture_from_body_and_shape(&polygon_shape, b_body));
	b_body->add_fixtures(reinterpret_cast<Physics2DShape*>(this), std::move(fixture_owner));
}

void B2PhysicsRectShape::set_size(const Vector2f &size) {
	this->size = size;
	polygon_shape.SetAsBox(size.x / 2, size.y / 2);
}

Vector2f B2PhysicsRectShape::get_size() const {
	return size;
}

void B2PhysicsSegmentShape::_add_body(Physics2DBody *body) {
	if (body->get_type() != PHYSICS_OBJECT_INTERFACE_B2)
		return;

	B2PhysicsBody *b_body = reinterpret_cast<B2PhysicsBody*>(body);
	FixtureOwner fixture_owner = {};

	fixture_owner.add_fixture(create_fixture_from_body_and_shape(&segment_shape, b_body));
	b_body->add_fixtures(reinterpret_cast<Physics2DShape*>(this), std::move(fixture_owner));
}

void B2PhysicsSegmentShape::update_shapes() {
	constexpr const float width = 3.0f;
	constexpr const float half_width = width / 2;

	segment_shape.m_vertices[0] = b2Vec2(a.x, a.y - half_width);
	segment_shape.m_vertices[1] = b2Vec2(a.x, a.y + half_width);
	segment_shape.m_vertices[2] = b2Vec2(b.x, b.x - half_width);
	segment_shape.m_vertices[3] = b2Vec2(b.x, b.y + half_width);
	segment_shape.m_count = 4;
}

void B2PhysicsSegmentShape::set_a(const Vector2f &a_position) {
	a = a_position;
	update_shapes();
}

void B2PhysicsSegmentShape::set_b(const Vector2f &b_position) {
	b = b_position;
	update_shapes();
}

Vector2f B2PhysicsSegmentShape::get_a() const {
	return a;
}

Vector2f B2PhysicsSegmentShape::get_b() const {
	return b;
}

void B2PhysicsWorldBoundaryShape::_add_body(Physics2DBody *body) {
	if (body->get_type() != PHYSICS_OBJECT_INTERFACE_B2)
		return;

	B2PhysicsBody *b_body = reinterpret_cast<B2PhysicsBody*>(body);
	FixtureOwner fixture_owner = {};

	fixture_owner.add_fixture(create_fixture_from_body_and_shape(&world_shape, b_body));
	b_body->add_fixtures(reinterpret_cast<Physics2DShape*>(this), std::move(fixture_owner));
}

void B2PhysicsWorldBoundaryShape::update_shape() {
	const constexpr float size = 1e26;
	const constexpr float half_size = size / 2;
	float rotation = atan2(normal.x, normal.y);
	Vector2f distance_vector = normal * distance;
	b2Vec2 center = b2Vec2(distance_vector.x + half_size, distance_vector.y + half_size);

	world_shape.SetAsBox(half_size, half_size, center, rotation);
}

void B2PhysicsWorldBoundaryShape::set_normal(const Vector2f &normal) {
	if (normal.is_zero_approx())
		return;

	this->normal = normal.normalized();
	update_shape();
}

Vector2f B2PhysicsWorldBoundaryShape::get_normal() const {
	return normal;
}

void B2PhysicsWorldBoundaryShape::set_distance(real distance) {
	this->distance = distance;
	update_shape();
}

real B2PhysicsWorldBoundaryShape::get_distance() const {
	return distance;
}

#endif
