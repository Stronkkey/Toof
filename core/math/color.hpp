/*  This file is part of the Toof Engine. */
/** @file color.hpp */
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

#include <core/string/string_def.hpp>
#include <core/math/math_defs.hpp>

#include <cereal/cereal.hpp>
#include <stringify/format.hpp>

#include <SDL_pixels.h>

#ifndef __COLOR_V_TYPE__
#define __COLOR_V_TYPE__ uint8_t
#endif

namespace Toof {

/**
* @brief A color represented in RGBA format in the range of 0 to 255 using a generic T.
*/
template<class T>
struct Color {
	using value_type = T;

	static_assert(std::is_arithmetic<value_type>::value, "value_type of Color must be an arithmetic type.");

	/**
	* @brief Constructs a default Color from opaque black.
	*/
	constexpr Color(): r(0), g(0), b(0), a(255) {
	}

	/**
	* @brief Constructs a Color from param from_color, with a set to the given alpha value.
	*/
	constexpr Color(const Color &from_color, const T alpha): r(from_color.r), g(from_color.g), b(from_color.b), a(alpha) {
	}

	/**
	* @brief Constructs a Color as a copy of the given Color.
	*/
	constexpr Color(const Color &from_color): r(from_color.r), g(from_color.g), b(from_color.b), a(from_color.a) {
	}

	/**
	* @brief Constructs a Color from RGB values, typically between 0 and 255. a is set to 255.
	*/
	constexpr Color(const T red, const T green, const T blue): r(red), g(green), b(blue), a(255) {
	}

	/**
	* @brief Constructs a Color from RGBA values, typically between 0 and 255.
	*/
	constexpr Color(const T red, const T green, const T blue, const T alpha): r(red), g(green), b(blue), a(alpha) {
	}

	/**
	* @brief The color's red component, typically on the range of 0 to 255.
	*/
	T r;

	/**
	* @brief The color's green component, typically on the range of 0 to 255.
	*/
	T g;

	/**
	* @brief The color's blue component, typically on the range of 0 to 255.
	*/
	T b;
	
	/**
	* @brief The color's alpha component, typically on the range of 0 to 255. A value of 0 means that the color is fully transparent. A value of 255 means that the color is fully opaque.
	*/
	T a;

	/**
	* @brief Returns a new color resulting from overlaying this over the given color.
	* @details In a painting program, you can imagine it as the over color painted over this color (including alpha).
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
	* @brief Returns a new color resulting from making this color darker by the specified amount (ratio from 0 to 255).
	*/
	[[nodiscard]] constexpr Color darkened(const float amount) const {
		return Color(r * (255 - -amount), g * (255 - -amount), b * (255 - -amount), a * (255 - -amount));
	}

	/**
	* @brief Sets the r, g, b, and a to that of @b right.
	*/
	constexpr void operator=(const Color &right) {
		r = right.r;
		g = right.g;
		b = right.b;
		a = right.a;
	}

	/**
	* @brief Returns @b true if this color and the color given are not exactly equal.
	* @note due to floating-point precision errors, consider using @b Math::is_equal_approx instead, which is more reliable.
	*/
	constexpr bool operator!=(const Color &right) const {
		return r != right.r || g != right.g || b != right.b || a != right.a;
	}

	/**
	* @brief Returns @b true if this color and the color given are exactly equal.
	* @note due to floating-point precision errors, consider using Math::is_equal_approx instead, which is more reliable.
	*/
	constexpr bool operator==(const Color &right) const {
		return r == right.r && g == right.g && b == right.b && a == right.a;
	}
	
	/**
	* @brief Returns this color with its components multiplied by each component of the given color.
	*/
	constexpr Color operator*(const Color &right) const {
		return Color(r * (right.r / 255), g * (right.g / 255), b * (right.b / 255), a * (right.a / 255));
	}

	/**
	* @brief Returns this color with its components multiplied by the given amount.
	*/
	constexpr Color operator*(const float right) const {
		return Color(r * right, g * right, b * right, a * right);
	}

	/**
	* @brief Modulates this color with the given color.
	*/
	constexpr void operator*=(const Color &right) {
		r *= (right.r / 255);
		g *= (right.g / 255);
		b *= (right.b / 255),
		a *= (right.a / 255);
	}

