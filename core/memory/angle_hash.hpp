#pragma once

#include <core/math/angle.hpp>

#include <functional>

template<>
struct std::hash<Toof::Angle> {
	size_t operator()(const Toof::Angle &angle) const noexcept {
		return std::hash<Toof::real>()(angle.get_angle_degrees());
	}
};