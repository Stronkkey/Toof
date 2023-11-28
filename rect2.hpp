#ifndef RECT2_LIB
#define RECT2_LIB

#include "vector2.hpp"

#include <SDL_rect.h>

namespace sdl {

struct Rect2i;

struct Rect2 {
  real_t x;
  real_t y;
  real_t w;
  real_t h;

  Rect2();
  Rect2(const Vector2 &position, const Vector2 &size);
  Rect2(real_t position_x, real_t position_y, real_t size_x, real_t size_y);
  Rect2(const SDL_Rect &rect);

  bool operator==(const Rect2 &right) const;
  Rect2 operator+(const Rect2 &right) const;
  Rect2 operator-(const Rect2 &right) const;
  void operator+=(const Rect2 &right);
  void operator-=(const Rect2 &right);

  Vector2 get_position() const;
  Vector2 get_size() const;

  SDL_Rect to_sdl_rect() const;

  static const Rect2 EMPTY;
  static SDL_Rect to_sdl_rect(const Rect2 &rect2);
};

struct Rect2i {
  int_t x;
  int_t y;
  int_t w;
  int_t h;

  Rect2i();
  Rect2i(const Vector2i &position, const Vector2i &size);
  Rect2i(int_t x, int_t y, int_t w, int_t h);
  Rect2i(const SDL_Rect &rect);

  bool operator==(const Rect2i &right) const;
  Rect2i operator+(const Rect2i &right) const;
  Rect2i operator-(const Rect2i &right) const;
  void operator+=(const Rect2i &right);
  void operator-=(const Rect2i &right);

  Vector2i get_position() const;
  Vector2i get_size() const;

  SDL_Rect to_sdl_rect() const;

  static const Rect2i EMPTY;
  static SDL_Rect to_sdl_rect(const Rect2i &rect2i);
};

}

#endif // !RECT2_LIB
