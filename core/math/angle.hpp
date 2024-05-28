/*  This file is part of the Toof Engine. */
/** @file angle.hpp */
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

#ifdef TOOF_PHYSICS_ENABLED
#include <box2d/b2_math.h>
#endif

#include <core/math/math_funcs.hpp>
#include <core/string/string_def.hpp>

#include <cereal/cereal.hpp>

namespace Toof {

/**
* @brief A class representing an angle.
* @details Angle is primarily designed as a substitute for arithmetic types that represent an Angle.
*
* There is no direct constructor for Angle, instead, you can use @b Angle::from_degrees or @b Angle::from_radians to construct an Angle.
*/
class Angle {
public:
	using value_type = real;
private:
	value_type angle_degrees;

	explicit constexpr Angle(const value_type angle_degrees): angle_degrees(angle_degrees) {
	}
public:
	/**
	* @brief Constructs an Angle with no rotation.
	*/
	constexpr Angle(): angle_degrees(0.0) {
	}

	/**
	* @brief Constructs an Angle from the given Angle.
	*/
	constexpr Angle(const Angle &angle): angle_degrees(angle.angle_degrees) {
	}

	~Angle() = default;

	/**
	* @brief Sets the rotation of this Angle.
	* @param angle_degrees the rotation in degrees.
	*/
	constexpr void set_angle_degrees(const value_type angle_degrees) {
		this->angle_degrees = angle_degrees;
	}

	/**
	* @brief Sets the rotation of this Angle.
	* @param angle_radians the rotation in radians.
	*/
	constexpr void set_angle_radians(const value_type angle_radians) {
		this->angle_degrees = Math::radians_to_degrees(angle_radians);
	}

	/**
	* @returns The rotation of this Angle in degrees.
	*/
	constexpr value_type get_angle_degrees() const {
		return angle_degrees;
	}

	/**
	* @returns The rotation of this Angle in radians.
	*/
	constexpr value_type get_angle_radians() const {
		return Math::degrees_to_radians(angle_degrees);
	}

	/**
	* @returns @b true if the rotation of this Angle (in degrees) is exactly equal to 0.
	*/
	constexpr bool is_zero_angle() const {
		return angle_degrees == 0.0;
	}

	/**
	* @brief Sets the rotation of this Angle to the Angle given.
	*/
	constexpr void operator=(const Angle &right) {
		angle_degrees = right.angle_degrees;
	}

	/**
	* @brief Compares this Angle with the given Angle.
	* @returns @b true if the rotation of this Angle and the given Angle are exactly equal.
	*/
	constexpr bool operator==(const Angle &right) const {
		return angle_degrees == right.angle_degrees;
	}

	/**
	* @brief Compares this Angle with the given Angle.
	* @returns @b true if the rotation of this Angle and the given Angle are not exactly equal.
	*/
	constexpr bool operator!=(const Angle &right) const {
		return angle_degrees != right.angle_degrees;
	}

	/**
	* @brief Adds the rotation of two Angles together.
	* @details This is equivalent to: @code Angle::from_degrees(left.get_angle_degrees() + right.get_angle_degrees()) @endcode
	* @returns This Angle's rotation added with the given Angle's rotation.
	*/
	constexpr Angle operator+(const Angle &right) const {
		return Angle(angle_degrees + right.angle_degrees);
	}

	/**
	* @brief Unary + does nothing, but sometimes it can make your code more readable.
	*/
	constexpr Angle operator+() const {
		return Angle(+angle_degrees);
	}

	/**
	* @brief Adds the rotation of the given Angle to this one.
	*/
	constexpr void operator+=(const Angle &right) {
		angle_degrees += right.angle_degrees;
	}

	/**
	* @brief Subtracts the rotation of this Angle from the Angle given.
	* @details This is equivalent to: @code Angle::from_degrees(left.get_angle_degrees() - right.get_angle_degrees()) @endcode
	* @returns This Angle's rotation subtracted from the given Angle.
	*/
	constexpr Angle operator-(const Angle &right) const {
		return Angle(angle_degrees - right.angle_degrees);
	}

	/**
	* @returns This Angle with the rotation inversed (e.g. a rotation of 56° becomes -56°).
	*/
	constexpr Angle operator-() const {
		return Angle(-angle_degrees);
	}

	/**
	* @brief Subtracts this Angle's rotation from the given Angle.
	*/
	constexpr void operator-=(const Angle &right) {
		angle_degrees -= right.angle_degrees;
	}

	/**
	* @deprecated This function doesn't have many real use cases. It will be removed in a future version.
	*/
	[[deprecated]] constexpr Angle operator*(const Angle &right) const {
		return Angle(angle_degrees * right.angle_degrees);
	}

	/**
	* @deprecated This function doesn't have many real use cases. It will be removed in a future version.
	*/
	[[deprecated]] constexpr void operator*=(const Angle &right) {
		angle_degrees *= right.angle_degrees;
	}

	/**
	* @deprecated This function doesn't have many real use cases. It will be removed in a future version.
	*/
	[[deprecated]] constexpr Angle operator/(const Angle &right) const {
		return Angle(angle_degrees / right.angle_degrees);
	}

	#ifdef TOOF_PHYSICS_ENABLED
	/**
	* @brief Converts the Angle into a b2Rot object.
	*/
	inline operator b2Rot() const {
		return b2Rot(Math::degrees_to_radians(angle_degrees));
	}
	#endif

	/**
	* @deprecated This function doesn't have many real use cases. It will be removed in a future version.
	*/
	[[deprecated]] constexpr void operator/=(const Angle &right) {
		angle_degrees /= right.angle_degrees;
	}
	
	/**
	* @brief Constructs an Angle with the specified rotation.
	* @param angle_degrees the rotation in degrees.
	*/
	static constexpr Angle from_degrees(const value_type angle_degrees) {
		return Angle(angle_degrees);
	}

	/**
	* @brief Constructs an Angle with the specified rotation.
	* @param angle_radians the rotation in radians.
	*/
	static constexpr Angle from_radians(const value_type angle_radians) {
		return Angle(Math::radians_to_degrees(angle_radians));
	}

	/**
	* @brief Creates a string representation of this Angle.
	*/
	[[nodiscard]] operator String() const;

	/**
	* @brief A constant expression equivalent to an Angle with no rotation.
	*/
	static constexpr Angle ZERO_ROTATION() {
		return Angle(0.0);
	}

	/**
	* @brief A constant expression equivalent to an Angle with a rotation of 90 degrees.
	*/
	static constexpr Angle QUARTER_PAST_ROTATION() {
		return Angle(90.0);
	}

	/**
	* @brief A constant expression equivalent to an Angle with a rotation of 180 degrees.
	*/
	static constexpr Angle HALF_ROTATION() {
		return Angle(180.0);
	}

	/**
	* @brief A constant expression equivalent to an Angle with a rotation of 270 degrees.
	*/
	static constexpr Angle QUARTER_TO_ROTATION() {
		return Angle(270.0);
	}

	/**
	* @brief A constant expression equivalent to an Angle with a rotation of 360 degrees.
	*/
	static constexpr Angle FULL_ROTATION() {
		return Angle(360.0);
	}

	template<class Archive>
	real save_minimal(Archive const&) const {
		return angle_degrees;
	}

	template<class Archive>
	void load_minimal(Archive const&, real const& rotation_degrees) {
		angle_degrees = rotation_degrees;
	}
};

/**
* @brief Inserts the angle into the stream.
*/
std::ostream &operator<<(std::ostream &stream, const Angle &angle);

}