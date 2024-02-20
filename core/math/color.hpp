#pragma once

#include <string>
#include <core/math/math_defs.hpp>

#include <SDL_pixels.h>

namespace sdl {

/*
*A color represented in RGBA format.
*/
struct Color {
	// Constructs a default Color from opaque black.
	constexpr Color();
	// Constructs a Color from param from_color, with a set to the given alpha value.
	constexpr Color(const Color &from_color, const uint16_t alpha);
	// Constructs a Color as a copy of the given Color.
	constexpr Color(const Color &from_color);
	// Constructs a Color from RGB values, typically between 0 and 255. a is set to 255.
	constexpr Color(const uint16_t red, const uint16_t green, const uint16_t blue);
	// Constructs a Color from RGBA values, typically between 0 and 255.
	constexpr Color(const uint16_t red, const uint16_t green, const uint16_t blue, const uint16_t alpha);

	/**
	* The color's red component, typically on the range of 0 to 255.
	*/
	uint16_t r;

	/**
	* The color's green component, typically on the range of 0 to 255.
	*/
	uint16_t g;

	/**
	* The color's blue component, typically on the range of 0 to 255.
	*/
	uint16_t b;
	
	/**
	* The color's alpha component, typically on the range of 0 to 255. A value of 0 means that the color is fully transparent. A value of 255 means that the color is fully opaque.
	*/
	uint16_t a;

	/**
	* @return a new color resulting from overlaying this color over the given color.
	* In a painting program, you can imagine it as the over color painted over this color (including alpha).
	*/
	[[nodiscard]] Color blend(const Color &over) const;

	/**
	* @return a new color resulting from making this color darker by the specified amount (ratio from 0 to 255).
	*/
	[[nodiscard]] constexpr Color darkened(const float amount) const;

	/**
	* Sets the r, g, b, and a to that of @param right_color.
	*/
	constexpr void operator=(const Color &right_color);

	/**
	* @return true if this color and @param right_color are not exactly equal.
	* @note due to floating-point precision errors, consider using Math::is_equal_approx instead, which is more reliable.
	*/
	constexpr bool operator!=(const Color &right_color) const;

	/**
	* @return true if this color and @param right_color are exactly equal.
	* @note due to floating-point precision errors, consider using Math::is_equal_approx instead, which is more reliable.
	*/
	constexpr bool operator==(const Color &right_color) const;
	
	/**
	* @returns this color with its components multiplied by each component of the @param right_color
	*/
	constexpr Color operator*(const Color &right_color) const;

	/**
	* @returns this color with its components multiplied by @param right
	*/
	constexpr Color operator*(const float right) const;

	/**
	* Modulates this color with @param right_color.
	*/
	constexpr void operator*=(const Color &right);

	/**
	* Multiplies each component of this color with @param right.
	*/
	constexpr void operator*=(const float right);

	/**
	* @returns this color with its components added by each component of the @param right_color
	*/
	constexpr Color operator+(const Color &right_color) const;

	/**
	* @returns this color with its components subtracted by each component of the @param right_color
	*/
	constexpr Color operator-(const Color &right_color) const;
	
	/**
	* Adds each component of this color by the components of the @param right_color.
	*/
	constexpr void operator+=(const Color &right_color);
	
	/**
	* Subtracts each component of this color by the components of the @param right_color.
	*/
	constexpr void operator-=(const Color &right_color);

	/**
	* @returns this color with its components divided by each component by the @param right_color
	*/
	constexpr Color operator/(const Color &right_color) const;

	/**
	* @returns this color with its components divided by @param right. 
	*/
	constexpr Color operator/(const float right) const;

	/**
	* Divides each component of this color by the components of the @param right_color.
	*/
	constexpr void operator/=(const Color &right_color);

	/**
	* Divides each component of this color by @param right.
	*/
	constexpr void operator/=(const float right);

	/**
	* @return an SDL_Color with the same r, b, g, and a value as this color.
	*/
	[[nodiscard]] SDL_Color to_sdl_color() const;

	/**
	* @return a String reprenstation of the color "(r, g, b , a)"
	*/
	[[nodiscard]] std::string to_string() const;


	/**
	* @return the same value as if the + was not there.
	* Unary + does nothing, but sometimes it can make your code more readable.
	*/
	constexpr Color operator+() const;

	/**
	* @return the inverted value of this color.
	* This is equivalent to Color::WHITE - c or Color(1 - c.r, 1 - c.g, 1 - c.b, 1 - c.a).
	*/
	constexpr Color operator-() const;

	/**
	* @return the color components using their index.
	* [0] is equivalent to r, [1] is equivalent to g, [2] is equivalent to b, and [3] is equivalent to a.
	*/
	constexpr uint16_t operator[](const int index) const;

	/**
	* Color white (equivalent to hex code #ffffff).
	*/
	static const Color WHITE;

