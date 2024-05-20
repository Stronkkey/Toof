#ifdef B2_INCLUDED

#pragma once

#include <scene/resources/resource.hpp>

namespace Toof {

class World2D : public Resource {
private:
	uid space;

public:
	constexpr void set_space(const uid new_space) {
		space = new_space;
	}
	constexpr uid get_space() const {
		return space;
	}
};

}

#endif