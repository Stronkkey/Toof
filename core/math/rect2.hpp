#pragma once

#include <core/math/vector2.hpp>

namespace sdl {

struct Rect2i;
struct Transform2D;

/**
* A 2D axis-aligned bounding box using floating-point coordinates.
*/
struct Rect2 {
	/**
	* Constructs a Rect2 with its x, y, w, and h properties set to 0.
	*/
	constexpr Rect2();

	/** 
	* Constructs a Rect2 by @param position and @param size.
	*/
	constexpr Rect2(const Vector2f &position, const Vector2f &size);

	/**
	* Constructs a Rect2 by setting its x and y values to @param position_x and @param position_y and w and h values to @param size_x and @param size_y.
	*/
	constexpr Rect2(const real_t position_x, const real_t position_y, const real_t size_x, const real_t size_y);

	/**
	* Constructs a Rect2 as a copy of the given Rect2.
	*/
	constexpr Rect2(const Rect2 &rect);

	/**
	* Constructs a Rect2 from a Rect2i.
	*/
	constexpr Rect2(const Rect2i &rect);

	/**
	* Constructs a Rect2 from a SDL_Rect.
	*/
	constexpr Rect2(const SDL_Rect &rect);

	/**
	* Constructs a Rect2 from a SDL_FRect.
	*/
	constexpr Rect2(const SDL_FRect &frect);

	/**
	* The x axis of the origin point. Usually the top-left corner of the rectangle.
	*/
	real_t x;

	/**
	* The y axis of the origin point. Usually the top-left corner of the rectangle.
	*/
	real_t y;

	/**
	* The rectangle's width, starting from the origin. Setting this value also affects the end point.
	*/
	real_t w;

	/**
	* The rectangle's height, starting from the origin. Setting this value also affects the end point.
	*/
	real_t h;

	/**
	* Sets the x, y, w, and h properties to that of @param right.
	*/
	constexpr void operator=(const Rect2 &right);

	/** 
	* @returns true if both x, y, w, and h of the rectangles are exactly equal, respectively.
	* @note due to floating-point precision errors, consider using Math::is_equal_approx instead, which is more reliable.
	*/
	constexpr bool operator==(const Rect2 &right) const;
	
	/** 
	* @returns true if both x, y, w, and h of the rectangles are exactly equal, respectively.
	* @note due to floating-point precision errors, consider using Math::is_equal_approx instead, which is more reliable.
	*/
	constexpr bool operator!=(const Rect2 &right) const;

	/**
	* @returns true if all of the components of this rect are smaller than those of @param right_rect.
	*/
	constexpr bool operator<(const Rect2 &right_rect) const;

	/**
	* @returns true if all of the components of this rect are smaller or equal to those of @param right_rect.
	*/
	constexpr bool operator<=(const Rect2 &right_rect) const;

	/**
	* @returns true if all of the components of this rect are bigger than those of @param right_rect.
	*/
	constexpr bool operator>(const Rect2 &right_rect) const;

	/**
	* @returns true if all of the components of this rect are bigger or equal to those of @param right_rect.
	*/
	constexpr bool operator>=(const Rect2 &right_rect) const;

	/**
	* @returns this rect with its components added with with the components of @param right_rect.
	*/
	constexpr Rect2 operator+(const Rect2 &right_rect) const;
	
	/**
	* @returns this rect with its components subtracted with with the components of @param right_rect.
	*/
	constexpr Rect2 operator-(const Rect2 &right_rect) const;

	/**
	* @returns this rect with its components multiplied with the components of @param right_rect.
	*/
	constexpr Rect2 operator*(const Rect2 &right_rect) const;

	/**
	* @returns this rect with its components multiplied with @param right.
	*/
	constexpr Rect2 operator*(const real_t right) const;

	/**
	* @returns this rect with its position added with the @param right_transform origin and size multiplied by @param right_transform scale.
	*/
	Rect2 operator*(const Transform2D &right_transform) const;

	/**
	* @returns this rect with its components divided with the components of @param right_rect.
	*/
	constexpr Rect2 operator/(const Rect2 &right_rect) const;

	/**
	* @returns this rect with its components multiplied by @param right.
	*/
	constexpr Rect2 operator/(const real_t right) const;

	/**
	* Adds each component of this rect by the components of @param right_rect.
	*/
	constexpr void operator+=(const Rect2 &right_rect);

