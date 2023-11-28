#include "vector2.hpp"

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

  bool operator==(const Rect2 &right) const;
  bool operator==(const Rect2i &right) const;

  Vector2 get_position() const;
  Vector2 get_size() const;

  static const Rect2 EMPTY;
};

struct Rect2i {
  int_t x;
  int_t y;
  int_t w;
  int_t h;

  Rect2i();
  Rect2i(const Vector2i &position, const Vector2i &size);
  Rect2i(int_t x, int_t y, int_t w, int_t h);

  bool operator==(const Rect2 &right) const;
  bool operator==(const Rect2i &right) const;

  Vector2i get_position() const;
  Vector2i get_size() const;

  static const Rect2i EMPTY;
};

}
