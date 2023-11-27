#include "vector2.hpp"

using namespace sdl;

Vector2::Vector2(real_t new_x, real_t new_y) {
  x = new_x;
  y = new_y;
}

Vector2::Vector2() {
  x = 0.0;
  y = 0.0;
}

Vector2i::Vector2i(int_t new_x, int_t new_y) {
  x = new_x;
  y = new_y;
}

Vector2i::Vector2i() {
  x = 0;
  y = 0;
}
