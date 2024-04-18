#pragma once

#include <core/math/math_funcs.hpp>
#include <core/string/string_def.hpp>

namespace sdl {

class Angle {
public:
	using value_type = real;
private:
	value_type angle_degrees;

	explicit constexpr Angle(const value_type angle_degrees): angle_degrees(angle_degrees) {
	}
public:
	constexpr Angle(): angle_degrees(0.0) {
	}

	constexpr Angle(const Angle &angle): angle_degrees(angle.angle_degrees) {
	}

	~Angle() = default;

	constexpr void set_angle_degrees(const value_type angle_degrees) {
		this->angle_degrees = angle_degrees;
	}

	constexpr void set_angle_radians(const value_type angle_radians) {
		this->angle_degrees = Math::radians_to_degrees(angle_radians);
	}

	constexpr value_type get_angle_degrees() const {
		return angle_degrees;
	}

	constexpr value_type get_angle_radians() const {
		return Math::degrees_to_radians(angle_degrees);
	}

	constexpr bool is_zero_angle() const {
		return angle_degrees == 0.0;
	}

	constexpr void operator=(const Angle &right) {
		angle_degrees = right.angle_degrees;
	}

	constexpr bool operator==(const Angle &right) const {
		return angle_degrees == right.angle_degrees;
	}

	constexpr bool operator!=(const Angle &right) const {
		return angle_degrees != right.angle_degrees;
	}

	constexpr Angle operator+(const Angle &right) const {
		return Angle(angle_degrees + right.angle_degrees);
	}

	constexpr Angle operator+() const {
		return Angle(+angle_degrees);
	}

	constexpr void operator+=(const Angle &right) {
		angle_degrees += right.angle_degrees;
	}

	constexpr Angle operator-(const Angle &right) const {
		return Angle(angle_degrees - right.angle_degrees);
	}

	constexpr Angle operator-() const {
		return Angle(-angle_degrees);
	}

	constexpr void operator-=(const Angle &right) {
		angle_degrees -= right.angle_degrees;
	}

	constexpr Angle operator*(const Angle &right) const {
		return Angle(angle_degrees * right.angle_degrees);
	}

	constexpr void operator*=(const Angle &right) {
		angle_degrees *= right.angle_degrees;
	}

	constexpr Angle operator/(const Angle &right) const {
		return Angle(angle_degrees / right.angle_degrees);
	}

	constexpr void operator/=(const Angle &right) {
		angle_degrees /= right.angle_degrees;
	}
	
	static constexpr Angle from_degrees(const value_type angle_degrees) {
		return Angle(angle_degrees);
	}

	static constexpr Angle from_radians(const value_type angle_radians) {
		return Angle(Math::radians_to_degrees(angle_radians));
	}

	[[nodiscard]] operator String() const;

	/**
	* A constant expression equivalent to an Angle with a rotation of 0 degrees.
	*/
	static constexpr Angle ZERO_ROTATION() {
		return Angle(0.0);
	}

	/**
	* A constant expression equivalent to an Angle with a rotation of 90 degrees.
	*/
	static constexpr Angle QUARTER_PAST_ROTATION() {
		return Angle(90.0);
	}

	/**
	* A constant expression equivalent to an Angle with a rotation of 180 degrees.
	*/
	static constexpr Angle HALF_ROTATION() {
		return Angle(180.0);
	}

	/**
	* A constant expression equivalent to an Angle with a rotation of 270 degrees.
	*/
	static constexpr Angle QUARTER_TO_ROTATION() {
		return Angle(270.0);
	}

	/**
	* A constant expression equivalent to an Angle with a rotation of 360 degrees.
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

}