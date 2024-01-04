#pragma once

#include <core/math/vector2.hpp>

#include <SDL_render.h>

namespace sdl {

struct Texture {
	SDL_Texture *texture_reference;
	Vector2i size;
	uint32_t format;
};

}