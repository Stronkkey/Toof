#pragma once

#include <core/math/vector2.hpp>

#include <cereal/cereal.hpp>

namespace sdl {

struct Transform2D;

/**
* A 2D axis-aligned bounding box using a generic T.
*/
template<class T>
struct Rect2 {
	using value_type = T;

	/**
	* The x axis of the origin point. Usually the top-left corner of the rectangle.
	*/
	T x;

	/**
	* The y axis of the origin point. Usually the top-left corner of the rectangle.
	*/
	T y;

	/**
	* The rectangle's width, starting from the origin. Setting this value also affects the end point.
	*/
	T w;

	/**
	* The rectangle's height, starting from the origin. Setting this value also affects the end point.
	*/
	T h;

	/**
	* Constructs a Rect2 with its x, y, w, and h properties set to 0.
	*/
	constexpr Rect2(): x(0), y(0), w(0), h(0) {
	}

	/** 
	* Constructs a Rect2 by @param position and @param size.
	*/
	constexpr Rect2(const Vector2<T> &position, const Vector2<T> &size): x(position.x), y(position.y), w(size.x), h(size.y) {
	}

	/**
	* Constructs a Rect2 by setting its x and y values to @param position_x and @param position_y and w and h values to @param size_x and @param size_y.
	*/
	constexpr Rect2(const T position_x, const T position_y, const T size_x, const T size_y): x(position_x), y(position_y), w(size_x), h(size_y) {
	}

	/**
	* Constructs a Rect2 as a copy of the given Rect2.
	*/
	constexpr Rect2(const Rect2 &rect): x(rect.x), y(rect.y), w(rect.w), h(rect.h) {
	}

	/**
	* Constructs a Rect2 as a copy of the given Rect2.
	*/
	template<class T2>
	constexpr Rect2(const Rect2<T2> &rect): x(rect.x), y(rect.y), w(rect.w), h(rect.h) {
	}

	/**
	* Constructs a Rect2 from a SDL_Rect.
	*/
	constexpr Rect2(const SDL_Rect &rect): x(rect.x), y(rect.y), w(rect.w), h(rect.h) {
	}

	/**
	* Constructs a Rect2 from a SDL_FRect.
	*/
	constexpr Rect2(const SDL_FRect &frect): x(frect.x), y(frect.y), w(frect.w), h(frect.h) {
	}

	/**
	* Sets the x, y, w, and h properties to that of @param right.
	*/
	constexpr void operator=(const Rect2 &right) {
		x = right.x;
		y = right.y;
		w = right.w;
		h = right.h;
	}

	/** 
	* @returns true if both x, y, w, and h of the rectangles are exactly equal, respectively.
	* @note due to floating-point precision errors, consider using Math::is_equal_approx instead, which is more reliable.
	*/
	constexpr bool operator==(const Rect2 &right) const {
		return x == right.x && y == right.y && w == right.w && h == right.h;
	}
	
	/** 
	* @returns true if both x, y, w, and h of the rectangles are exactly equal, respectively.
	* @note due to floating-point precision errors, consider using Math::is_equal_approx instead, which is more reliable.
	*/
	constexpr bool operator!=(const Rect2 &right) const {
		return x != right.x || y != right.y || w != right.w || h != right.h;
	}

	/**
	* @returns true if all of the components of this rect are smaller than those of @param right.
	*/
	constexpr bool operator<(const Rect2 &right) const {
		return x < right.x && y < right.y && w < right.w && h < right.h;
	}

	/**
	* @returns true if all of the components of this rect are smaller or equal to those of @param right.
	*/
	constexpr bool operator<=(const Rect2 &right) const {
		return x <= right.x && y <= right.y && w <= right.w && h != right.h;
	}

	/**
	* @returns true if all of the components of this rect are bigger than those of @param right.
	*/
	constexpr bool operator>(const Rect2 &right) const {
		return x > right.x && y > right.y && w > right.w && h > right.h;
	}

	/**
	* @returns true if all of the components of this rect are bigger or equal to those of @param right.
	*/
	constexpr bool operator>=(const Rect2 &right) const {
		return x >= right.x && y >= right.y && w >= right.w && h >= right.h;
	}

	/**
	* @returns this rect with its components added with with the components of @param right.
	*/
	constexpr Rect2 operator+(const Rect2 &right) const {
		return Rect2(x + right.x, y + right.y, w + right.w, h + right.h);
	}
	
	/**
	* @returns this rect with its components subtracted with with the components of @param right.
	*/
	constexpr Rect2 operator-(const Rect2 &right) const {
		return Rect2(x - right.x, y - right.y, w - right.w, h - right.h);
	}

	/**
	* @returns this rect with its components multiplied with the components of @param right.
	*/
	constexpr Rect2 operator*(const Rect2 &right) const {
		return Rect2(x * right.x, y * right.y, w * right.w, h * right.h);
	}

	/**
	* @returns this rect with its components multiplied with @param right.
	*/
	constexpr Rect2 operator*(const T right) const {
		return Rect2(x * right, y * right, w * right, h * right);
	}

	/**
	* @returns this rect with its components divided with the components of @param right.
	*/
	constexpr Rect2 operator/(const Rect2 &right) const {
		return Rect2(x / right.x, y / right.y, w / right.w, h / right.h);
	}

	/**
	* @returns this rect with its components multiplied by @param right.
	*/
	constexpr Rect2 operator/(const T right) const {
		return Rect2(x / right, y / right, w / right, h / right);
	}

