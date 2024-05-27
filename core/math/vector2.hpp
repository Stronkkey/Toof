/*  This file is part of the Toof Engine. */
/** @file vector2.hpp */
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

#include <core/string/string_def.hpp>
#include <core/math/math_funcs.hpp>

#include <SDL_rect.h>

#include <cereal/cereal.hpp>
#include <stringify/format.hpp>

#include <algorithm>

#ifdef TOOF_PHYSICS_ENABLED
#include <box2d/b2_math.h>
#endif

namespace Toof {

/**
* A Vector2 class using a generic T.
*/
template<class T>
struct Vector2 {
	using value_type = T;

	static_assert(std::is_arithmetic<value_type>::value, "value_type of Vector2 must be an arithmetic type.");

	constexpr Vector2(): x(0), y(0) {
	}

	constexpr Vector2(const T new_x, const T new_y): x(new_x), y(new_y) {
	}
	
	constexpr Vector2(const Vector2 &vector2): x(vector2.x), y(vector2.y) {
	}

	template<class T2>
	constexpr Vector2(const Vector2<T2> &vector2): x(vector2.x), y(vector2.y) {
	}

	constexpr Vector2(const SDL_FPoint &fpoint): x(fpoint.x), y(fpoint.y) {
	}

	constexpr Vector2(const SDL_Point &point): x(point.x), y(point.y) {
	}
	
	#ifdef TOOF_PHYSICS_ENABLED
	inline Vector2(const b2Vec2 &b2_vec2): x(b2_vec2.x), y(b2_vec2.y) {
	}
	#endif

	T x;
	T y;

	constexpr void operator=(const Vector2 &right) {
		x = right.x;
		y = right.y;
	}

	template<class T2>
	constexpr void operator=(const Vector2<T2> &right) {
		x = right.x;
		y = right.y;
	}

	constexpr bool operator==(const Vector2 &right) const {
		return x == right.x && y == right.y;
	}

	template<class T2>
	constexpr bool operator==(const Vector2<T2> &right) const {
		return x == right.x && y == right.y;
	}

	constexpr bool operator!=(const Vector2 &right) const {
		return x != right.x || y != right.y;
	}

	template<class T2>
	constexpr bool operator!=(const Vector2<T2> &right) const {
		return x != right.x || y != right.y;
	}

	constexpr bool operator<(const Vector2 &right) const {
		return x < right.x && y < right.y;
	}

	constexpr bool operator<=(const Vector2 &right) const {
		return x <= right.x && y <= right.y;
	}

	template<class T2>
	constexpr bool operator<=(const Vector2<T2> &right) const {
		return x <= right.x && y <= right.y;
	}

	constexpr bool operator>(const Vector2 &right) const {
		return x > right.x && y > right.y;
	}

	template<class T2>
	constexpr bool operator>(const Vector2<T2> &right) const {
		return x > right.x && y > right.y;
	}

	constexpr bool operator>=(const Vector2 &right) const {
		return x >= right.x && y >= right.y;
	}

	template<class T2>
	constexpr bool operator>=(const Vector2<T2> &right) const {
		return x >= right.x && y >= right.y;
	}

	constexpr Vector2 operator+(const Vector2 &right) const {
		return Vector2(x + right.x, y + right.y);
	}

	template<class T2>
	constexpr Vector2 operator+(const Vector2<T2> &right) const {
		return Vector2(x + right.x, y + right.y);
	}

	constexpr Vector2 operator-(const Vector2 &right) const {
		return Vector2(x - right.x, y - right.y);
	}

	template<class T2>
	constexpr Vector2 operator-(const Vector2<T2> &right) const {
		return Vector2(x - right.x, y - right.y);
	}

	constexpr Vector2 operator*(const Vector2 &right) const {
		return Vector2(x * right.x, y * right.y);
	}

	template<class T2>
	constexpr Vector2 operator*(const Vector2<T2> &right) const {
		return Vector2(x * right.x, y * right.y);
	}

	constexpr Vector2 operator*(const T right) const {
		return Vector2(x * right, y * right);
	}

	template<class T2>
	constexpr Vector2 operator*(const T2 right) const {
		return Vector2(x * right, y * right);
	}

	constexpr Vector2 operator/(const Vector2 &right) const {
		return Vector2(x / right.x, y / right.y);
	}

	template<class T2>
	constexpr Vector2 operator/(const Vector2<T2> &right) const {
		return Vector2(x / right.x, y / right.y);
	}

	constexpr Vector2 operator/(const T right) const {
		return Vector2(x / right, y / right);
	}

	template<class T2>
	constexpr Vector2 operator/(const T2 right) const {
		return Vector2(x / right, y / right);
	}

	constexpr void operator+=(const Vector2 &right) {
		x += right.x;
		y += right.y;
	}

	template<class T2>
	constexpr void operator+=(const Vector2<T2> &right) {
		x += right.x;
		y += right.y;
	}

	constexpr void operator-=(const Vector2 &right) {
		x -= right.x;
		y -= right.y;
	}

	template<class T2>
	constexpr void operator-=(const Vector2<T2> &right) {
		x -= right.x;
		y -= right.y;
	}

	constexpr void operator*=(const Vector2 &right) {
		x *= right.x;
		y *= right.y;
	}

	constexpr void operator*=(const T right) {
		x *= right;
		y *= right;
	}

	template<class T2>
	constexpr void operator*=(const T2 right) {
		x *= right;
		y *= right;
	}

