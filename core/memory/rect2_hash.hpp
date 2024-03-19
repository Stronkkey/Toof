#pragma once

#include <core/math/rect2.hpp>

#include <functional>

template<class T>
struct std::hash<sdl::Rect2<T>> {
	size_t operator()(const sdl::Rect2<T> &rect2) const noexcept {
		const size_t x_hash = std::hash<T>()(rect2.x);
		const size_t y_hash = std::hash<T>()(rect2.y);
		const size_t w_hash = std::hash<T>()(rect2.w);
		const size_t h_hash = std::hash<T>()(rect2.h);
		return (x_hash ^ (y_hash << 1)) ^ (w_hash ^ (h_hash << 1));
	}
};