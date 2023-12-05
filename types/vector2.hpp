#ifndef VECTOR2
#define VECTOR2

#include <types/math_defs.hpp>

#include <string>

namespace sdl {

struct Vector2i;

struct Vector2 {
  real_t x;
  real_t y;

  Vector2();
  Vector2(const real_t new_x, const real_t new_y);
  Vector2(const Vector2 &vector2);
  Vector2(const Vector2i &vector2i);

  void operator=(const Vector2 &right);
  bool operator==(const Vector2 &right) const;
  bool operator!=(const Vector2 &right) const;
  
  bool operator<(const Vector2 &right) const;
  bool operator<=(const Vector2 &right) const;
  bool operator>(const Vector2 &right) const;
  bool operator>=(const Vector2 &right) const;

  Vector2 operator+(const Vector2 &right) const;
  Vector2 operator-(const Vector2 &right) const;

  Vector2 operator*(const Vector2 &right) const;
  Vector2 operator*(const real_t right) const;
  Vector2 operator*(const int_t right) const;

  Vector2 operator/(const Vector2 &right) const;
  Vector2 operator/(const real_t right) const;
  Vector2 operator/(const int_t right) const;

  void operator+=(const Vector2 &right);
  void operator-=(const Vector2 &right);

  void operator*=(const Vector2 &right);
  void operator*=(const real_t right);
  void operator*=(const int_t right);

  void operator/=(const Vector2 &right);
  void operator/=(const real_t right);
  void operator/=(const int_t right);

  real_t operator[](const int_t index) const;
  Vector2 operator-() const;
  Vector2 operator+() const;

  std::string to_string() const;

  static const Vector2 ONE;
  static const Vector2 ZERO;
  static const Vector2 LEFT;
  static const Vector2 RIGHT;
  static const Vector2 UP;
  static const Vector2 DOWN;
};

struct Vector2i {
  int_t x;
  int_t y;

  Vector2i();
  Vector2i(const int_t new_x, const int_t new_y);
  Vector2i(const Vector2 &vector2);
  Vector2i(const Vector2i &vector2i);

  void operator=(const Vector2i &right);
  bool operator==(const Vector2i &right) const;
  bool operator!=(const Vector2i &right) const;
  
  bool operator<(const Vector2i &right) const;
  bool operator<=(const Vector2i &right) const;
  bool operator>(const Vector2i &right) const;
  bool operator>=(const Vector2i &right) const;

  Vector2i operator+(const Vector2i &right) const;
  Vector2i operator-(const Vector2i &right) const;

  Vector2i operator*(const Vector2i &right) const;
  Vector2i operator*(const real_t right) const;
  Vector2i operator*(const int_t right) const;

  Vector2i operator/(const Vector2 &right) const;
  Vector2i operator/(const real_t right) const;
  Vector2i operator/(const int_t right) const;

  void operator+=(const Vector2i &right);
  void operator-=(const Vector2i &right);

  void operator*=(const Vector2i &right);
  void operator*=(const real_t right);
  void operator*=(const int_t right);

  void operator/=(const Vector2i &right);
  void operator/=(const real_t right);
  void operator/=(const int_t right);

  int_t operator[](const int_t index) const;
  Vector2i operator-() const;
  Vector2i operator+() const;
  
  std::string to_string() const;

  static const Vector2i ONE;
  static const Vector2i ZERO;
  static const Vector2i LEFT;
  static const Vector2i RIGHT;
  static const Vector2i UP;
  static const Vector2i DOWN;
};
}

#endif // !VECTOR2
