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
	Color();
	// Constructs a Color from param from_color, with a set to the given alpha value.
	Color(const Color &from_color, const uint16_t alpha);
	// Constructs a Color as a copy of the given Color.
	Color(const Color &from);
	// Constructs a Color from RGB values, typically between 0 and 255. a is set to 1.0.
	Color(const uint16_t red, const uint16_t green, const uint16_t blue);
	// Constructs a Color from RGBA values, typically between 0 and 255.
	Color(const uint16_t red, const uint16_t green, const uint16_t blue, const uint16_t alpha);

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
	[[nodiscard]] Color darkened(const float amount) const;

	/**
	* Sets the r, g, b, and a to that of @param right_color.
	*/
	void operator=(const Color &right_color);

	/**
	* @return true if this color and @param right_color are not exactly equal.
	* @note due to floating-point precision errors, consider using Math::is_equal_approx instead, which is more reliable.
	*/
	bool operator!=(const Color &right_color) const;

	/**
	* @return true if this color and @param right_color are exactly equal.
	* @note due to floating-point precision errors, consider using Math::is_equal_approx instead, which is more reliable.
	*/
	bool operator==(const Color &right_color) const;
	
	/**
	* @returns this color with its components multiplied by each component of the @param right_color
	*/
	Color operator*(const Color &right_color) const;

	/**
	* @returns this color with its components multiplied by @param right
	*/
	Color operator*(const float right) const;

	/**
	* Modulates this color with @param right_color.
	*/
	void operator*=(const Color &right);

	/**
	* Multiplies each component of this color with @param right.
	*/
	void operator*=(const float right);

	/**
	* @returns this color with its components added by each component of the @param right_color
	*/
	Color operator+(const Color &right_color) const;

	/**
	* @returns this color with its components subtracted by each component of the @param right_color
	*/
	Color operator-(const Color &right_color) const;
	
	/**
	* Adds each component of this color by the components of the @param right_color.
	*/
	void operator+=(const Color &right_color);
	
	/**
	* Subtracts each component of this color by the components of the @param right_color.
	*/
	void operator-=(const Color &right_color);

	/**
	* @returns this color with its components divided by each component by the @param right_color
	*/
	Color operator/(const Color &right_color) const;

	/**
	* @returns this color with its components divided by @param right. 
	*/
	Color operator/(const float right) const;

	/**
	* Divides each component of this color by the components of the @param right_color.
	*/
	void operator/=(const Color &right_color);

	/**
	* Divides each component of this color by @param right.
	*/
	void operator/=(const float right);

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
	Color operator+() const;

	/**
	* @return the inverted value of this color.
	* This is equivalent to Color::WHITE - c or Color(1 - c.r, 1 - c.g, 1 - c.b, 1 - c.a).
	*/
	Color operator-() const;

	/**
	* @return the color components using their index.
	* [0] is equivalent to r, [1] is equivalent to g, [2] is equivalent to b, and [3] is equivalent to a.
	*/
	uint16_t operator[](const int index) const;

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

}
