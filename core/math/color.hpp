#pragma once

#include <core/string/string_funcs.hpp>
#include <core/math/math_defs.hpp>

#include <cereal/cereal.hpp>

#include <SDL_pixels.h>

#ifndef __COLOR_V_TYPE__
#define __COLOR_V_TYPE__ uint8_t
#endif

namespace sdl {

/*
* A color represented in RGBA format in the range of 0 to 255 using a generic T.
*/
template<class T>
struct Color {
	using value_type = T;

	// Constructs a default Color from opaque black.
	constexpr Color(): r(0), g(0), b(0), a(255) {
	}

	// Constructs a Color from param from_color, with a set to the given alpha value.
	constexpr Color(const Color &from_color, const T alpha): r(from_color.r), g(from_color.g), b(from_color.b), a(alpha) {
	}

	// Constructs a Color as a copy of the given Color.
	constexpr Color(const Color &from_color): r(from_color.r), g(from_color.g), b(from_color.b), a(from_color.a) {
	}

	// Constructs a Color from RGB values, typically between 0 and 255. a is set to 255.
	constexpr Color(const T red, const T green, const T blue): r(red), g(green), b(blue), a(255) {
	}

	// Constructs a Color from RGBA values, typically between 0 and 255.
	constexpr Color(const T red, const T green, const T blue, const T alpha): r(red), g(green), b(blue), a(alpha) {
	}

	/**
	* The color's red component, typically on the range of 0 to 255.
	*/
	T r;

	/**
	* The color's green component, typically on the range of 0 to 255.
	*/
	T g;

	/**
	* The color's blue component, typically on the range of 0 to 255.
	*/
	T b;
	
	/**
	* The color's alpha component, typically on the range of 0 to 255. A value of 0 means that the color is fully transparent. A value of 255 means that the color is fully opaque.
	*/
	T a;

	/**
	* @return a new color resulting from overlaying this color over the given color.
	* In a painting program, you can imagine it as the over color painted over this color (including alpha).
	*/
	[[nodiscard]] inline Color blend(const Color &over) const {
		Color blended_color;
		T inverted_alpha = 255 - over.a;
		blended_color.a = ceil((a / 255.0 * inverted_alpha / 255.0 + over.a / 255.0) * 255.0);

		if (blended_color.a == 0)
			return Color(0, 0, 0, 0);

		blended_color.r = ceil((r / 255.0 * a / 255.0 * inverted_alpha / 255.0 + over.r / 255.0 * over.a / 255.0 / blended_color.a / 255) * 255.0);
		blended_color.g = ceil((g / 255.0 * a / 255.0 * inverted_alpha / 255.0 + over.g / 255.0 * over.a / 255.0 / blended_color.a / 255) * 255.0);
		blended_color.b = ceil((b / 255.0 * a / 255.0 * inverted_alpha / 255.0 + over.b / 255.0 * over.a / 255.0 / blended_color.a / 255) * 255.0);

		return blended_color;
	}

	/**
	* @return a new color resulting from making this color darker by the specified amount (ratio from 0 to 255).
	*/
	[[nodiscard]] constexpr Color darkened(const float amount) const {
		return Color(r * (255 - -amount), g * (255 - -amount), b * (255 - -amount), a * (255 - -amount));
	}

	/**
	* Sets the r, g, b, and a to that of @param right.
	*/
	constexpr void operator=(const Color &right) {
		r = right.r;
		g = right.g;
		b = right.b;
		a = right.a;
	}

	/**
	* @return true if this color and @param right are not exactly equal.
	* @note due to floating-point precision errors, consider using Math::is_equal_approx instead, which is more reliable.
	*/
	constexpr bool operator!=(const Color &right) const {
		return r != right.r || g != right.g || b != right.b || a != right.a;
	}

	/**
	* @return true if this color and @param right are exactly equal.
	* @note due to floating-point precision errors, consider using Math::is_equal_approx instead, which is more reliable.
	*/
	constexpr bool operator==(const Color &right) const {
		return r == right.r && g == right.g && b == right.b && a == right.a;
	}
	
	/**
	* @returns this color with its components multiplied by each component of the @param right
	*/
	constexpr Color operator*(const Color &right) const {
		return Color(r * (right.r / 255), g * (right.g / 255), b * (right.b / 255), a * (right.a / 255));
	}

	/**
	* @returns this color with its components multiplied by @param right
	*/
	constexpr Color operator*(const float right) const {
		return Color(r * right, g * right, b * right, a * right);
	}

	/**
	* Modulates this color with @param right.
	*/
	constexpr void operator*=(const Color &right) {
		r *= (right.r / 255);
		g *= (right.g / 255);
		b *= (right.b / 255),
		a *= (right.a / 255);
	}

	/**
	* Multiplies each component of this color with @param right.
	*/
	constexpr void operator*=(const float right) {
		r *= right;
		g *= right;
		b *= right;
		a *= right;
	}

