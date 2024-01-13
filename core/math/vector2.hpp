#pragma once

#include <core/math/math_defs.hpp>

#include <string>
#include <SDL_rect.h>

#ifdef B2_INCLUDED
struct b2Vec2;
#endif

namespace sdl {

struct Vector2i;

struct Vector2 {
	real_t x;
	real_t y;

	Vector2();
	Vector2(const real_t new_x, const real_t new_y);
	Vector2(const Vector2 &vector2);
	Vector2(const Vector2i &vector2i);
	Vector2(const SDL_FPoint &fpoint);
	Vector2(const SDL_Point &point);

	void operator=(const Vector2 &right);
	bool operator==(const Vector2 &right) const;
	bool operator!=(const Vector2 &right) const;

	bool operator<(const Vector2 &right) const;
	bool operator<=(const Vector2 &right) const;
	bool operator>(const Vector2 &right) const;
	bool operator>=(const Vector2 &right) const;

	Vector2 operator+(const Vector2 &right) const;
	Vector2 operator-(const Vector2 &right) const;

	Vector2 operator*(const Vector2 &right) const;
	Vector2 operator*(const real_t right) const;

	Vector2 operator/(const Vector2 &right) const;
	Vector2 operator/(const real_t right) const;

	void operator+=(const Vector2 &right);
	void operator-=(const Vector2 &right);

	void operator*=(const Vector2 &right);
	void operator*=(const real_t right);

	void operator/=(const Vector2 &right);
	void operator/=(const real_t right);

	real_t operator[](const int index) const;
	Vector2 operator-() const;
	Vector2 operator+() const;

	void normalize();
	void rounded();
	void floored();
	void ceiled();

	real_t length() const;
	real_t length_squared() const;

	[[nodiscard]] Vector2 round() const;
	[[nodiscard]] Vector2 floor() const;
	[[nodiscard]] Vector2 ceil() const;
	[[nodiscard]] Vector2 normalized() const;
	[[nodiscard]] Vector2 move_toward(const Vector2 &to, const real_t delta) const;
	[[nodiscard]] real_t distance_to_squared(const Vector2 &to) const;
	[[nodiscard]] real_t distance_to(const Vector2 &to) const;
	[[nodiscard]] std::string to_string() const;
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
	int_t x;
	int_t y;

	Vector2i();
	Vector2i(const int_t new_x, const int_t new_y);
	Vector2i(const Vector2 &vector2);
	Vector2i(const Vector2i &vector2i);
	Vector2i(const SDL_FPoint &fpoint);
	Vector2i(const SDL_Point &point);

	void operator=(const Vector2i &right);
	bool operator==(const Vector2i &right) const;
	bool operator!=(const Vector2i &right) const;

	bool operator<(const Vector2i &right) const;
	bool operator<=(const Vector2i &right) const;
	bool operator>(const Vector2i &right) const;
	bool operator>=(const Vector2i &right) const;

	Vector2i operator+(const Vector2i &right) const;
	Vector2i operator-(const Vector2i &right) const;

	Vector2i operator*(const Vector2i &right) const;
	Vector2i operator*(const int_t right) const;

	Vector2i operator/(const Vector2 &right) const;
	Vector2i operator/(const int_t right) const;

	void operator+=(const Vector2i &right);
	void operator-=(const Vector2i &right);

	void operator*=(const Vector2i &right);
	void operator*=(const int_t right);

	void operator/=(const Vector2i &right);
	void operator/=(const int_t right);

	int_t operator[](const int index) const;
	Vector2i operator-() const;
	Vector2i operator+() const;

	[[nodiscard]] std::string to_string() const;
	[[nodiscard]] SDL_FPoint to_sdl_fpoint() const;
	[[nodiscard]] SDL_Point to_sdl_point() const;

	static const Vector2i ONE;
	static const Vector2i ZERO;
	static const Vector2i LEFT;
	static const Vector2i RIGHT;
	static const Vector2i UP;
	static const Vector2i DOWN;
};

}