	/**
	* Subtracts each component of this rect by the components of @param right_rect.
	*/
	constexpr void operator-=(const Rect2 &right_rect);

	/**
	* Multiplies each component of this rect by the components of @param right_rect.
	*/
	constexpr void operator*=(const Rect2 &right_rect);

	/**
	* Multiplies each component of this rect by @param right.
	*/
	constexpr void operator*=(const real_t right);

	/**
	* Adds the @param right_transform origin to the position and multiplies the size by @param right_transform scale.
	*/
	void operator*=(const Transform2D &right);

	/**
	* Divides each component of this rect by the components of @param right_rect.
	*/
	constexpr void operator/=(const Rect2 &right_rect);
	
	/**
	* Divides each component of this rect by @param right.
	*/
	constexpr void operator/=(const real_t right);

	/**
	* @return the rect components using their index.
	* [0] is equivalent to x, [1] is equivalent to y, [2] is equivalent to w, and [3] is equivalent to h.
	*/
	constexpr real_t operator[](const int index) const;

	/**
	* @return the inverted value of this rect.
	*/
	constexpr Rect2 operator-() const;

	/**
	* @return the same value as if the + was not there.
	* Unary + does nothing, but sometimes it can make your code more readable.
	*/
	constexpr Rect2 operator+() const;

	[[nodiscard]] operator String() const;

	/**
	* Rounds each component of this rect.
	*/
	constexpr void rounded();

	/**
	* Floors each component of this rect.
	*/
	constexpr void floored();

	/**
	* Ceils each component of this rect.
	*/
	constexpr void ceiled();

	/**
	* @returns this rect with its components rounded.
	*/
	[[nodiscard]] constexpr Rect2 round() const;

	/**
	* @returns this rect with its components floored.
	*/
	[[nodiscard]] constexpr Rect2 floor() const;

	/**
	* @returns this rect with its components ceiled.
	*/
	[[nodiscard]] constexpr Rect2 ceil() const;

	/**
	* @returns a string representation as '((x, y), (w, h))'.
	*/
	[[nodiscard]] String to_string() const;

	/**
	* @returns a Rect2 that encloses both this rectangle and @param right around the edges.
	*/
	[[nodiscard]] constexpr Rect2 merge(const Rect2 &right) const;

	/**
	* @returns this rect with its components set to absolute values of themselfs.
	*/
	[[nodiscard]] Rect2 abs() const;

	/**
	* @returns this rect with negative sizes removed.
	*/
	[[nodiscard]] constexpr Rect2 remove_negative_size() const;

	/**
	* @returns a copy of this rectangle expanded to align the edges with the given @param to point, if necessary.
	*/
	[[nodiscard]] constexpr Rect2 expand(const Vector2f &to) const;

	/**
	* @returns a vector2 with the x and y properties set to this rectangles x and y properties.
	*/
	constexpr Vector2f get_position() const;

	/**
	* @returns a vector2 with the x and y properties set to this rectangles w and h properties.
	*/
	constexpr Vector2f get_size() const;

	/**
	* @returns true if @param point is inside this rect.
	*/
	constexpr bool has_point(const Vector2f &point) const;

	/**
	* @returns true if the width and height of this rect is higher or equal to 0.
	*/
	constexpr bool has_area() const;

	/**
	* @returns true if this rectangle overlaps with the @param rect2. The edges of both rectangles are excluded, unless @param include_borders is true.
	*/
	constexpr bool intersects(const Rect2 &rect2, const bool include_borders = false) const;

	/**
	* Aligns the edges of this rect with the edges with the given @param to point, if necessary.
	*/
	constexpr void expand_to(const Vector2f &to);

	/**
	* Sets the x and y properties to that of @param new_position x and y values.
	*/
	constexpr void set_position(const Vector2f &new_position);

	/**
	* Sets the w and h properties to that of @param new_size x and y values.
	*/
	constexpr void set_size(const Vector2f &new_size);

	[[nodiscard]] SDL_Rect to_sdl_rect() const;
	[[nodiscard]] SDL_FRect to_sdl_frect() const;

	static const Rect2 EMPTY;
	static const Rect2 ONE;
	static SDL_Rect to_sdl_rect(const Rect2 &rect2);
	static SDL_FRect to_sdl_frect(const Rect2 &rect);
};

struct Rect2i {
	constexpr Rect2i();
	constexpr Rect2i(const Vector2i &position, const Vector2i &size);
	constexpr Rect2i(const int_t x, const int_t y, const int_t w, const int_t h);
	constexpr Rect2i(const Rect2 &rect);
	constexpr Rect2i(const Rect2i &rect);
	constexpr Rect2i(const SDL_Rect &rect);
	constexpr Rect2i(const SDL_FRect &frect);

