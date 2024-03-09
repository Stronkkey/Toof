#include <core/math/color.hpp>
#include <core/string_funcs.hpp>

using namespace sdl;

const Color Color::BLACK = Color(0, 0, 0, 255);
const Color Color::WHITE = Color(255, 255, 255, 255);
const Color Color::TRANSPARENT = Color(0, 0, 0, 0);
const Color Color::RED = Color(255, 0, 0, 255);
const Color Color::GREEN = Color(0, 255, 0, 255);
const Color Color::BLUE = Color(0, 0, 255, 255);

Color Color::blend(const Color &over) const {
	Color blended_color;
	uint16_t inverted_alpha = 255 - over.a;
	blended_color.a = ceil((a / 255.0 * inverted_alpha / 255.0 + over.a / 255.0) * 255.0);

	if (blended_color.a == 0)
		return Color(0, 0, 0, 0);

	blended_color.r = ceil((r / 255.0 * a / 255.0 * inverted_alpha / 255.0 + over.r / 255.0 * over.a / 255.0 / blended_color.a / 255) * 255.0);
	blended_color.g = ceil((g / 255.0 * a / 255.0 * inverted_alpha / 255.0 + over.g / 255.0 * over.a / 255.0 / blended_color.a / 255) * 255.0);
	blended_color.b = ceil((b / 255.0 * a / 255.0 * inverted_alpha / 255.0 + over.b / 255.0 * over.a / 255.0 / blended_color.a / 255) * 255.0);

	return blended_color;
}

SDL_Color Color::to_sdl_color() const {
	SDL_Color color;
	color.a = a;
	color.r = r;
	color.b = b;
	color.g = g;
	return color;
}
