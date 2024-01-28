#pragma once

#include <core/math/math_defs.hpp>

namespace sdl {

class Resource {

protected:
	virtual uid _get_uid() const;

public:
	uid get_uid() const;

};

}