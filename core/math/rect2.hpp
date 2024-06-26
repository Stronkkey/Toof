/*  This file is part of the Toof Engine. */
/** @file rect2.hpp */
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

#include <cereal/cereal.hpp>

namespace Toof {

struct Transform2D;

/**
* @brief A 2D axis-aligned bounding box using a generic T.
*/
template<class T>
struct Rect2 {
	using value_type = T;

	static_assert(std::is_arithmetic<value_type>::value, "value_type of Rect2 must be an arithmetic type.");

	/**
	* @brief The x axis of the origin point. Usually the top-left corner of the rectangle.
	*/
	T x;

	/**
	* @brief The y axis of the origin point. Usually the top-left corner of the rectangle.
	*/
	T y;

	/**
	* @brief The rectangle's width, starting from the origin. Setting this value also affects the end point.
	*/
	T w;

	/**
	* @brief The rectangle's height, starting from the origin. Setting this value also affects the end point.
	*/
	T h;

	/**
	* @brief Constructs a Rect2 with its x, y, w, and h properties set to 0.
	*/
	constexpr Rect2(): x(0), y(0), w(0), h(0) {
	}

	/** 
	* @brief Constructs a Rect2 with the given position and size.
	*/
	constexpr Rect2(const Vector2<T> &position, const Vector2<T> &size): x(position.x), y(position.y), w(size.x), h(size.y) {
	}

	/**
	* @brief Constructs a Rect2 by setting its position to @b position_x, @b position_y, and its size to @b size_x, @b size_y.
	*/
	constexpr Rect2(const T position_x, const T position_y, const T size_x, const T size_y): x(position_x), y(position_y), w(size_x), h(size_y) {
	}

	/**
	* @brief Constructs a Rect2 as a copy of the given Rect2.
	*/
	constexpr Rect2(const Rect2 &rect): x(rect.x), y(rect.y), w(rect.w), h(rect.h) {
	}

	/**
	* @brief Constructs a Rect2 as a copy of the given Rect2.
	*/
	template<class T2>
	constexpr Rect2(const Rect2<T2> &rect): x(rect.x), y(rect.y), w(rect.w), h(rect.h) {
	}

	/**
	* @brief Constructs a Rect2 from a SDL_Rect.
	*/
	constexpr Rect2(const SDL_Rect &rect): x(rect.x), y(rect.y), w(rect.w), h(rect.h) {
	}

	/**
	* @brief Constructs a Rect2 from a SDL_FRect.
	*/
	constexpr Rect2(const SDL_FRect &frect): x(frect.x), y(frect.y), w(frect.w), h(frect.h) {
	}

	/**
	* @brief Sets the x, y, w, and h properties to that of the given Rect2.
	*/
	constexpr void operator=(const Rect2 &right) {
		x = right.x;
		y = right.y;
		w = right.w;
		h = right.h;
	}

	/** 
	* @brief Returns @b true if both x, y, w, and h of the rectangles are exactly equal, respectively.
	* @note due to floating-point precision errors, consider using Math::is_equal_approx instead, which is more reliable.
	*/
	constexpr bool operator==(const Rect2 &right) const {
		return x == right.x && y == right.y && w == right.w && h == right.h;
	}
	
	/** 
	* @brief Returns true if both x, y, w, and h of the rectangles are exactly equal, respectively.
	* @note due to floating-point precision errors, consider using Math::is_equal_approx instead, which is more reliable.
	*/
	constexpr bool operator!=(const Rect2 &right) const {
		return x != right.x || y != right.y || w != right.w || h != right.h;
	}

	/**
	* @brief Returns true if all of the components of this rect are smaller than those of the given Rect2.
	*/
	constexpr bool operator<(const Rect2 &right) const {
		return x < right.x && y < right.y && w < right.w && h < right.h;
	}

	/**
	* @brief Returns true if all of the components of this rect are smaller or equal to those of the given Rect2.
	*/
	constexpr bool operator<=(const Rect2 &right) const {
		return x <= right.x && y <= right.y && w <= right.w && h != right.h;
	}

	/**
	* @brief Returns true if all of the components of this rect are bigger than those of the given Rect2.
	*/
	constexpr bool operator>(const Rect2 &right) const {
		return x > right.x && y > right.y && w > right.w && h > right.h;
	}

	/**
	* @brief Returns true if all of the components of this rect are bigger or equal to those of the given Rect2.
	*/
	constexpr bool operator>=(const Rect2 &right) const {
		return x >= right.x && y >= right.y && w >= right.w && h >= right.h;
	}

	/**
	* @brief Returns this rect with its components added with with the components of the given Rect2.
	*/
	constexpr Rect2 operator+(const Rect2 &right) const {
		return Rect2(x + right.x, y + right.y, w + right.w, h + right.h);
	}
	
