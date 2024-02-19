#pragma once

#include <core/math/math_defs.hpp>

namespace sdl {

class Angle {
private:
	real_t angle_degrees;
public:
	constexpr Angle(): angle_degrees(0.0) {
	}

	constexpr void set_angle_degrees(const real_t angle_degrees) {
		this->angle_degrees = angle_degrees;
	}

	constexpr void set_angle_radians(const real_t angle_radians) {
		this->angle_degrees = Math::radians_to_degrees(angle_radians);
	}

	constexpr real_t get_angle_degrees() const {
		return Math::radians_to_degrees(angle_degrees);
	}

	constexpr real_t get_angle_radians() const {
		return Math::degrees_to_radians(angle_degrees);
	}
};

}