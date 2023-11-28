#include "rect2.hpp"

using namespace sdl;

const Rect2 Rect2::EMPTY = Rect2();
const Rect2i Rect2i::EMPTY = Rect2i();

Rect2::Rect2() {
  x = 0.0;
  y = 0.0;
  w = 0.0;
  h = 0.0;
}

Rect2::Rect2(const Vector2 &position, const Vector2 &size) {
  x = position.x;
  y = position.y;
  w = size.x;
  h = size.y;
}

Rect2::Rect2(const real_t position_x, const real_t position_y, const real_t size_x, const real_t size_y) {
  x = position_x;
  y = position_y;
  w = size_x;
  h = size_y;
}

Rect2::Rect2(const SDL_Rect &rect) {
  x = rect.x;
  y = rect.y;
  w = rect.w;
  h = rect.h;
}

bool Rect2::operator==(const Rect2 &right) const {
  return get_position() == right.get_position() && get_size() == right.get_size();
}

bool Rect2::operator==(const Rect2i &right) const {
  return get_position() == right.get_position() && get_size() == right.get_size();
}

Vector2 Rect2::get_position() const {
  return Vector2(x, y);
}

Vector2 Rect2::get_size() const {
  return Vector2(w, h);
}

SDL_Rect Rect2::to_sdl_rect() const {
  SDL_Rect rect;
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


Rect2i::Rect2i() {
  x = 0;
  y = 0;
  w = 0;
  h = 0;
}

Rect2i::Rect2i(const Vector2i &position, const Vector2i &size) {
  x = position.x;
  y = position.y;
  w = size.x;
  h = size.y;
}

Rect2i::Rect2i(const int_t position_x, const int_t position_y, const int_t size_x, const int_t size_y) {
  x = position_x;
  y = position_y;
  w = size_x;
  h = size_y;
}

Rect2i::Rect2i(const SDL_Rect &rect) {
  x = rect.x;
  y = rect.y;
  w = rect.w;
  h = rect.h;
}

bool Rect2i::operator==(const Rect2 &right) const {
  return get_position() == right.get_position() && get_size() == right.get_size();
}

bool Rect2i::operator==(const Rect2i &right) const {
  return get_position() == right.get_position() && get_size() == right.get_size();
}

Vector2i Rect2i::get_position() const {
  return Vector2i(x, y);
}

Vector2i Rect2i::get_size() const {
  return Vector2i(w, h);
}

SDL_Rect Rect2i::to_sdl_rect() const {
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;
  return rect;
}

SDL_Rect Rect2i::to_sdl_rect(const Rect2i &rect2i) {
  SDL_Rect rect;
  rect.x = rect2i.x;
  rect.y = rect2i.y;
  rect.w = rect2i.w;
  rect.h = rect2i.h;
  return rect;
}