	int_t x;
	int_t y;
	int_t w;
	int_t h;

	constexpr void operator=(const Rect2i &right);
	constexpr bool operator==(const Rect2i &right) const;
	constexpr bool operator!=(const Rect2i &right) const;

	constexpr bool operator<(const Rect2i &right) const;
	constexpr bool operator<=(const Rect2i &right) const;
	constexpr bool operator>(const Rect2i &right) const;
	constexpr bool operator>=(const Rect2i &right) const;

	constexpr Rect2i operator+(const Rect2i &right) const;
	constexpr Rect2i operator-(const Rect2i &right) const;

	constexpr Rect2i operator*(const Rect2i &right) const;
	constexpr Rect2i operator*(const int_t right) const;

	constexpr Rect2i operator/(const Rect2i &right) const;
	constexpr Rect2i operator/(const int_t right) const;

	constexpr void operator+=(const Rect2i &right);
	constexpr void operator-=(const Rect2i &right);

	constexpr void operator*=(const Rect2i &right);
	constexpr void operator*=(const int_t right);

	constexpr void operator/=(const Rect2i &right);
	constexpr void operator/=(const int_t right);

	constexpr int_t operator[](const int index) const;
	constexpr Rect2i operator-() const;
	constexpr Rect2i operator+() const;

	constexpr Vector2i get_position() const;
	constexpr Vector2i get_size() const;

	[[nodiscard]] String to_string() const;
	[[nodiscard]] constexpr Rect2i merge(const Rect2i &right) const;
	[[nodiscard]] Rect2i abs() const;
	[[nodiscard]] constexpr Rect2i remove_negative_size() const;
	[[nodiscard]] constexpr Rect2i expand(const Vector2i &to) const;

	constexpr void set_position(const Vector2i &new_position);
	constexpr void set_size(const Vector2i &new_size);
	constexpr bool has_point(const Vector2i &point) const;
	constexpr bool has_area() const;
	constexpr bool intersects(const Rect2i &rect2i, const bool include_borders = false) const;
	constexpr void expand_to(const Vector2i &to);

	[[nodiscard]] SDL_Rect to_sdl_rect() const;
	[[nodiscard]] SDL_FRect to_sdl_frect() const;

	[[nodiscard]] operator String() const;

