#include "math_defs.hpp"

namespace sdl {

class Vector2 {
public:
  real_t x;
  real_t y;

  Vector2();
  Vector2(real_t new_x, real_t new_y);

};

class Vector2i {

public:
  int_t x;
  int_t y;

  Vector2i();
  Vector2i(int_t new_x, int_t new_y);

};
}