	/**
	* @returns this color with its components added by each component of the @param right
	*/
	constexpr Color operator+(const Color &right) const {
		return Color(r + right.r, g + right.g, b + right.b, a + right.a);
	}

	/**
	* @returns this color with its components subtracted by each component of the @param right
	*/
	constexpr Color operator-(const Color &right) const {
		return Color(r - right.r, g - right.g, b - right.b, a - right.a);
	}
	
	/**
	* Adds each component of this color by the components of the @param right.
	*/
	constexpr void operator+=(const Color &right) {
		r += right.r;
		g += right.g;
		b += right.b;
		a += right.a;
	}
	
	/**
	* Subtracts each component of this color by the components of the @param right.
	*/
	constexpr void operator-=(const Color &right) {
		r -= right.r;
		g -= right.g;
		b -= right.b;
		a -= right.a;
	}

	/**
	* @returns this color with its components divided by each component by the @param right
	*/
	constexpr Color operator/(const Color &right) const {
		return Color(r / right.r, g / right.g, b / right.b, a / right.a);
	}

	/**
	* @returns this color with its components divided by @param right. 
	*/
	constexpr Color operator/(const float right) const {
		return Color(r / right, g / right, b / right, a / right);
	}

	/**
	* Divides each component of this color by the components of the @param right.
	*/
	constexpr void operator/=(const Color &right) {
		r /= right.r;
		g /= right.g;
		b /= right.b;
		a /= right.a;
	}

	/**
	* Divides each component of this color by @param right.
	*/
	constexpr void operator/=(const float right) {
		r /= right;
		g /= right;
		b /= right;
		a /= right;
	}

	/**
	* @return a String reprenstation of the color "(r, g, b , a)"
	*/
	[[nodiscard]] inline operator String() const {
		return vformat("(R: {}, G: {}, B: {}, A: {})", r, g, b, a);
	}

	/**
	* @return an SDL_Color with the same r, b, g, and a value as this color.
	*/
	[[nodiscard]] inline SDL_Color to_sdl_color() const {
		SDL_Color color;
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
		return color;
	}

	/**
	* @return the same value as if the + was not there.
	* Unary + does nothing, but sometimes it can make your code more readable.
	*/
	constexpr Color operator+() const {
		return Color(+r, +g, +b, +a);
	}

	/**
	* @return the inverted value of this color.
	* This is equivalent to Color(255, 255, 255, 255) - c or Color(255 - c.r, 255 - c.g, 255 - c.b, 255 - c.a).
	*/
	constexpr Color operator-() const {
		return Color(255 - r, 255 - g, 255 - b, 255 - a);
	}

	/**
	* @return the color components using their index.
	* [0] is equivalent to r, [1] is equivalent to g, [2] is equivalent to b, and [3] is equivalent to a.
	* @note return value is undefined if @param index is not between 0 and 3. 
	*/
	constexpr T operator[](const int index) const {
		switch (index) {
			case 0:
				return r;
			case 1:
				return g;
			case 2:
				return b;
			case 3:
				return a;
		}

		return 0;
	}

	constexpr static Color BLACK() {
		return Color(0, 0, 0, 255);
	}

	constexpr static Color WHITE() {
		return Color(255, 255, 255, 255);
	}

	constexpr static Color TRANSPARENT() {
		return Color(0, 0, 0, 0);
	}

	constexpr static Color RED() {
		return Color(255, 0, 0, 255);
	}

	constexpr static Color GREEN() {
		return Color(0, 255, 0, 255);
	}

	constexpr static Color BLUE() {
		return Color(0, 0, 255, 255);
	}

	template<class Archive>
	inline void serialize(Archive &archive) {
		archive(cereal::make_nvp("Unused", static_cast<uint64_t>(sizeof(value_type))));
		archive(cereal::make_nvp("Red", r));
		archive(cereal::make_nvp("Green", g));
		archive(cereal::make_nvp("Blue", b));
		archive(cereal::make_nvp("Alpha", a));
	}
};

/*
* A color represented in RGBA format in the range of 0 to 255 using a unsigned 8 bit number.
*/
typedef Color<uint8_t> Color8;

/*
* A color represented in RGBA format in the range of 0 to 255 using a unsigned 16 bit number.
*/
typedef Color<uint16_t> Color16;

/*
* A colour represented in RGBA format in the range of 0 to 255 using a unsigned 8 bit number.
*/
typedef Color<uint8_t> Colour8;

/*
* A colour represented in RGBA format in the range of 0 to 255 using a unsigned 16 bit number.
*/
typedef Color<uint16_t> Colour16;

/*
* A color represented in RGBA format in the range of 0 to 255 using a number defined by the build settings.
*/
typedef Color<__COLOR_V_TYPE__> ColorV;

/*
* A colour represented in RGBA format in the range of 0 to 255 using a number defined by the build settings.
*/
typedef Color<__COLOR_V_TYPE__> ColourV;

}
