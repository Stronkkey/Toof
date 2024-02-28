#pragma once

#include <core/string_def.hpp>
#include <core/math/math_defs.hpp>

#include <SDL_rect.h>

#include <algorithm>

#ifdef B2_INCLUDED
struct b2Vec2;
#endif

namespace sdl {

struct Vector2i;

struct Vector2 {
	constexpr Vector2();
	constexpr Vector2(const real_t new_x, const real_t new_y);
	constexpr Vector2(const Vector2 &vector2);
	constexpr Vector2(const Vector2i &vector2i);
	constexpr Vector2(const SDL_FPoint &fpoint);
	constexpr Vector2(const SDL_Point &point);
	
	#ifdef B2_INCLUDED
	Vector2(const b2Vec2 &b2_vec2);
	#endif

	real_t x;
	real_t y;

	constexpr void operator=(const Vector2 &right);
	constexpr bool operator==(const Vector2 &right) const;
	constexpr bool operator!=(const Vector2 &right) const;

	constexpr bool operator<(const Vector2 &right) const;
	constexpr bool operator<=(const Vector2 &right) const;
	constexpr bool operator>(const Vector2 &right) const;
	constexpr bool operator>=(const Vector2 &right) const;

	constexpr Vector2 operator+(const Vector2 &right) const;
	constexpr Vector2 operator-(const Vector2 &right) const;

	constexpr Vector2 operator*(const Vector2 &right) const;
	constexpr Vector2 operator*(const real_t right) const;

	constexpr Vector2 operator/(const Vector2 &right) const;
	constexpr Vector2 operator/(const real_t right) const;

	constexpr void operator+=(const Vector2 &right);
	constexpr void operator-=(const Vector2 &right);

	constexpr void operator*=(const Vector2 &right);
	constexpr void operator*=(const real_t right);

	constexpr void operator/=(const Vector2 &right);
	constexpr void operator/=(const real_t right);

	constexpr real_t operator[](const int index) const;
	constexpr Vector2 operator-() const;
	constexpr Vector2 operator+() const;

	[[nodiscard]] operator String() const;

	constexpr void normalize();
	constexpr void rounded();
	constexpr void floored();
	constexpr void ceiled();
	constexpr void lerp_to(const Vector2 &to, const real_t weight);
	constexpr void clamped(const Vector2 &lower, const Vector2 &higher);

	constexpr real_t length() const;
	constexpr real_t length_squared() const;

	[[nodiscard]] constexpr Vector2 round() const;
	[[nodiscard]] constexpr Vector2 floor() const;
	[[nodiscard]] constexpr Vector2 ceil() const;
	[[nodiscard]] constexpr Vector2 normalized() const;
	[[nodiscard]] constexpr Vector2 move_toward(const Vector2 &to, const real_t delta) const;
	[[nodiscard]] constexpr real_t distance_to_squared(const Vector2 &to) const;
	[[nodiscard]] constexpr real_t distance_to(const Vector2 &to) const;
	[[nodiscard]] constexpr Vector2 lerp(const Vector2 &to, const real_t weight) const;
	[[nodiscard]] constexpr Vector2 clamp(const Vector2 &lower, const Vector2 &higher) const;
	[[nodiscard]] String to_string() const;
	[[nodiscard]] SDL_FPoint to_sdl_fpoint() const;
	[[nodiscard]] SDL_Point to_sdl_point() const;

	#ifdef B2_INCLUDED
	[[nodiscard]] b2Vec2 to_b2_vec2() const;
	#endif

	static const Vector2 ONE;
	static const Vector2 ZERO;
	static const Vector2 LEFT;
	static const Vector2 RIGHT;
	static const Vector2 UP;
	static const Vector2 DOWN;
};

struct Vector2i {
	constexpr Vector2i();
	constexpr Vector2i(const int_t new_x, const int_t new_y);
	constexpr Vector2i(const Vector2 &vector2);
	constexpr Vector2i(const Vector2i &vector2i);
	constexpr Vector2i(const SDL_FPoint &fpoint);
	constexpr Vector2i(const SDL_Point &point);

	int_t x;
	int_t y;

	constexpr void operator=(const Vector2i &right);
	constexpr bool operator==(const Vector2i &right) const;
	constexpr bool operator!=(const Vector2i &right) const;

	constexpr bool operator<(const Vector2i &right) const;
	constexpr bool operator<=(const Vector2i &right) const;
	constexpr bool operator>(const Vector2i &right) const;
	constexpr bool operator>=(const Vector2i &right) const;

	constexpr Vector2i operator+(const Vector2i &right) const;
	constexpr Vector2i operator-(const Vector2i &right) const;

	constexpr Vector2i operator*(const Vector2i &right) const;
	constexpr Vector2i operator*(const int_t right) const;

	constexpr Vector2i operator/(const Vector2 &right) const;
	constexpr Vector2i operator/(const int_t right) const;

	constexpr void operator+=(const Vector2i &right);
	constexpr void operator-=(const Vector2i &right);

