#include <core/math/vector2.hpp>

#ifdef B2_INCLUDED
#include <box2d/b2_math.h>
#endif

using namespace sdl;

const Vector2 Vector2::ONE = Vector2(1, 1);
const Vector2 Vector2::ZERO = Vector2(0, 0);
const Vector2 Vector2::LEFT = Vector2(-1, 0);
const Vector2 Vector2::RIGHT = Vector2(1, 0);
const Vector2 Vector2::DOWN = Vector2(0, 1);
const Vector2 Vector2::UP = Vector2(0, -1);

const Vector2i Vector2i::ONE = Vector2i(1, 1);
const Vector2i Vector2i::ZERO = Vector2i(0, 0);
const Vector2i Vector2i::LEFT = Vector2i(-1, 0);
const Vector2i Vector2i::RIGHT = Vector2i(1, 0);
const Vector2i Vector2i::DOWN = Vector2i(0, 1);
const Vector2i Vector2i::UP = Vector2i(0, -1);

std::string Vector2::to_string() const {
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

#ifdef B2_INCLUDED
Vector2::Vector2(const b2Vec2 &b2_vec2): x(b2_vec2.x), y(b2_vec2.y) {
}

b2Vec2 Vector2::to_b2_vec2() const {
	return b2Vec2((float)x, (float)y);
}
#endif

SDL_FPoint Vector2::to_sdl_fpoint() const {
	SDL_FPoint fpoint;
	fpoint.x = x;
	fpoint.y = y;
	return fpoint;
}

SDL_Point Vector2::to_sdl_point() const {
	SDL_Point point;
	point.x = x;
	point.y = y;
	return point;
}

std::string Vector2i::to_string() const {
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

SDL_FPoint Vector2i::to_sdl_fpoint() const {
	SDL_FPoint fpoint;
	fpoint.x = x;
	fpoint.y = y;
	return fpoint;
}

SDL_Point Vector2i::to_sdl_point() const {
	SDL_Point point;
	point.x = x;
	point.y = y;
	return point;
}
