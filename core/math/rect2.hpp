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
	* Constructs a Rect2 with its x, y, w, and h properties set to 0.
	*/
	Rect2();

	/** 
	* Constructs a Rect2 by @param position and @param size.
	*/
	Rect2(const Vector2 &position, const Vector2 &size);

	/**
	* Constructs a Rect2 by setting its x and y values to @param position_x and @param position_y and w and h values to @param size_x and @param size_y.
	*/
	Rect2(const real_t position_x, const real_t position_y, const real_t size_x, const real_t size_y);

	/**
	* Constructs a Rect2 as a copy of the given Rect2.
	*/
	Rect2(const Rect2 &rect);

	/**
	* Constructs a Rect2 from a Rect2i.
	*/
	Rect2(const Rect2i &rect);

	/**
	* Constructs a Rect2 from a SDL_Rect.
	*/
	Rect2(const SDL_Rect &rect);

	/**
	* Constructs a Rect2 from a SDL_FRect.
	*/
	Rect2(const SDL_FRect &frect);

	/**
	* Sets the x, y, w, and h properties to that of @param right.
	*/
	void operator=(const Rect2 &right);

	/** 
	* @returns true if both x, y, w, and h of the rectangles are exactly equal, respectively.
	* @note due to floating-point precision errors, consider using Math::is_equal_approx instead, which is more reliable.
	*/
	bool operator==(const Rect2 &right) const;
	
	/** 
	* @returns true if both x, y, w, and h of the rectangles are exactly equal, respectively.
	* @note due to floating-point precision errors, consider using Math::is_equal_approx instead, which is more reliable.
	*/
	bool operator!=(const Rect2 &right) const;

	/**
	* @returns true if all of the components of this rect are smaller than those of @param right_rect.
	*/
	bool operator<(const Rect2 &right_rect) const;

	/**
	* @returns true if all of the components of this rect are smaller or equal to those of @param right_rect.
	*/
	bool operator<=(const Rect2 &right_rect) const;

	/**
	* @returns true if all of the components of this rect are bigger than those of @param right_rect.
	*/
	bool operator>(const Rect2 &right_rect) const;

	/**
	* @returns true if all of the components of this rect are bigger or equal to those of @param right_rect.
	*/
	bool operator>=(const Rect2 &right_rect) const;

	/**
	* @returns this rect with its components added with with the components of @param right_rect.
	*/
	Rect2 operator+(const Rect2 &right_rect) const;
	
	/**
	* @returns this rect with its components subtracted with with the components of @param right_rect.
	*/
	Rect2 operator-(const Rect2 &right_rect) const;

	/**
	* @returns this rect with its components multiplied with the components of @param right_rect.
	*/
	Rect2 operator*(const Rect2 &right_rect) const;

	/**
	* @returns this rect with its components multiplied with @param right.
	*/
	Rect2 operator*(const real_t right) const;

	/**
	* @returns this rect with its position added with the @param right_transform origin and size multiplied by @param right_transform scale.
	*/
	Rect2 operator*(const Transform2D &right_transform) const;

	/**
	* @returns this rect with its components divided with the components of @param right_rect.
	*/
	Rect2 operator/(const Rect2 &right_rect) const;

	/**
	* @returns this rect with its components multiplied by @param right.
	*/
	Rect2 operator/(const real_t right) const;

	/**
	* Adds each component of this rect by the components of @param right_rect.
	*/
	void operator+=(const Rect2 &right_rect);

	/**
	* Subtracts each component of this rect by the components of @param right_rect.
	*/
	void operator-=(const Rect2 &right_rect);

	/**
	* Multiplies each component of this rect by the components of @param right_rect.
	*/
	void operator*=(const Rect2 &right_rect);

	/**
	* Multiplies each component of this rect by @param right.
	*/
	void operator*=(const real_t right);

	/**
	* Adds the @param right_transform origin to the position and multiplies the size by @param right_transform scale.
	*/
	void operator*=(const Transform2D &right);

	/**
	* Divides each component of this rect by the components of @param right_rect.
	*/
	void operator/=(const Rect2 &right_rect);
	
	/**
	* Divides each component of this rect by @param right.
	*/
	void operator/=(const real_t right);

	/**
	* @return the rect components using their index.
	* [0] is equivalent to x, [1] is equivalent to y, [2] is equivalent to w, and [3] is equivalent to h.
	*/
	real_t operator[](const int index) const;

	/**
	* @return the inverted value of this rect.
	*/
	Rect2 operator-() const;

	/**
	* @return the same value as if the + was not there.
	* Unary + does nothing, but sometimes it can make your code more readable.
	*/
	Rect2 operator+() const;

	/**
	* Rounds each component of this rect.
	*/
	void rounded();

	/**
	* Floors each component of this rect.
	*/
	void floored();

	/**
	* Ceils each component of this rect.
	*/
	void ceiled();

	/**
	* @returns this rect with its components rounded.
	*/
	[[nodiscard]] Rect2 round() const;

	/**
	* @returns this rect with its components floored.
	*/
	[[nodiscard]] Rect2 floor() const;

	/**
	* @returns this rect with its components ceiled.
	*/
	[[nodiscard]] Rect2 ceil() const;

	/**
	* @returns a string representation as '(x, y, w, h)'.
	*/
	[[nodiscard]] std::string to_string() const;

	/**
	* @returns a Rect2 that encloses both this rectangle and @param right around the edges.
	*/
	[[nodiscard]] Rect2 merge(const Rect2 &right) const;

	/**
	* @returns this rect with its components set to absolute values of themselfs.
	*/
	[[nodiscard]] Rect2 abs() const;

	/**
	* @returns this rect with negative sizes removed.
	*/
	[[nodiscard]] Rect2 remove_negative_size() const;

	/**
	* @returns a copy of this rectangle expanded to align the edges with the given @param to point, if necessary.
	*/
	[[nodiscard]] Rect2 expand(const Vector2 &to) const;

	/**
	* @returns a vector2 with the x and y properties set to this rectangles x and y properties.
	*/
	Vector2 get_position() const;

	/**
	* @returns a vector2 with the x and y properties set to this rectangles w and h properties.
	*/
	Vector2 get_size() const;

	/**
	* @returns true if @param point is inside this rect.
	*/
	bool has_point(const Vector2 &point) const;

	/**
	* @returns true if the width and height of this rect is higher or equal to 0.
	*/
	bool has_area() const;

	/**
	* @returns true if this rectangle overlaps with the @param rect2. The edges of both rectangles are excluded, unless @param include_borders is true.
	*/
	bool intersects(const Rect2 &rect2, const bool include_borders = false) const;

	/**
	* Aligns the edges of this rect with the edges with the given @param to point, if necessary.
	*/
	void expand_to(const Vector2 &to);

	/**
	* Sets the x and y properties to that of @param new_position x and y values.
	*/
	void set_position(const Vector2 &new_position);

	/**
	* Sets the w and h properties to that of @param new_size x and y values.
	*/
	void set_size(const Vector2 &new_size);

	[[nodiscard]] SDL_Rect to_sdl_rect() const;
	[[nodiscard]] SDL_FRect to_sdl_frect() const;

	static const Rect2 EMPTY;
	static SDL_Rect to_sdl_rect(const Rect2 &rect2);
	static SDL_FRect to_sdl_frect(const Rect2 &rect);
};