	/**
	* Color black (equivalent to hex code #000000).
	*/
	static const Color BLACK;

	/**
	* Color black that is transparent (equivalent to hex code #000000 with transparency of 0).
	*/
	static const Color TRANSPARENT;

	/**
	* Color red (equivalent to hex code #ff0000).
	*/
	static const Color RED;

	/**
	* Color green (equivalent to hex code #00ff00).
	*/
	static const Color GREEN;

	/**
	* Color blue (equivalent to hex code #0000ff).
	*/
	static const Color BLUE;
};

/**
* A colour represented in RGBA format.
*/
typedef Color Colour;

constexpr Color::Color(): r(0), g(0), b(0), a(255) {
}

constexpr Color::Color(const Color &from_color, const uint16_t alpha): r(from_color.r), g(from_color.g), b(from_color.b), a(alpha) {
}

constexpr Color::Color(const Color &from_color): r(from_color.r), g(from_color.g), b(from_color.b), a(from_color.a) {
}

constexpr Color::Color(const uint16_t red, const uint16_t green, const uint16_t blue): r(red), g(green), b(blue), a(255) {
}

constexpr Color::Color(const uint16_t red, const uint16_t green, const uint16_t blue, const uint16_t alpha): r(red), g(green), b(blue), a(alpha) {
}

constexpr Color Color::darkened(const float amount) const {
	Color darkened_color = *this;
	darkened_color.r *= (1.0f - -amount);
	darkened_color.g *= (1.0f - -amount);
	darkened_color.b *= (1.0f - -amount);
	return darkened_color;
}

constexpr void Color::operator=(const Color &right) {
	r = right.r;
	g = right.g;
	b = right.b;
	a = right.a;
}

constexpr bool Color::operator!=(const Color &right_color) const {
	return r != right_color.r || g != right_color.g || b != right_color.b || a != right_color.a;
}

constexpr bool Color::operator==(const Color &right_color) const {
	return r == right_color.r && g == right_color.g && b == right_color.b && a == right_color.a;
}

constexpr Color Color::operator*(const Color &right) const {
	Color multiplied_color = *this;
	multiplied_color.r *= (right.r / 255);
	multiplied_color.g *= (right.g / 255);
	multiplied_color.b *= (right.b / 255);
	multiplied_color.a *= (right.a / 255);
	return multiplied_color;
}

constexpr Color Color::operator*(const float right) const {
	Color multiplied_color = *this;
	multiplied_color.r *= right;
	multiplied_color.g *= right;
	multiplied_color.b *= right;
	multiplied_color.a *= right;
	return multiplied_color;
}

constexpr void Color::operator*=(const float right) {
	r *= right;
	g *= right;
	b *= right;
	a *= right;
}

constexpr void Color::operator*=(const Color &right) {
	r *= (right.r / 255);
	g *= (right.g / 255);
	b *= (right.b / 255);
	a *= (right.a / 255);
}

constexpr Color Color::operator+(const Color &right) const {
	Color added_color = *this;
	added_color.a += right.a;
	added_color.r += right.r;
	added_color.g += right.g;
	added_color.b += right.b;
	return added_color;
}

constexpr Color Color::operator-(const Color &right) const {
	Color added_color = *this;
	added_color.a -= right.a;
	added_color.r -= right.r;
	added_color.g -= right.g;
	added_color.b -= right.b;
	return added_color;
}

constexpr Color Color::operator+() const {
	Color unary_color = *this;
	unary_color.a = +unary_color.a;
	unary_color.r = +unary_color.r;
	unary_color.g = +unary_color.g;
	unary_color.b = +unary_color.b;
	return unary_color;
}

constexpr Color Color::operator-() const {
	Color unary_color = *this;
	unary_color.a = -unary_color.a;
	unary_color.r = -unary_color.r;
	unary_color.g = -unary_color.g;
	unary_color.b = -unary_color.b;
	return unary_color;
}

constexpr Color Color::operator/(const Color &right) const {
	Color divided_color = *this;
	divided_color.a /= right.a;
	divided_color.r /= right.r;
	divided_color.g /= right.g;
	divided_color.b /= right.b;
	return divided_color;
}

constexpr Color Color::operator/(const float right) const {
	Color divided_color = *this;
	divided_color.a /= right;
	divided_color.r /= right;
	divided_color.g /= right;
	divided_color.b /= right;
	return divided_color;
}

constexpr void Color::operator/=(const Color &right) {
	a /= right.a;
	r /= right.r;
	g /= right.g;
	b /= right.b;
}

constexpr void Color::operator/=(const float right) {
	a /= right;
	r /= right;
	g /= right;
	b /= right;
}

constexpr uint16_t Color::operator[](const int index) const {
	switch (index) {
		case 0:
			return r;
		case 1:
			return g;
		case 2:
			return b;
		default:
			return 0;
	}
}

}
