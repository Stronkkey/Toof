#include <core/math/color.hpp>

using namespace sdl;

const Color Color::BLACK = Color(0, 0, 0, 255);
const Color Color::WHITE = Color(255, 255, 255, 255);
const Color Color::TRANSPARENT = Color(0, 0, 0, 0);
const Color Color::RED = Color(255, 0, 0, 255);
const Color Color::GREEN = Color(0, 255, 0, 255);
const Color Color::BLUE = Color(0, 0, 255, 255);

SDL_Color Color::to_sdl_color() const {
	SDL_Color color;
	color.a = a;
	color.r = r;
	color.b = b;
	color.g = g;
	return color;
}

std::string Color::to_string() const {
	return "(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ", " + std::to_string(a) + ")";
}
