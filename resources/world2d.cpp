#ifdef B2_INCLUDED

#pragma once

#include <resources/world2d.hpp>

void sdl::World2D::set_space(const uid new_space) {
	space = new_space;
}

sdl::uid sdl::World2D::get_space() const {
	return space;
}

#endif