	static const Rect2i EMPTY;
	static const Rect2i ONE;
	static SDL_Rect to_sdl_rect(const Rect2i &rect2i);
	static SDL_FRect to_sdl_frect(const Rect2i &rect2i);
};

constexpr Rect2::Rect2(): x(0), y(0), w(0), h(0) {
}

constexpr Rect2::Rect2(const Vector2f &position, const Vector2f &size): x(position.x), y(position.y), w(size.x), h(size.y) {
}

constexpr Rect2::Rect2(const real_t position_x, const real_t position_y, const real_t size_x, const real_t size_y): x(position_x), y(position_y), w(size_x), h(size_y) {
}

constexpr Rect2::Rect2(const Rect2 &rect): x(rect.x), y(rect.y), w(rect.w), h(rect.h) {
}

constexpr Rect2::Rect2(const Rect2i &rect): x(rect.x), y(rect.y), w(rect.w), h(rect.h) { 
}

constexpr Rect2::Rect2(const SDL_Rect &rect): x(rect.x), y(rect.y), w(rect.w), h(rect.h) {
}

constexpr Rect2::Rect2(const SDL_FRect &frect): x(frect.x), y(frect.y), w(frect.w), h(frect.h) {
}

constexpr void Rect2::operator=(const Rect2 &right) {
	x = right.x;
	y = right.y;
	w = right.w;
	h = right.h;
}

constexpr bool Rect2::operator==(const Rect2 &right) const {
	return x == right.x && y == right.y;
}

constexpr bool Rect2::operator!=(const Rect2 &right) const {
	return x != right.x || y != right.y || w != right.w || h != right.h;
}

constexpr bool Rect2::operator<(const Rect2 &right) const {
	return x < right.x && y < right.y && w < right.w && h < right.h;
}

constexpr bool Rect2::operator<=(const Rect2 &right) const {
	return x <= right.x && y <= right.y && w <= right.w && h <= right.h;
}

constexpr bool Rect2::operator>(const Rect2 &right) const {
	return get_position() > right.get_position() && get_size() > right.get_size();
}

constexpr bool Rect2::operator>=(const Rect2 &right) const {
	return get_position() >= right.get_position() && get_size() >= right.get_size();
}

constexpr Rect2 Rect2::operator+(const Rect2 &right) const {
	return Rect2(get_position() + right.get_position(), get_size() + right.get_size());
}

constexpr Rect2 Rect2::operator-(const Rect2 &right) const {
	return Rect2(get_position() - right.get_position(), get_size() - right.get_size());
}

constexpr Rect2 Rect2::operator*(const Rect2 &right) const {
	return Rect2(get_position() * right.get_position(), get_size() - right.get_size());
}

constexpr Rect2 Rect2::operator*(const real_t right) const {
	return Rect2(get_position() * right, get_size() * right);
}

constexpr Rect2 Rect2::operator/(const Rect2 &right) const {
	return Rect2(get_position() / right.get_position(), get_size() / right.get_size());
}

constexpr Rect2 Rect2::operator/(const real_t right) const {
	return Rect2(get_position() / right, get_size() / right);
}

constexpr void Rect2::operator+=(const Rect2 &right) {
	x += right.x;
	y += right.y;
	w += right.w;
	h += right.h;
}

constexpr void Rect2::operator-=(const Rect2 &right) {
	x -= right.x;
	y -= right.y;
	w -= right.w;
	h -= right.h;
}

constexpr void Rect2::operator*=(const Rect2 &right) {
	x *= right.x;
	y *= right.y;
	w *= right.w;
	h *= right.h;
}

constexpr void Rect2::operator*=(const real_t right) {
	x *= right;
	y *= right;
	w *= right;
	h *= right;
}


constexpr void Rect2::operator/=(const Rect2 &right) {
	x /= right.x;
	y /= right.y;
	w /= right.w;
	h /= right.h;
}

constexpr void Rect2::operator/=(const real_t right) {
	x /= right;
	y /= right;
	w /= right;
	h /= right;
}

constexpr real_t Rect2::operator[](const int index) const {
	switch (index) {
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return w;
		case 3:
			return h;
	}
	return 0.0;
}

constexpr Rect2 Rect2::operator+() const {
	return Rect2(+x, +y, +w, +h);
}

constexpr Rect2 Rect2::operator-() const {
	return Rect2(-x, -y, -w, -h);
}

constexpr void Rect2::rounded() {
	x = std::round(x);
	y = std::round(y);
	w = std::round(w);
	h = std::round(h);
}

constexpr void Rect2::floored() {
	x = std::floor(x);
	y = std::floor(y);
	w = std::floor(w);
	h = std::floor(h);
}

constexpr void Rect2::ceiled() {
	x = std::ceil(x);
	y = std::ceil(y);
	w = std::ceil(w);
	h = std::ceil(h);
}

constexpr Rect2 Rect2::round() const {
	Rect2 rect = *this;
	rect.rounded();
	return rect;
}

constexpr Rect2 Rect2::floor() const {
	Rect2 rect = *this;
	rect.floored();
	return rect;
}

constexpr Rect2 Rect2::ceil() const {
	Rect2 rect = *this;
	rect.ceiled();
	return rect;
}

constexpr Vector2f Rect2::get_position() const {
	return Vector2f(x, y);
}

constexpr Vector2f Rect2::get_size() const {
	return Vector2f(w, h);
}

constexpr bool Rect2::has_point(const Vector2f &point) const {
	if (point.x < x)
		return false;
	if (point.y < y)
		return false;
	if (point.x >= (x + w))
		return false;
	if (point.y >= (y + h))
		return false;

	return true;
}

constexpr bool Rect2::has_area() const {
	return w > 0 && h > 0;
}

constexpr bool Rect2::intersects(const Rect2 &rect2, const bool include_borders) const {
	if (include_borders) {
		if (x > (rect2.x + rect2.w))
			return false;

		if ((x + w) < rect2.x)
			return false;

		if (y > (rect2.y + rect2.h))
			return false;

		if ((y + h) < rect2.y)
			return false;
	} else {
		if (x >= (rect2.x + rect2.w))
			return false;

		if ((x + w) <= rect2.x)
			return false;

		if (y >= (rect2.y + rect2.h))
			return false;

		if ((y + h) <= rect2.y)
			return false;
	}

	return true;
}

constexpr Rect2 Rect2::merge(const Rect2 &right) const {
	Rect2 new_rect;

	new_rect.x = std::min(right.x, x);
	new_rect.y = std::min(right.y, y);

	new_rect.w = std::max(right.x + right.w, x + w);
	new_rect.h = std::max(right.y + right.h, y + h);

	new_rect.w -= new_rect.x;
	new_rect.h -= new_rect.y;

	return new_rect;
}

constexpr Rect2 Rect2::remove_negative_size() const {
	Rect2 rect = *this;
	if (w < 0.0) {
		rect.x += w;
		rect.w = -w;
	}

	if (h < 0.0) {
		rect.y += h;
		rect.h = -h;
	}

	return rect;
}

constexpr Rect2 Rect2::expand(const Vector2f &to) const {
	Rect2 rect = *this;
	rect.expand_to(to);
	return rect;
}

constexpr void Rect2::expand_to(const Vector2f &to) {
	real_t begin_x = x;
	real_t begin_y = y;
	real_t end_x = x + w;
	real_t end_y = y + h;

	if (to.x < begin_x)
		begin_x = to.x;

	if (to.y < begin_y)
		begin_y = to.y;

	if (to.x > end_x)
		end_x = to.x;

	if (to.y > end_y)
		end_y = to.y;

	x = begin_x;
	y = begin_y;
	w = end_x - begin_x;
	h = end_y - begin_y;
}

constexpr void Rect2::set_position(const Vector2f &new_position) {
	x = new_position.x;
	y = new_position.y;
}

constexpr void Rect2::set_size(const Vector2f &new_size) {
	x = new_size.x;
	y = new_size.y;
}

// RECT2i //

constexpr Rect2i::Rect2i(): x(0), y(0), w(0), h(0) {
}

constexpr Rect2i::Rect2i(const Vector2i &position, const Vector2i &size): x(position.x), y(position.y), w(size.x), h(size.y) {
}

constexpr Rect2i::Rect2i(const int_t position_x, const int_t position_y, const int_t size_x, const int_t size_y): x(position_x), y(position_y), w(size_x), h(size_y) {
}

constexpr Rect2i::Rect2i(const Rect2 &rect): x(rect.x), y(rect.y), w(rect.w), h(rect.h) {
}

constexpr Rect2i::Rect2i(const Rect2i &rect): x(rect.x), y(rect.y), w(rect.w), h(rect.h) {
}

constexpr Rect2i::Rect2i(const SDL_Rect &rect): x(rect.x), y(rect.y), w(rect.w), h(rect.h) {
}

constexpr Rect2i::Rect2i(const SDL_FRect &frect): x(frect.x), y(frect.y), w(frect.w), h(frect.h) {
}

constexpr void Rect2i::operator=(const Rect2i &right) {
	x = right.x;
	y = right.y;
	w = right.w;
	h = right.h;
}

constexpr bool Rect2i::operator==(const Rect2i &right) const {
	return x == right.x && y == right.y && w == right.w && h == right.h;
}

constexpr bool Rect2i::operator!=(const Rect2i &right) const {
	return get_position() != right.get_position() && get_size() != right.get_size();
}

constexpr bool Rect2i::operator<(const Rect2i &right) const {
	return get_position() < right.get_position() && get_size() < right.get_size();
}

constexpr bool Rect2i::operator<=(const Rect2i &right) const {
	return get_position() <= right.get_position() && get_size() <= right.get_size();
}

constexpr bool Rect2i::operator>(const Rect2i &right) const {
	return get_position() > right.get_position() && get_size() > right.get_size();
}

constexpr bool Rect2i::operator>=(const Rect2i &right) const {
	return get_position() >= right.get_position() && get_size() >= right.get_size();
}

constexpr Rect2i Rect2i::operator+(const Rect2i &right) const {
	return Rect2i(get_position() + right.get_position(), get_size() + right.get_size());
}

constexpr Rect2i Rect2i::operator-(const Rect2i &right) const {
	return Rect2i(get_position() - right.get_position(), get_size() - right.get_size());
}

constexpr Rect2i Rect2i::operator*(const Rect2i &right) const {
	return Rect2i(get_position() * right.get_position(), get_size() - right.get_size());
}

constexpr Rect2i Rect2i::operator*(const int_t right) const {
	return Rect2i(get_position() * right, get_size() * right);
}

constexpr Rect2i Rect2i::operator/(const Rect2i &right) const {
	return Rect2i(get_position() / right.get_position(), get_size() / right.get_size());
}

constexpr Rect2i Rect2i::operator/(const int_t right) const {
	return Rect2i(get_position() / right, get_size() / right);
}

constexpr void Rect2i::operator+=(const Rect2i &right) {
	x += right.x;
	y += right.y;
	w += right.w;
	h += right.h;
}

constexpr void Rect2i::operator-=(const Rect2i &right) {
	x -= right.x;
	y -= right.y;
	w -= right.w;
	h -= right.h;
}

constexpr void Rect2i::operator*=(const Rect2i &right) {
	x *= right.x;
	y *= right.y;
	w *= right.w;
	h *= right.h;
}

constexpr void Rect2i::operator*=(const int_t right) {
	x *= right;
	y *= right;
	w *= right;
	h *= right;
}

constexpr void Rect2i::operator/=(const Rect2i &right) {
	x /= right.x;
	y /= right.y;
	w /= right.w;
	h /= right.h;
}

constexpr void Rect2i::operator/=(const int_t right) {
	x /= right;
	y /= right;
	w /= right;
	h /= right;
}

constexpr int_t Rect2i::operator[](const int index) const {
	switch (index) {
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return w;
		case 3:
			return h;
	}
	return 0;
}

constexpr Vector2i Rect2i::get_position() const {
	return Vector2i(x, y);
}

constexpr Vector2i Rect2i::get_size() const {
	return Vector2i(w, h);
}

constexpr bool Rect2i::has_point(const Vector2i &point) const {
	if (point.x < x)
		return false;
	if (point.y < y)
		return false;
	if (point.x >= (x + w))
		return false;
	if (point.y >= (y + h))
		return false;

	return true;
}

constexpr bool Rect2i::has_area() const {
	return w > 0 && h > 0;
}

constexpr bool Rect2i::intersects(const Rect2i &rect2i, const bool include_borders) const {
	if (include_borders) {
		if (x > (rect2i.x + rect2i.w))
			return false;

		if ((x + w) < rect2i.x)
			return false;

		if (y > (rect2i.y + rect2i.h))
			return false;

		if ((y + h) < rect2i.y)
			return false;
	} else {
		if (x >= (rect2i.x + rect2i.w))
			return false;

		if ((x + w) <= rect2i.x)
			return false;

		if (y >= (rect2i.y + rect2i.h))
			return false;

		if ((y + h) <= rect2i.y)
			return false;
	}

	return true;
}

constexpr Rect2i Rect2i::merge(const Rect2i &right) const {
	Rect2i new_rect;

	new_rect.x = std::min(right.x, x);
	new_rect.y = std::min(right.y, y);

	new_rect.w = std::max(right.x + right.w, x + w);
	new_rect.h = std::max(right.y + right.h, y + h);

	new_rect.w -= new_rect.x;
	new_rect.h -= new_rect.y;

	return new_rect;
}

constexpr Rect2i Rect2i::remove_negative_size() const {
	Rect2i rect = *this;
	if (w < 0.0) {
		rect.x += w;
		rect.w = -w;
	}

	if (h < 0.0) {
		rect.y += h;
		rect.h = -h;
	}

	return rect;
}

constexpr Rect2i Rect2i::expand(const Vector2i &to) const {
	Rect2i rect = *this;
	rect.expand_to(to);
	return rect;
}

constexpr void Rect2i::expand_to(const Vector2i &to) {
	int_t begin_x = x;
	int_t begin_y = y;
	int_t end_x = x + w;
	int_t end_y = y + h;

	if (to.x < begin_x)
		begin_x = to.x;

	if (to.y < begin_y)
		begin_y = to.y;

	if (to.x > end_x)
		end_x = to.x;

	if (to.y > end_y)
		end_y = to.y;

	x = begin_x;
	y = begin_y;
	w = end_x - begin_x;
	h = end_y - begin_y;
}

constexpr void Rect2i::set_position(const Vector2i &new_position) {
	x = new_position.x;
	y = new_position.y;
}

constexpr void Rect2i::set_size(const Vector2i &new_size) {
	w = new_size.x;
	h = new_size.y;
}

}
