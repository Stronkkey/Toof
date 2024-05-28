/*  This file is part of the Toof Engine. */
/** @file physics_body.hpp */
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

#include <core/math/math_defs.hpp>

namespace Toof {

template<class>
class Vector2;

using Vector2f = Vector2<real>;

class Transform2D;
class Angle;

class PhysicsBody2D {
private:
	uid world_uid;
public:
	enum class BodyType {
		NONE = 0,
		STATIC = 1,
		KINEMATIC = 2,
		DYNAMIC = 3,
	};

	constexpr void set_world_uid(uid world_uid) {
		this->world_uid = world_uid;
	}

	constexpr uid get_world_uid() const {
		return world_uid;
	}

	virtual void set_transform(const Transform2D &transform);
	virtual Transform2D get_transform() const;

	virtual void set_linear_velocity(const Vector2f &linear_velocity);
	virtual Vector2f get_linear_velocity() const;

	virtual void set_angular_velocity(const double angular_velocity);
	virtual double get_angular_velocity() const;

	virtual void set_linear_damping(double linear_damping);
	virtual double get_linear_damping() const;

	virtual void set_angular_damping(double angular_damping);
	virtual double get_angular_damping() const;

	virtual void set_sleeping_allowed(bool is_sleeping_allowed);
	virtual bool is_sleeping_allowed() const;

	virtual void set_awake(bool awake);
	virtual bool is_awake() const;

	virtual void set_rotation_fixed(bool rotation_fixed);
	virtual bool is_rotation_fixed() const;

	virtual void set_ccd_active(bool ccd_active);
	virtual bool is_ccd_active() const;

	virtual void set_gravity_scale(double gravity_scale);
	virtual double get_gravity_scale() const;

	virtual BodyType get_body_type() const;
	virtual int get_type() const;

	void set_position(const Vector2f &position);
	Vector2f get_position() const;

	void set_scale(const Vector2f &scale);
	Vector2f get_scale() const;

	void set_rotation(const Angle &angle);
	Angle get_rotation() const;
};

}

#endif