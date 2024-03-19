#pragma once

#include <core/math/angle.hpp>

#include <functional>

template<>
struct std::hash<sdl::Angle> {
	size_t operator()(const sdl::Angle &angle) const noexcept {
		return std::hash<sdl::real>()(angle.get_angle_degrees());
	}
};