	constexpr void operator*=(const Vector2i &right);
	constexpr void operator*=(const int_t right);

	constexpr void operator/=(const Vector2i &right);
	constexpr void operator/=(const int_t right);

	constexpr int_t operator[](const int index) const;
	constexpr Vector2i operator-() const;
	constexpr Vector2i operator+() const;

	[[nodiscard]] String to_string() const;
	[[nodiscard]] SDL_FPoint to_sdl_fpoint() const;
	[[nodiscard]] SDL_Point to_sdl_point() const;

	static const Vector2i ONE;
	static const Vector2i ZERO;
	static const Vector2i LEFT;
	static const Vector2i RIGHT;
	static const Vector2i UP;
	static const Vector2i DOWN;
};


constexpr Vector2::Vector2(const real_t new_x, const real_t new_y): x(new_x), y(new_y) {
}

constexpr Vector2::Vector2(): x(0), y(0) {
}

constexpr Vector2::Vector2(const Vector2 &vector2): x(vector2.x), y(vector2.y) {
}

constexpr Vector2::Vector2(const Vector2i &vector2i): x(vector2i.x), y(vector2i.y) {
}

constexpr Vector2::Vector2(const SDL_FPoint &fpoint): x(fpoint.x), y(fpoint.y) {
}

constexpr Vector2::Vector2(const SDL_Point &point): x(point.x), y(point.y) {
}

constexpr void Vector2::operator=(const Vector2 &right) {
	x = right.x;
	y = right.y;
}

constexpr bool Vector2::operator==(const Vector2 &right) const {
	return x == right.x && y == right.y;
}

constexpr bool Vector2::operator!=(const Vector2 &right) const {
	return x != right.x || y != right.y;
}

constexpr bool Vector2::operator<(const Vector2 &right) const {
	return x < right.x && y < right.y;
}

constexpr bool Vector2::operator<=(const Vector2 &right) const {
	return x <= right.x && y <= right.y;
}

constexpr bool Vector2::operator>(const Vector2 &right) const {
	return x > right.x && y > right.y;
}

constexpr bool Vector2::operator>=(const Vector2 &right) const {
	return x >= right.x && y >= right.y;
}

constexpr Vector2 Vector2::operator+(const Vector2 &right) const {
	return Vector2(x + right.x, y + right.y);
}

constexpr Vector2 Vector2::operator-(const Vector2 &right) const {
	return Vector2(x - right.x, y - right.y);
}

constexpr Vector2 Vector2::operator*(const Vector2 &right) const {
	return Vector2(x * right.x, y * right.y);
}

constexpr Vector2 Vector2::operator*(const real_t right) const {
	return Vector2(x * right, y * right);
}

constexpr Vector2 Vector2::operator/(const Vector2 &right) const {
	return Vector2(x / right.x, y / right.y);
}

constexpr Vector2 Vector2::operator/(const real_t right) const {
	return Vector2(x / right, y / right);
}

constexpr void Vector2::operator+=(const Vector2 &right) {
	x += right.x;
	y += right.y;
}

constexpr void Vector2::operator-=(const Vector2 &right) {
 x -= right.x;
 y -= right.y;
}

constexpr void Vector2::operator*=(const Vector2 &right) {
	x *= right.x;
	y *= right.y;
}

constexpr void Vector2::operator*=(const real_t right) {
	x *= right;
	y *= right;
}

constexpr void Vector2::operator/=(const Vector2 &right) {
	x /= right.x;
	y /= right.y;
}

constexpr void Vector2::operator/=(const real_t right) {
	x /= right;
	y /= right;
}

constexpr real_t Vector2::operator[](const int index) const {
	if (index == 0)
		return x;
	else if (index == 1)
		return y;
	return 0.0;
}

constexpr Vector2 Vector2::operator+() const {
	return Vector2(+x, +y);
}

constexpr Vector2 Vector2::operator-() const {
	return Vector2(-x, -y);
}

constexpr void Vector2::normalize() {
	real_t length = (x * x) + (y * y);
	if (length != 0.0) {
		length = std::sqrt(length);
		x /= length;
		y /= length;
	}
}

constexpr void Vector2::rounded() {
	x = std::round(x);
	y = std::round(y);
}

constexpr void Vector2::floored() {
	x = std::floor(x);
	y = std::floor(y);
}

constexpr void Vector2::ceiled() {
	x = std::ceil(x);
	y = std::ceil(y);
}

constexpr void Vector2::lerp_to(const Vector2 &to, const real_t weight) {
	x = Math::lerp(x, to.x, weight);
	y = Math::lerp(y, to.y, weight);
}

constexpr void Vector2::clamped(const Vector2 &lower, const Vector2 &higher) {
	x = std::clamp(x, lower.x, higher.x);
	y = std::clamp(y, lower.y, higher.y);
}

constexpr Vector2 Vector2::move_toward(const Vector2 &to, const real_t delta) const {
	Vector2 vector = *this;
	Vector2 from_vector = to - vector;
	real_t length = from_vector.length();
	return length <= delta ? to : vector + from_vector / length * delta;
}

constexpr real_t Vector2::distance_to(const Vector2 &to) const {
	return std::sqrt((x - to.x) * (x - to.x) + (y - to.y) * (y - to.y));
}

constexpr Vector2 Vector2::lerp(const Vector2 &to, const real_t weight) const {
	Vector2 vector;
	vector.x = Math::lerp(x, to.x, weight);
	vector.y = Math::lerp(y, to.y, weight);
	return vector;
}

constexpr Vector2 Vector2::clamp(const Vector2 &lower, const Vector2 &higher) const {
	Vector2 vector;
	vector.x = std::clamp(x, lower.x, higher.x);
	vector.y = std::clamp(y, lower.y, higher.y);
	return vector;
}

constexpr real_t Vector2::distance_to_squared(const Vector2 &to) const {
	return ((x - to.x) * (x - to.x) + (y - to.y) * (y - to.y));
}

constexpr real_t Vector2::length() const {
	return std::sqrt(x * x + y * y);
}

constexpr real_t Vector2::length_squared() const {
	return x * x + y * y;
}

constexpr Vector2 Vector2::normalized() const {
	Vector2 vector = *this;
	vector.normalize();
	return vector;
}

constexpr Vector2 Vector2::ceil() const {
	Vector2 vector = *this;
	vector.ceiled();
	return vector;
}

constexpr Vector2 Vector2::round() const {
	Vector2 vector = *this;
	vector.rounded();
	return vector;
}

constexpr Vector2 Vector2::floor() const {
	Vector2 vector = *this;
	vector.floored();
	return vector;
}

// Vector2i //


constexpr Vector2i::Vector2i(const int_t new_x, const int_t new_y): x(new_x), y(new_y) {
}

constexpr Vector2i::Vector2i(): x(0), y(0) {
}

constexpr Vector2i::Vector2i(const Vector2 &vector2): x(vector2.x), y(vector2.y) {
}

constexpr Vector2i::Vector2i(const Vector2i &vector2i): x(vector2i.x), y(vector2i.y) {
}

constexpr Vector2i::Vector2i(const SDL_FPoint &fpoint): x(fpoint.x), y(fpoint.y) {
}

constexpr Vector2i::Vector2i(const SDL_Point &point): x(point.x), y(point.y) {
}

constexpr void Vector2i::operator=(const Vector2i &right) {
	x = right.x;
	y = right.y;
}

constexpr bool Vector2i::operator==(const Vector2i &right) const {
	return x == right.x && y == right.y;
}

constexpr bool Vector2i::operator!=(const Vector2i &right) const {
	return x != right.x && y != right.y;
}

constexpr bool Vector2i::operator<(const Vector2i &right) const {
	return x < right.x && y < right.y;
}

constexpr bool Vector2i::operator<=(const Vector2i &right) const {
	return x <= right.x && y <= right.y;
}

constexpr bool Vector2i::operator>(const Vector2i &right) const {
	return x > right.x && y > right.y;
}

constexpr bool Vector2i::operator>=(const Vector2i &right) const {
	return x >= right.x && y >= right.y;
}

constexpr Vector2i Vector2i::operator+(const Vector2i &right) const {
	return Vector2i(x + right.x, y + right.y);
}

constexpr Vector2i Vector2i::operator-(const Vector2i &right) const {
	return Vector2i(x - right.x, y - right.y);
}

constexpr Vector2i Vector2i::operator*(const Vector2i &right) const {
	return Vector2i(x * right.x, y * right.y);
}

constexpr Vector2i Vector2i::operator*(const int_t right) const {
	return Vector2i(x * right, y * right);
}

constexpr Vector2i Vector2i::operator/(const Vector2 &right) const {
	return Vector2(x / right.x, y / right.y);
}

constexpr Vector2i Vector2i::operator/(const int_t right) const {
	return Vector2i(x / right, y / right);
}

constexpr void Vector2i::operator+=(const Vector2i &right) {
	x += right.x;
	y += right.y;
}

constexpr void Vector2i::operator-=(const Vector2i &right) {
 x -= right.x;
 y -= right.y;
}

constexpr void Vector2i::operator*=(const Vector2i &right) {
	x *= right.x;
	y *= right.y;
}

constexpr void Vector2i::operator*=(const int_t right) {
	x *= right;
	y *= right;
}

constexpr void Vector2i::operator/=(const Vector2i &right) {
	x /= right.x;
	y /= right.y;
}

constexpr void Vector2i::operator/=(const int_t right) {
	x /= right;
	y /= right;
}

constexpr int_t Vector2i::operator[](const int index) const {
	if (index == 0)
		return x;
	else if (index == 1)
		return y;
	return 0;
}

constexpr Vector2i Vector2i::operator+() const {
	return Vector2i(+x, +y);
}

constexpr Vector2i Vector2i::operator-() const {
	return Vector2i(-x, -y);
}

}
