#ifdef B2_INCLUDED

#pragma once

#include <scene/resources/resource.hpp>

namespace sdl {

class World2D : public Resource {
private:
	uid space;

public:
	constexpr void set_space(const uid new_space);
	constexpr uid get_space() const;
};

constexpr void World2D::set_space(const uid new_space) {
	space = new_space;
}

constexpr uid World2D::get_space() const {
	return space;
}

}

#endif