#include <core/math/transform2d.hpp>
#include <core/math/rect2.hpp>

#include <algorithm>

using namespace sdl;

const Rect2 Rect2::EMPTY = Rect2();
const Rect2i Rect2i::EMPTY = Rect2i();


Rect2 Rect2::operator*(const Transform2D &right) const {
	Rect2 rect = *this;
	rect *= right;
	return rect;
}

void Rect2::operator*=(const Transform2D &right) {
	x += right.origin.x;
	y += right.origin.y;
	w *= right.scale.x;
	h *= right.scale.y;
}

std::string Rect2::to_string() const {
	return "(" + get_position().to_string() + ", " + get_size().to_string() + ")";
}

Rect2 Rect2::abs() const {
	Rect2 rect = Rect2{};

	rect.x = std::abs(rect.x);
	rect.y = std::abs(rect.y);
	rect.w = std::abs(rect.w);
	rect.h = std::abs(rect.h);

	return rect;
}

SDL_Rect Rect2::to_sdl_rect() const {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return rect;
}

SDL_FRect Rect2::to_sdl_frect() const {
	SDL_FRect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return rect;
}

SDL_Rect Rect2::to_sdl_rect(const Rect2 &rect2) {
	SDL_Rect rect;
	rect.x = rect2.x;
	rect.y = rect2.y;
	rect.w = rect2.w;
	rect.h = rect2.h;
	return rect;
}

SDL_FRect Rect2::to_sdl_frect(const Rect2 &rect2) {
	SDL_FRect rect;
	rect.x = rect2.x;
	rect.y = rect2.y;
	rect.w = rect2.w;
	rect.h = rect2.h;
	return rect;
}


std::string Rect2i::to_string() const {
	return "(" + get_position().to_string() + ", " + get_size().to_string() + ")";
}

Rect2i Rect2i::abs() const {
	Rect2i rect = Rect2i{};

	rect.x = std::abs(rect.x);
	rect.y = std::abs(rect.y);
	rect.w = std::abs(rect.w);
	rect.h = std::abs(rect.h);

	return rect;
}


SDL_Rect Rect2i::to_sdl_rect() const {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return rect;
}

SDL_FRect Rect2i::to_sdl_frect() const {
	SDL_FRect frect;
	frect.x = x;
	frect.y = y;
	frect.w = w;
	frect.h = h;
	return frect;
}

SDL_Rect Rect2i::to_sdl_rect(const Rect2i &rect2i) {
	SDL_Rect rect;
	rect.x = rect2i.x;
	rect.y = rect2i.y;
	rect.w = rect2i.w;
	rect.h = rect2i.h;
	return rect;
}

SDL_FRect Rect2i::to_sdl_frect(const Rect2i &rect2i) {
	SDL_FRect frect;
	frect.x = rect2i.x;
	frect.y = rect2i.y;
	frect.w = rect2i.w;
	frect.h = rect2i.h;
	return frect;
}