struct Rect2i {
	int_t x;
	int_t y;
	int_t w;
	int_t h;

	Rect2i();
	Rect2i(const Vector2i &position, const Vector2i &size);
	Rect2i(const int_t x, const int_t y, const int_t w, const int_t h);
	Rect2i(const Rect2 &rect);
	Rect2i(const Rect2i &rect);
	Rect2i(const SDL_Rect &rect);
	Rect2i(const SDL_FRect &frect);

	void operator=(const Rect2i &right);
	bool operator==(const Rect2i &right) const;
	bool operator!=(const Rect2i &right) const;

	bool operator<(const Rect2i &right) const;
	bool operator<=(const Rect2i &right) const;
	bool operator>(const Rect2i &right) const;
	bool operator>=(const Rect2i &right) const;

	Rect2i operator+(const Rect2i &right) const;
	Rect2i operator-(const Rect2i &right) const;

	Rect2i operator*(const Rect2i &right) const;
	Rect2i operator*(const int_t right) const;

	Rect2i operator/(const Rect2i &right) const;
	Rect2i operator/(const int_t right) const;

	void operator+=(const Rect2i &right);
	void operator-=(const Rect2i &right);

	void operator*=(const Rect2i &right);
	void operator*=(const int_t right);

	void operator/=(const Rect2i &right);
	void operator/=(const int_t right);

	int_t operator[](const int index) const;
	Rect2i operator-() const;
	Rect2i operator+() const;

	Vector2i get_position() const;
	Vector2i get_size() const;

	[[nodiscard]] std::string to_string() const;
	[[nodiscard]] Rect2i merge(const Rect2i &right) const;
	[[nodiscard]] Rect2i abs() const;
	[[nodiscard]] Rect2i remove_negative_size() const;
	[[nodiscard]] Rect2i expand(const Vector2i &to) const;

	void set_position(const Vector2i &new_position);
	void set_size(const Vector2i &new_size);
	bool has_point(const Vector2i &point) const;
	bool has_area() const;
	bool intersects(const Rect2i &rect2i, const bool include_borders = false) const;
	void expand_to(const Vector2i &to);

	[[nodiscard]] SDL_Rect to_sdl_rect() const;
	[[nodiscard]] SDL_FRect to_sdl_frect() const;

	static const Rect2i EMPTY;
	static SDL_Rect to_sdl_rect(const Rect2i &rect2i);
	static SDL_FRect to_sdl_frect(const Rect2i &rect2i);
};

}
