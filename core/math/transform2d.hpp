/*  This file is part of the Toof Engine. */
/** @file transform2d.hpp */
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
#include <core/math/angle.hpp>

#include <cereal/cereal.hpp>

#ifdef B2_INCLUDED
struct b2Transform;
#endif

namespace Toof {

struct Transform2D {
	constexpr Transform2D();
	constexpr Transform2D(const Angle rotation, const Vector2f &new_origin, const Vector2f &new_scale);
	constexpr Transform2D(const Angle rotation, const real origin_x, const real origin_y, const real scale_x, const real scale_y);
	constexpr Transform2D(const Transform2D &transform2d);
	#ifdef B2_INCLUDED
	Transform2D(const b2Transform &b2_transform);
	#endif

	Angle rotation;
	Vector2f origin;
	Vector2f scale;

	constexpr bool operator==(const Transform2D &right) const;
	constexpr bool operator!() const;

	constexpr Transform2D operator*(const Transform2D &right) const;

	#ifdef B2_INCLUDED
	[[nodiscard]] b2Transform to_b2_transform() const;
	#endif

	[[nodiscard]] operator String() const;
	[[nodiscard]] constexpr operator bool() const {
		return true;
	}

	constexpr void operator=(const Transform2D &right);
	constexpr void operator*=(const Transform2D &right);

	static const Transform2D IDENTITY;

	template<class Archive>
	inline void save(Archive &archive) const {
		archive(cereal::make_nvp("IsDouble", REAL_IS_DOUBLE));
		archive(cereal::make_nvp("RotationDegrees", rotation));
		archive(cereal::make_nvp("OriginX", origin.x));
		archive(cereal::make_nvp("OriginY", origin.y));
		archive(cereal::make_nvp("ScaleX", scale.x));
		archive(cereal::make_nvp("ScaleY", scale.y));
	}

	template<class Archive>
	inline void load(Archive &archive) {
		bool is_double;
		archive(is_double);

		if (REAL_IS_DOUBLE == is_double) {
			Angle angle;
			archive(angle);
			rotation = angle;

			archive(origin.x);
			archive(origin.y);
			archive(scale.x);
			archive(scale.y);
			return;
		}

		if (!is_double) {
			float temp_value;
			archive(temp_value);
			rotation = Angle::from_degrees(temp_value);

			archive(temp_value);
			origin.x = temp_value;

			archive(temp_value);
			origin.y = temp_value;

			archive(temp_value);
			scale.x = temp_value;

			archive(temp_value);
			scale.y = temp_value;
		}

		if (is_double) {
			double temp_value;
			archive(temp_value);
			rotation = Angle::from_degrees(temp_value);

			archive(temp_value);
			origin.x = temp_value;

			archive(temp_value);
			origin.y = temp_value;

			archive(temp_value);
			scale.x = temp_value;

			archive(temp_value);
			scale.y = temp_value;
		}
	}
};

/**
* @brief Inserts the transform into the stream.
*/
std::ostream &operator<<(std::ostream &stream, const Transform2D &transform);

constexpr Transform2D::Transform2D(): rotation(Angle::ZERO_ROTATION()), origin(), scale() {
}

constexpr Transform2D::Transform2D(const Angle rotation, const Vector2f &new_origin, const Vector2f &new_scale): rotation(rotation), origin(new_origin), scale(new_scale) {
}

constexpr Transform2D::Transform2D(const Angle rotation, const real origin_x, const real origin_y, const real scale_x, const real scale_y):
    rotation(rotation),
    origin(Vector2(origin_x, origin_y)),
    scale(Vector2(scale_x, scale_y)) {
}

constexpr Transform2D::Transform2D(const Transform2D &transform2d): rotation(transform2d.rotation), origin(transform2d.origin), scale(transform2d.scale) {
}

constexpr bool Transform2D::operator==(const Transform2D &right) const {
	return origin == right.origin && rotation == right.rotation;
}

constexpr bool Transform2D::operator!() const {
	return origin || rotation.get_angle_degrees();
}

constexpr Transform2D Transform2D::operator*(const Transform2D &right) const {
	return Transform2D(rotation + right.rotation, origin + right.origin, scale * right.scale);
}

constexpr void Transform2D::operator=(const Transform2D &right) {
	origin = right.origin;
	rotation = right.rotation;
	scale = right.scale;
}

constexpr void Transform2D::operator*=(const Transform2D &right) {
	origin += right.origin;
	rotation += right.rotation;
	scale *= right.scale;
}


}
