#pragma once

#include <core/math/math_defs.hpp>
#include <core/string_def.hpp>

namespace sdl {

class Angle {
private:
	real angle_degrees;

	explicit constexpr Angle(const real angle_degrees): angle_degrees(angle_degrees) {
	}
public:
	constexpr Angle(): angle_degrees(0.0) {
	}

	constexpr Angle(const Angle &angle): angle_degrees(angle.angle_degrees) {
	}

	constexpr void set_angle_degrees(const real angle_degrees) {
		this->angle_degrees = angle_degrees;
	}

	constexpr void set_angle_radians(const real angle_radians) {
		this->angle_degrees = Math::radians_to_degrees(angle_radians);
	}

	constexpr real get_angle_degrees() const {
		return angle_degrees;
	}

	constexpr real get_angle_radians() const {
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
	
	static constexpr Angle from_degrees(const real angle_degrees) {
		return Angle(angle_degrees);
	}

	static constexpr Angle from_radians(const real angle_radians) {
		return Angle(Math::radians_to_degrees(angle_radians));
	}

	[[nodiscard]] operator String() const;
};

}