	/**
	* @brief Returns this rect with its components subtracted with with the components of the given Rect2.
	*/
	constexpr Rect2 operator-(const Rect2 &right) const {
		return Rect2(x - right.x, y - right.y, w - right.w, h - right.h);
	}

	/**
	* @brief Returns this rect with its components multiplied with the components of the given Rect2.
	*/
	constexpr Rect2 operator*(const Rect2 &right) const {
		return Rect2(x * right.x, y * right.y, w * right.w, h * right.h);
	}

	/**
	* @brief Returns this rect with its components multiplied with the given amount.
	*/
	constexpr Rect2 operator*(const T right) const {
		return Rect2(x * right, y * right, w * right, h * right);
	}

	/**
	* @brief Returns this rect with its components divided with the components of the given Rect2.
	*/
	constexpr Rect2 operator/(const Rect2 &right) const {
		return Rect2(x / right.x, y / right.y, w / right.w, h / right.h);
	}

	/**
	* @brief Returns this rect with its components multiplied by the given amount.
	*/
	constexpr Rect2 operator/(const T right) const {
		return Rect2(x / right, y / right, w / right, h / right);
	}

	/**
	* @brief Adds each component of this rect by the components of the given Rect2.
	*/
	constexpr void operator+=(const Rect2 &right) {
		x += right.x;
		y += right.y;
		w += right.w;
		h += right.h;
	}

	/**
	* @brief Subtracts each component of this rect by the components of the given Rect2.
	*/
	constexpr void operator-=(const Rect2 &right) {
		x -= right.x;
		y -= right.y;
		w -= right.w;
		h -= right.h;
	}

	/**
	* @brief Multiplies each component of this rect by the components of the given Rect2.
	*/
	constexpr void operator*=(const Rect2 &right) {
		x *= right.x;
		y *= right.y;
		w *= right.w;
		h *= right.h;
	}

	/**
	* @brief Multiplies each component of this rect by the given amount.
	*/
	constexpr void operator*=(const T right) {
		x *= right;
		y *= right;
		w *= right;
		h *= right;
	}

	/**
	* @brief Divides each component of this rect by the components of the given Rect2.
	*/
	constexpr void operator/=(const Rect2 &right) {
		x /= right.x;
		y /= right.y;
		w /= right.w;
		h /= right.h;
	}
	
	/**
	* @brief Divides each component of this rect by the given amount.
	*/
	constexpr void operator/=(const T right) {
		x /= right;
		y /= right;
		w /= right;
		h /= right;
	}

	/**
	* @return the rect components using their index.
	* @details [0] is equivalent to x, [1] is equivalent to y, [2] is equivalent to w, and [3] is equivalent to h.
	*/
	constexpr T operator[](const int index) const {
		switch (index) {
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return w;
			case 3:
				return h;
			default:
				return 0;
		}
	}

	/**
	* @brief Returns the inverted value of this rect.
	*/
	constexpr Rect2 operator-() const {
		return Rect2(-x, -y, -w, -h);
	}

	/**
	* @brief Returns the same value as if the + was not there.
	* Unary + does nothing, but sometimes it can make your code more readable.
	*/
	constexpr Rect2 operator+() const {
		return Rect2(x, y, w, h);
	}

	/**
	* @brief Inserts the rectangle into the stream.
	*/
	template<class CharT, class Traits>
	friend std::basic_ostream<CharT, Traits> &operator<<(std::basic_ostream<CharT, Traits> &stream, const Rect2 &rect) {
		S_STREAM_FORMAT(stream, "[P: ({}, {}), S: ({}, {})]", rect.x, rect.y, rect.w, rect.h);
		return stream;
	}

	/**
	* @brief Returns a string representation as '[P: (x, y), S: (w, h)].
	*/
	[[nodiscard]] operator String() const {
		return S_FORMAT("[P: ({}, {}), S: ({}, {})]", x, y, w, h);
	}

	/**
	* @brief Rounds each component of this rect.
	*/
	constexpr void rounded() {
		x = std::round(x);
		y = std::round(y);
		w = std::round(w);
		h = std::round(h);
	}

	/**
	* @brief Floors each component of this rect.
	*/
	constexpr void floored() {
		x = std::floor(x);
		y = std::floor(y);
		w = std::floor(w);
		h = std::floor(h);
	}

	/**
	* @brief Ceils each component of this rect.
	*/
	constexpr void ceiled() {
		x = std::ceil(x);
		y = std::ceil(y);
		w = std::ceil(w);
		h = std::ceil(h);
	}

	/**
	* @brief Returns this rect with its components rounded.
	*/
	[[nodiscard]] constexpr Rect2 round() const {
		return Rect2(std::round(x), std::round(y), std::round(w), std::round(h));
	}

	/**
	* @brief Returns this rect with its components floored.
	*/
	[[nodiscard]] constexpr Rect2 floor() const {
		return Rect2(std::floor(x), std::floor(y), std::floor(w), std::floor(h));
	}

