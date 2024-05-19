#pragma once

#include <core/math/transform2d.hpp>

#include <functional>

template<>
struct std::hash<Toof::Transform2D> {
	size_t operator()(const Toof::Transform2D &transform2d) const noexcept {
		const size_t x_hash = std::hash<Toof::real>()(transform2d.origin.x);
		const size_t y_hash = std::hash<Toof::real>()(transform2d.origin.y);
		const size_t w_hash = std::hash<Toof::real>()(transform2d.scale.x);
		const size_t h_hash = std::hash<Toof::real>()(transform2d.scale.y);
		const size_t angle_hash = std::hash<Toof::real>()(transform2d.rotation.get_angle_degrees());
		return angle_hash ^ (((w_hash ^ (h_hash << 1)) ^ ((x_hash ^ (y_hash << 1)) << 1)) << 1);
	}
};