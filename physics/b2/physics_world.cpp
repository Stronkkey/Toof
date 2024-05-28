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

#include <core/math/angle.hpp>
#include <physics/physics_object_interface.hpp>
#include <physics/b2/physics_body.hpp>
#include <physics/b2/physics_world.hpp>

#include <box2d/b2_body.h>

using namespace Toof;

B2PhysicsWorld::B2PhysicsWorld(): world(b2Vec2(0, 0)), velocity_iterations(6), position_iterations(2) {
}

void B2PhysicsWorld::set_velocity_iterations(int32_t velocity_iterations) {
	this->velocity_iterations = velocity_iterations;
}

int32_t B2PhysicsWorld::get_velocity_iterations() const {
	return velocity_iterations;
}

void B2PhysicsWorld::set_position_iterations(int32_t position_iterations) {
	this->position_iterations = position_iterations;
}

int32_t B2PhysicsWorld::get_position_iterations() const {
	return position_iterations;
}

void B2PhysicsWorld::set_gravity(const Vector2f &gravity) {
	world.SetGravity(gravity);
}

Vector2f B2PhysicsWorld::get_gravity() const {
	return world.GetGravity();
}

void B2PhysicsWorld::step(double delta) {
	world.Step(delta, velocity_iterations, position_iterations);
}

void B2PhysicsWorld::destroy_body(PhysicsBody2D *body) {
	if (body->get_type() != PHYSICS_OBJECT_INTERFACE_B2)
		return;

	B2PhysicsBody *b2_body = reinterpret_cast<B2PhysicsBody*>(body);
	world.DestroyBody(b2_body->get_body());
	b2_body->set_body(nullptr);
}

void B2PhysicsWorld::add_body(PhysicsBody2D *body) {
	if (body->get_type() != PHYSICS_OBJECT_INTERFACE_B2)
		return;

	b2BodyDef defintion = {};
	B2PhysicsBody *b2_body = reinterpret_cast<B2PhysicsBody*>(body);
	
	if (!b2_body) {
		b2_body->set_body(world.CreateBody(&defintion));
		return;
	}

	defintion.position = body->get_position();
	defintion.angle = body->get_rotation().get_angle_radians();
	defintion.linearVelocity = body->get_linear_velocity();
	defintion.angularVelocity = body->get_angular_velocity();
	defintion.linearDamping = body->get_linear_damping();
	defintion.angularDamping = body->get_angular_damping();
	defintion.allowSleep = body->is_sleeping_allowed();
	defintion.awake = body->is_awake();
	defintion.fixedRotation = body->is_rotation_fixed();
	defintion.bullet = body->is_ccd_active();
	defintion.gravityScale = body->get_gravity_scale();

	switch (body->get_body_type()) {
		case PhysicsBody2D::BodyType::STATIC:
			defintion.type = b2_staticBody;
			break;
		case PhysicsBody2D::BodyType::DYNAMIC:
			defintion.type = b2_dynamicBody;
			break;
		case PhysicsBody2D::BodyType::KINEMATIC:
			defintion.type = b2_kinematicBody;
			break;
		default:
			break;
	}

	b2_body->set_body(world.CreateBody(&defintion));
}

#endif
