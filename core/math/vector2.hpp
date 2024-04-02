#pragma once

#include <core/string/string_funcs.hpp>
#include <core/math/math_defs.hpp>

#include <SDL_rect.h>

#include <cereal/cereal.hpp>

#include <algorithm>

#ifdef B2_INCLUDED
#include <box2d/b2_math.h>
#endif

namespace sdl {

/**
* A Vector2 class using a generic T.
*/
template<class T>
struct Vector2 {
	using value_type = T;

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
	
	#ifdef B2_INCLUDED
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
		return vformat("({}, {})", x, y);
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

	#ifdef B2_INCLUDED
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

typedef Vector2<real> Vector2f;
typedef Vector2<integer> Vector2i;

}