	/**
	* @brief Returns this rect with its components ceiled.
	*/
	[[nodiscard]] constexpr Rect2 ceil() const {
		return Rect2(std::ceil(x), std::ceil(y), std::ceil(w), std::ceil(h));
	}

	/**
	* @brief Returns a Rect2 that encloses both this rectangle and the given Rect2 around the edges.
	*/
	[[nodiscard]] constexpr Rect2 merge(const Rect2 &right) const {
		Rect2 new_rect;

		new_rect.x = std::min(right.x, x);
		new_rect.y = std::min(right.y, y);

		new_rect.w = std::max(right.x + right.w, x + w);
		new_rect.h = std::max(right.y + right.h, y + h);

		new_rect.w -= new_rect.x;
		new_rect.h -= new_rect.y;

		return new_rect;
	}

	/**
	* @brief Returns this rect with its components set to absolute values of themselfs.
	*/
	[[nodiscard]] Rect2 abs() const {
		return Rect2(std::abs(x), std::abs(y), std::abs(w), std::abs(h));
	}

	/**
	* @brief Returns this rect with negative sizes removed.
	*/
	[[nodiscard]] constexpr Rect2 remove_negative_size() const {
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

	/**
	* @brief Returns a copy of this rectangle expanded to align the edges with the given point, if necessary.
	*/
	[[nodiscard]] constexpr Rect2 expand(const Vector2f &to) const {
		Rect2 rect = *this;
		rect.expand_to(to);
		return rect;
	}

	/**
	* @brief Returns a vector2 with the x and y properties set to this rectangles x and y properties.
	*/
	constexpr Vector2<T> get_position() const {
		return Vector2<T>(x, y);
	}

	/**
	* @brief Returns a vector2 with the x and y properties set to this rectangles w and h properties.
	*/
	constexpr Vector2<T> get_size() const {
		return Vector2<T>(w, h);
	}

	/**
	* @brief Returns true if the @b point is inside this rect.
	*/
	constexpr bool has_point(const Vector2<T> &point) const {
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

	/**
	* @brief Returns true if the width and height of this rect is higher or equal to 0.
	*/
	constexpr bool has_area() const {
		return w > 0 && h > 0;
	}

	/**
	* @brief Returns true if this rectangle overlaps with the given Rect2. The edges of both rectangles are excluded, unless @b include_borders is true.
	*/
	constexpr bool intersects(const Rect2 &rect2, const bool include_borders = false) const {
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

	/**
	* @brief Aligns the edges of this rect with the edges with the given @b to point, if necessary.
	*/
	constexpr void expand_to(const Vector2<T> &to) {
		T begin_x = x;
		T begin_y = y;
		T end_x = x + w;
		T end_y = y + h;

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

	/**
	* @brief Sets the x and y properties to that of the Vector2 x and y values.
	*/
	constexpr void set_position(const Vector2<T> &position) {
		x = position.x;
		y = position.y;
	}

	/**
	* @brief Sets the w and h properties to that of Vector2 x and y values.
	*/
	constexpr void set_size(const Vector2<T> &size) {
		x = size.x;
		y = size.y;
	}

	[[nodiscard]] inline SDL_Rect to_sdl_rect() const {
		SDL_Rect rect;
		rect.x = (int)x;
		rect.y = (int)y;
		rect.w = (int)w;
		rect.h = (int)h;
		return rect;
	}

	[[nodiscard]] inline SDL_FRect to_sdl_frect() const {
		SDL_FRect rect;
		rect.x = (float)x;
		rect.y = (float)y;
		rect.w = (float)w;
		rect.h = (float)h;
		return rect;
	}

	[[nodiscard]] constexpr bool is_zero_approx() const {
		return Math::is_zero_approx(x) && Math::is_zero_approx(y) && Math::is_zero_approx(w) && Math::is_zero_approx(h);
	}

	[[nodiscard]] constexpr bool is_equal_approx(const Rect2 &rect2) const {
		return Math::is_equal_approx(x, rect2.x) && Math::is_equal_approx(y, rect2.y) && Math::is_equal_approx(w, rect2.w) && Math::is_equal_approx(h, rect2.h);
	}

	template<class Archive>
	inline void serialize(Archive &archive) {
		archive(cereal::make_nvp("X", x));
		archive(cereal::make_nvp("Y", y));
		archive(cereal::make_nvp("W", w));
		archive(cereal::make_nvp("H", h));
	}
};

using Rect2f = Rect2<real>;
using Rect2i = Rect2<integer>;

using Rect2f32 = Rect2<float>;
using Rect2f64 = Rect2<double>;

using Rect2i32 = Rect2<int32_t>;
using Rect2i64 = Rect2<int64_t>;

/**
* @brief Returns the Rect2 with its position added with the transform origin and size multiplied by the transform scale.
*/
Rect2f rect2f_add_transform(const Rect2f &rect2f, const Transform2D &transform2d);

}