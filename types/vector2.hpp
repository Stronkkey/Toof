#ifndef VECTOR2
#define VECTOR2

#include <cstdint>
#include <string>

namespace sdl {

struct Vector2i;

struct Vector2 {
  double x;
  double y;

  Vector2();
  Vector2(double new_x, double new_y);
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
  Vector2 operator*(const double right) const;
  Vector2 operator*(const int64_t right) const;

  Vector2 operator/(const Vector2 &right) const;
  Vector2 operator/(const double right) const;
  Vector2 operator/(const int64_t right) const;

  void operator+=(const Vector2 &right);
  void operator-=(const Vector2 &right);

  void operator*=(const Vector2 &right);
  void operator*=(const double right);
  void operator*=(const int64_t right);

  void operator/=(const Vector2 &right);
  void operator/=(const double right);
  void operator/=(const int64_t right);

  double operator[](const int64_t index) const;
  Vector2 operator-() const;
  Vector2 operator+() const;

  std::string to_string() const;

  static const Vector2 ONE;
  static const Vector2 ZERO;
};

struct Vector2i {
  int64_t x;
  int64_t y;

  Vector2i();
  Vector2i(const int64_t new_x, const int64_t new_y);
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
  Vector2i operator*(const double right) const;
  Vector2i operator*(const int64_t right) const;

  Vector2i operator/(const Vector2 &right) const;
  Vector2i operator/(const double right) const;
  Vector2i operator/(const int64_t right) const;

  void operator+=(const Vector2i &right);
  void operator-=(const Vector2i &right);

  void operator*=(const Vector2i &right);
  void operator*=(const double right);
  void operator*=(const int64_t right);

  void operator/=(const Vector2i &right);
  void operator/=(const double right);
  void operator/=(const int64_t right);

  int64_t operator[](const int64_t index) const;
  Vector2i operator-() const;
  Vector2i operator+() const;
  
  std::string to_string() const;

  static const Vector2i ONE;
  static const Vector2i ZERO;
};
}

#endif // !VECTOR2
