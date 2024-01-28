#ifdef B2_INCLUDED

#pragma once

#include <resources/resource.hpp>

namespace sdl {

class World2D : public Resource {
private:
	uid space;
public:
	void set_space(const uid new_space);
	uid get_space() const;
};

}

#endif