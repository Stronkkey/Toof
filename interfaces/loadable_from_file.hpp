#pragma once

#include <core/string/string_def.hpp>

namespace sdl {

class ILoadableFromFile {
public:
	virtual void load_from_path(const String &string) = 0;
};

}