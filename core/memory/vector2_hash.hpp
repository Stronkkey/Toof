#pragma once

#include <core/math/vector2.hpp>

#include <functional>

template<class T>
struct std::hash<Toof::Vector2<T>> {
	size_t operator()(const Toof::Vector2<T> &vector2) const noexcept {
		const size_t x_hash = std::hash<T>()(vector2.x);
		const size_t y_hash = std::hash<T>()(vector2.y);
		return x_hash ^ (y_hash << 1);
	}
};