	constexpr void operator/=(const Vector2 &right) {
		x /= right.x;
		y /= right.y;
	}

	constexpr void operator/=(const T right) {
		x /= right;
		y /= right;
	}

	template<class T2>
	constexpr void operator/=(const T2 right) {
		x /= right;
		y /= right;
	}

	constexpr T operator[](const int index) const {
		switch (index) {
			case 0:
				return x;
			case 1:
				return y;
			default:
				return 0;
		}
	}

	constexpr Vector2 operator-() const {
		return Vector2(-x, -y);
	}

	constexpr Vector2 operator+() const {
		return Vector2(+x, +y);
	}

	[[nodiscard]] operator String() const {
		return S_FORMAT("({}, {})", x, y);
	}

	[[nodiscard]] constexpr operator bool() const {
		return x && y;
	}

	[[nodiscard]] constexpr bool operator!() const {
		return !x && !y;
	}

	constexpr void normalize() {
		T length = (x * x) + (y * y);
		if (length != 0.0) {
			length = std::sqrt(length);
			x /= length;
			y /= length;
		}
	}

	constexpr void rounded() {
		x = std::round(x);
		y = std::round(y);
	}

	constexpr void floored() {
		x = std::floor(x);
		y = std::floor(y);
	}

	constexpr void ceiled() {
		x = std::ceil(x);
		y = std::ceil(y);
	}

	constexpr void lerp_to(const Vector2 &to, const T weight) {
		x = Math::lerp(x, to.x, weight);
		y = Math::lerp(y, to.y, weight);
	}

	constexpr void clamped(const Vector2 &lower, const Vector2 &higher) {
		x = std::clamp(x, lower.x, higher.x);
		y = std::clamp(y, lower.y, higher.y);
	}

	constexpr T length() const {
		return std::sqrt(x * x + y * y);
	}

	constexpr T length_squared() const {
		return x * x + y * y;
	}

	[[nodiscard]] constexpr Vector2 round() const {
		return Vector2(std::round(x), std::round(y));
	}

	[[nodiscard]] constexpr Vector2 floor() const {
		return Vector2(std::floor(x), std::floor(y));
	}
	
	[[nodiscard]] constexpr Vector2 ceil() const {
		return Vector2(std::ceil(x), std::ceil(y));
	}

	[[nodiscard]] constexpr Vector2 normalized() const {
		Vector2 vector = *this;
		vector.normalize();
		return vector;
	}
	[[nodiscard]] constexpr Vector2 move_toward(const Vector2 &to, const T delta) const {
		Vector2 vector = *this;
		Vector2 from_vector = to - vector;
		T length = from_vector.length();
		return length <= delta ? to : vector + from_vector / length * delta;
	}

	[[nodiscard]] constexpr real distance_to_squared(const Vector2 &to) const {
		return (x - to.x) * (x - to.x) + (y - to.y) * (y - to.y);
	}

	[[nodiscard]] constexpr real distance_to(const Vector2 &to) const {
		return std::sqrt((x - to.x) * (x - to.x) + (y - to.y) * (y - to.y));
	}

	[[nodiscard]] constexpr Vector2 lerp(const Vector2 &to, const T weight) const {
		return Vector2(Math::lerp(x, to.x, weight), Math::lerp(y, to.y, weight));
	}

	[[nodiscard]] constexpr Vector2 clamp(const Vector2 &lower, const Vector2 &higher) const {
		return Vector2(std::clamp(x, lower.x, higher.x), std::clamp(y, lower.y, higher.y));
	}

	[[nodiscard]] inline SDL_FPoint to_sdl_fpoint() const {
		SDL_FPoint fpoint;
		fpoint.x = (float)x;
		fpoint.y = (float)y;
		return fpoint;
	}

	[[nodiscard]] constexpr bool is_zero_approx() const {
		return Math::is_zero_approx(x) && Math::is_zero_approx(y);
	}

	[[nodiscard]] constexpr bool is_equal_approx(const Vector2 &right) const {
		return Math::is_equal_approx(x, right.x) && Math::is_equal_approx(y, right.y);
	}

	[[nodiscard]] SDL_Point to_sdl_point() const {
		SDL_Point point;
		point.x = (int)x;
		point.y = (int)y;
		return point;
	}

	#ifdef TOOF_PHYSICS_ENABLED
	[[nodiscard]] inline b2Vec2 to_b2_vec2() const {
		return b2Vec2((float)x, (float)y);
	}
	#endif

	static constexpr Vector2 ZERO() {
		return Vector2(0, 0);
	}

	static constexpr Vector2 ONE() {
		return Vector2(1, 1);
	}

	static constexpr Vector2 LEFT() {
		return Vector2(-1, 0);
	}

	static constexpr Vector2 RIGHT() {
		return Vector2(1, 0);
	}

	static constexpr Vector2 DOWN() {
		return Vector2(0, 1);
	}

	static constexpr Vector2 UP() {
		return Vector2(0, -1);
	}

	template<class Archive>
	void serialize(Archive &archive) {
		archive(cereal::make_nvp("X", x));
		archive(cereal::make_nvp("Y", y));
	}
};

using Vector2f = Vector2<real>;
using Vector2i = Vector2<integer>;

using Vector2i32 = Vector2<int32_t>;
using Vector2i64 = Vector2<int64_t>;
using Vector2f32 = Vector2<float>;
using Vector2f64 = Vector2<double>;

}
