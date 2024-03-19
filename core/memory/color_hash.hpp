#pragma once

#include <core/math/color.hpp>

#include <functional>

template<class T>
struct std::hash<sdl::Color<T>> {
	size_t operator()(const sdl::Color<T> &color) const noexcept {
		const size_t r_hash = std::hash<T>()(color.r);
		const size_t g_hash = std::hash<T>()(color.g);
		const size_t b_hash = std::hash<T>()(color.b);
		const size_t a_hash = std::hash<T>()(color.a);
		return ((r_hash ^ (g_hash << 1)) ^ (b_hash << 1)) ^ (a_hash << 1);
	}
};