	/**
	* Adds each component of this rect by the components of @param right.
	*/
	constexpr void operator+=(const Rect2 &right) {
		x += right.x;
		y += right.y;
		w += right.w;
		h += right.h;
	}

	/**
	* Subtracts each component of this rect by the components of @param right.
	*/
	constexpr void operator-=(const Rect2 &right) {
		x -= right.x;
		y -= right.y;
		w -= right.w;
		h -= right.h;
	}

	/**
	* Multiplies each component of this rect by the components of @param right.
	*/
	constexpr void operator*=(const Rect2 &right) {
		x *= right.x;
		y *= right.y;
		w *= right.w;
		h *= right.h;
	}

	/**
	* Multiplies each component of this rect by @param right.
	*/
	constexpr void operator*=(const T right) {
		x *= right;
		y *= right;
		w *= right;
		h *= right;
	}

	/**
	* Divides each component of this rect by the components of @param right.
	*/
	constexpr void operator/=(const Rect2 &right) {
		x /= right.x;
		y /= right.y;
		w /= right.w;
		h /= right.h;
	}
	
	/**
	* Divides each component of this rect by @param right.
	*/
	constexpr void operator/=(const T right) {
		x /= right;
		y /= right;
		w /= right;
		h /= right;
	}

	/**
	* @return the rect components using their index.
	* [0] is equivalent to x, [1] is equivalent to y, [2] is equivalent to w, and [3] is equivalent to h.
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
	* @return the inverted value of this rect.
	*/
	constexpr Rect2 operator-() const {
		return Rect2(-x, -y, -w, -h);
	}

	/**
	* @return the same value as if the + was not there.
	* Unary + does nothing, but sometimes it can make your code more readable.
	*/
	constexpr Rect2 operator+() const {
		return Rect2(x, y, w, h);
	}

	/**
	* @returns a string representation as '[P: (x, y), S: (w, h)].
	*/
	[[nodiscard]] operator String() const {
		return vformat("[P: ({}, {}), S: ({}, {})]", x, y, w, h);
	}

	/**
	* Rounds each component of this rect.
	*/
	constexpr void rounded() {
		x = std::round(x);
		y = std::round(y);
		w = std::round(w);
		h = std::round(h);
	}

	/**
	* Floors each component of this rect.
	*/
	constexpr void floored() {
		x = std::floor(x);
		y = std::floor(y);
		w = std::floor(w);
		h = std::floor(h);
	}

	/**
	* Ceils each component of this rect.
	*/
	constexpr void ceiled() {
		x = std::ceil(x);
		y = std::ceil(y);
		w = std::ceil(w);
		h = std::ceil(h);
	}

	/**
	* @returns this rect with its components rounded.
	*/
	[[nodiscard]] constexpr Rect2 round() const {
		return Rect2(std::round(x), std::round(y), std::round(w), std::round(h));
	}

	/**
	* @returns this rect with its components floored.
	*/
	[[nodiscard]] constexpr Rect2 floor() const {
		return Rect2(std::floor(x), std::floor(y), std::floor(w), std::floor(h));
	}

	/**
	* @returns this rect with its components ceiled.
	*/
	[[nodiscard]] constexpr Rect2 ceil() const {
		return Rect2(std::ceil(x), std::ceil(y), std::ceil(w), std::ceil(h));
	}

	/**
	* @returns a Rect2 that encloses both this rectangle and @param right around the edges.
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
	* @returns this rect with its components set to absolute values of themselfs.
	*/
	[[nodiscard]] Rect2 abs() const {
		return Rect2(std::abs(x), std::abs(y), std::abs(w), std::abs(h));
	}

	/**
	* @returns this rect with negative sizes removed.
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
	* @returns a copy of this rectangle expanded to align the edges with the given @param to point, if necessary.
	*/
	[[nodiscard]] constexpr Rect2 expand(const Vector2f &to) const {
		Rect2 rect = *this;
		rect.expand_to(to);
		return rect;
	}

	/**
	* @returns a vector2 with the x and y properties set to this rectangles x and y properties.
	*/
	constexpr Vector2<T> get_position() const {
		return Vector2<T>(x, y);
	}

	/**
	* @returns a vector2 with the x and y properties set to this rectangles w and h properties.
	*/
	constexpr Vector2<T> get_size() const {
		return Vector2<T>(w, h);
	}

	/**
	* @returns true if @param point is inside this rect.
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
	* @returns true if the width and height of this rect is higher or equal to 0.
	*/
	constexpr bool has_area() const {
		return w > 0 && h > 0;
	}

	/**
	* @returns true if this rectangle overlaps with the @param rect2. The edges of both rectangles are excluded, unless @param include_borders is true.
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
	* Aligns the edges of this rect with the edges with the given @param to point, if necessary.
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
	* Sets the x and y properties to that of @param position x and y values.
	*/
	constexpr void set_position(const Vector2<T> &position) {
		x = position.x;
		y = position.y;
	}

	/**
	* Sets the w and h properties to that of @param size x and y values.
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

typedef Rect2<real> Rect2f;
typedef Rect2<integer> Rect2i;

/**
* @returns @param rect2f with its position added with the @param transfor2nd origin and size multiplied by @param transform2d scale.
*/
Rect2f rect2f_add_transform(const Rect2f &rect2f, const Transform2D &transform2d);

}