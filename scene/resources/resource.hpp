#pragma once

#include <core/math/math_defs.hpp>

#include <array>

namespace sdl {

class Resource {
protected:
	virtual uid _get_uid() const;
public:
	Resource() = default;
	~Resource() = default;

	uid get_uid() const;
};

}
