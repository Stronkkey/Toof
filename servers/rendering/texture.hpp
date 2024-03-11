#pragma once

#include <core/math/vector2.hpp>

#include <SDL_render.h>

namespace sdl {

struct __Texture_Ref__ {
	SDL_Texture *texture_reference;
	Vector2i size;
	uint32_t format;
};

}
