#ifndef RECT2_LIB
#define RECT2_LIB

#include <types/vector2.hpp>
#include <SDL2/SDL_rect.h>

namespace sdl {

struct Rect2i;

struct Rect2 {
  double x;
  double y;
  double w;
  double h;

  Rect2();
  Rect2(const Vector2 &position, const Vector2 &size);
  Rect2(double position_x, double position_y, double size_x, double size_y);
  Rect2(const Rect2 &rect);
  Rect2(const Rect2i &rect);
  Rect2(const SDL_Rect &rect);

  void operator=(const Rect2 &right);
  bool operator==(const Rect2 &right) const;
  bool operator!=(const Rect2 &right) const;
  
  bool operator<(const Rect2 &right) const;
  bool operator<=(const Rect2 &right) const;
  bool operator>(const Rect2 &right) const;
  bool operator>=(const Rect2 &right) const;

  Rect2 operator+(const Rect2 &right) const;
  Rect2 operator-(const Rect2 &right) const;

  Rect2 operator*(const Rect2 &right) const;
  Rect2 operator*(const double right) const;
  Rect2 operator*(const int64_t right) const;

  Rect2 operator/(const Rect2 &right) const;
  Rect2 operator/(const double right) const;
  Rect2 operator/(const int64_t right) const;

  void operator+=(const Rect2 &right);
  void operator-=(const Rect2 &right);

  void operator*=(const Rect2 &right);
  void operator*=(const double right);
  void operator*=(const int64_t right);

  void operator/=(const Rect2 &right);
  void operator/=(const double right);
  void operator/=(const int64_t right);

  double operator[](const int64_t index) const;
  Rect2 operator-() const;
  Rect2 operator+() const;

  String to_string() const;
  Vector2 get_position() const;
  Vector2 get_size() const;

  void set_position(const Vector2 &new_position);
  void set_size(const Vector2 &new_size);

  SDL_Rect to_sdl_rect() const;

  static const Rect2 EMPTY;
  static SDL_Rect to_sdl_rect(const Rect2 &rect2);
};

struct Rect2i {
  int64_t x;
  int64_t y;
  int64_t w;
  int64_t h;

  Rect2i();
  Rect2i(const Vector2i &position, const Vector2i &size);
  Rect2i(int64_t x, int64_t y, int64_t w, int64_t h);
  Rect2i(const Rect2 &rect);
  Rect2i(const Rect2i &rect);
  Rect2i(const SDL_Rect &rect);

  void operator=(const Rect2i &right);
  bool operator==(const Rect2i &right) const;
  bool operator!=(const Rect2i &right) const;
  
  bool operator<(const Rect2i &right) const;
  bool operator<=(const Rect2i &right) const;
  bool operator>(const Rect2i &right) const;
  bool operator>=(const Rect2i &right) const;

  Rect2i operator+(const Rect2i &right) const;
  Rect2i operator-(const Rect2i &right) const;

  Rect2i operator*(const Rect2i &right) const;
  Rect2i operator*(const double right) const;
  Rect2i operator*(const int64_t right) const;

  Rect2i operator/(const Rect2i &right) const;
  Rect2i operator/(const double right) const;
  Rect2i operator/(const int64_t right) const;

  void operator+=(const Rect2i &right);
  void operator-=(const Rect2i &right);

  void operator*=(const Rect2i &right);
  void operator*=(const double right);
  void operator*=(const int64_t right);

  void operator/=(const Rect2i &right);
  void operator/=(const double right);
  void operator/=(const int64_t right);

  int64_t operator[](const int64_t index) const;
  Rect2i operator-() const;
  Rect2i operator+() const;

  Vector2i get_position() const;
  Vector2i get_size() const;

  String to_string() const;
  void set_position(const Vector2i &new_position);
  void set_size(const Vector2i &new_size);

  SDL_Rect to_sdl_rect() const;

  static const Rect2i EMPTY;
  static SDL_Rect to_sdl_rect(const Rect2i &rect2i);
};

}

#endif // !RECT2_LIB
