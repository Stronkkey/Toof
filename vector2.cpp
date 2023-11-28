#include "vector2.hpp"

using namespace sdl;

const Vector2 Vector2::ONE = Vector2(1, 1);
const Vector2 Vector2::ZERO = Vector2();
const Vector2i Vector2i::ONE = Vector2i(1, 1);
const Vector2i Vector2i::ZERO = Vector2i();

Vector2::Vector2(const real_t new_x, const real_t new_y) {
  x = new_x;
  y = new_y;
}

Vector2::Vector2() {
  x = 0.0;
  y = 0.0;
}

Vector2::Vector2(const Vector2 &vector2) {
  x = vector2.x;
  y = vector2.y;
}

Vector2::Vector2(const Vector2i &vector2i) {
  x = vector2i.x;
  y = vector2i.y;
}

bool Vector2::operator==(const Vector2 &right) const {
  return x == right.x && y == right.y;
}

bool Vector2::operator==(const Vector2i &right) const {
  return x == right.x && y == right.y;
}

Vector2i::Vector2i(const int_t new_x, const int_t new_y) {
  x = new_x;
  y = new_y;
}

Vector2i::Vector2i() {
  x = 0;
  y = 0;
}

Vector2i::Vector2i(const Vector2 &vector2) {
  x = vector2.x;
  y = vector2.y;
}

Vector2i::Vector2i(const Vector2i &vector2i) {
  x = vector2i.x;
  y = vector2i.y;
}

bool Vector2i::operator==(const Vector2 &right) const {
  return x == right.x && y == right.y;
}

bool Vector2i::operator==(const Vector2i &right) const {
  return x == right.x && y == right.y;
}
