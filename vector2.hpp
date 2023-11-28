#include "math_defs.hpp"

namespace sdl {

struct Vector2i;

struct Vector2 {
  real_t x;
  real_t y;

  Vector2();
  Vector2(real_t new_x, real_t new_y);
  Vector2(const Vector2 &vector2);
  Vector2(const Vector2i &vector2i);

  bool operator==(const Vector2 &right) const;
  bool operator==(const Vector2i &right) const;

  static const Vector2 ONE;
  static const Vector2 ZERO;
};

struct Vector2i {
  int_t x;
  int_t y;

  Vector2i();
  Vector2i(const int_t new_x, const int_t new_y);
  Vector2i(const Vector2 &vector2);
  Vector2i(const Vector2i &vector2i);

  bool operator==(const Vector2i &right) const;
  bool operator==(const Vector2 &right) const;

  static const Vector2i ONE;
  static const Vector2i ZERO;
};
}