	/**
	* @brief Multiplies each component of this color with the given amount.
	*/
	constexpr void operator*=(const float right) {
		r *= right;
		g *= right;
		b *= right;
		a *= right;
	}

	/**
	* @brief Returns this color with its components added by each component of the given color.
	*/
	constexpr Color operator+(const Color &right) const {
		return Color(r + right.r, g + right.g, b + right.b, a + right.a);
	}

	/**
	* @brief Returns this color with its components subtracted by each component of the given color.
	*/
	constexpr Color operator-(const Color &right) const {
		return Color(r - right.r, g - right.g, b - right.b, a - right.a);
	}
	
	/**
	* @brief Adds each component of this color by the components of the given color.
	*/
	constexpr void operator+=(const Color &right) {
		r += right.r;
		g += right.g;
		b += right.b;
		a += right.a;
	}
	
	/**
	* @brief Subtracts each component of this color by the components of the given color.
	*/
	constexpr void operator-=(const Color &right) {
		r -= right.r;
		g -= right.g;
		b -= right.b;
		a -= right.a;
	}

	/**
	* @brief Returns this color with its components divided by each component by the given color
	*/
	constexpr Color operator/(const Color &right) const {
		return Color(r / right.r, g / right.g, b / right.b, a / right.a);
	}

	/**
	* @brief Returns this color with its components divided by the given amount. 
	*/
	constexpr Color operator/(const float right) const {
		return Color(r / right, g / right, b / right, a / right);
	}

	/**
	* @brief Divides each component of this color by the components of the given color.
	*/
	constexpr void operator/=(const Color &right) {
		r /= right.r;
		g /= right.g;
		b /= right.b;
		a /= right.a;
	}

	/**
	* @brief Divides each component of this color by the given amount.
	*/
	constexpr void operator/=(const float right) {
		r /= right;
		g /= right;
		b /= right;
		a /= right;
	}

	/**
	* @brief Inserts the color into the stream.
	*/
	template<class CharT, class Traits>
	friend std::basic_ostream<CharT, Traits> &operator<<(std::basic_ostream<CharT, Traits> &stream, const Color &color) {
		S_STREAM_FORMAT(stream, "(R: {}, G: {}, B: {}, A: {})", color);
		return stream;
	}

	/**
	* @brief Creates a string representation of this color.
	*/
	[[nodiscard]] inline operator String() const {
		return S_FORMAT("(R: {}, G: {}, B: {}, A: {})", r, g, b, a);
	}

	/**
	* @brief Creates an SDL_Color structure and sets the @b r, @b b, @b g, and @b a properties to those of this color.
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
	* @brief Unary + does nothing, but sometimes it can make your code more readable.
	*/
	constexpr Color operator+() const {
		return Color(+r, +g, +b, +a);
	}

	/**
	* @brief Returns the inverted value of this color.
	* @brief This is equivalent to Color(255, 255, 255, 255) - c or Color(255 - c.r, 255 - c.g, 255 - c.b, 255 - c.a).
	*/
	constexpr Color operator-() const {
		return Color(255 - r, 255 - g, 255 - b, 255 - a);
	}

	/**
	* @brief Returns the color components using their index.
	* @details [0] is equivalent to @b r, [1] is equivalent to @b g, [2] is equivalent to @b b, and [3] is equivalent to @b a.
	* @note The return value is 0 if the index is not between 0 to 3. 
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

/**
* @brief A color represented in RGBA format in the range of 0 to 255 using a unsigned 8 bit number.
*/
typedef Color<uint8_t> Color8;

/**
* @brief A color represented in RGBA format in the range of 0 to 255 using a unsigned 16 bit number.
*/
typedef Color<uint16_t> Color16;

/**
* @brief A colour represented in RGBA format in the range of 0 to 255 using a unsigned 8 bit number.
*/
typedef Color<uint8_t> Colour8;

/**
* @brief A colour represented in RGBA format in the range of 0 to 255 using a unsigned 16 bit number.
*/
typedef Color<uint16_t> Colour16;

/**
* @brief A color represented in RGBA format in the range of 0 to 255 using a number defined by the build settings.
*/
typedef Color<__COLOR_V_TYPE__> ColorV;

/**
* @brief A colour represented in RGBA format in the range of 0 to 255 using a number defined by the build settings.
*/
typedef Color<__COLOR_V_TYPE__> ColourV;

}
