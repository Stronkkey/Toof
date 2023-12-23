#pragma once

#include <types/vector2.hpp>

namespace sdl {

struct Rect2i;

struct Rect2 {
  real_t x;
  real_t y;
  real_t w;
  real_t h;

  Rect2();
  Rect2(const Vector2 &position, const Vector2 &size);
  Rect2(const real_t position_x, const real_t position_y, const real_t size_x, const real_t size_y);
  Rect2(const Rect2 &rect);
  Rect2(const Rect2i &rect);
  Rect2(const SDL_Rect &rect);
  Rect2(const SDL_FRect &frect);

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
  Rect2 operator*(const real_t right) const;

  Rect2 operator/(const Rect2 &right) const;
  Rect2 operator/(const real_t right) const;

  void operator+=(const Rect2 &right);
  void operator-=(const Rect2 &right);

  void operator*=(const Rect2 &right);
  void operator*=(const real_t right);

  void operator/=(const Rect2 &right);
  void operator/=(const real_t right);

  real_t operator[](const int index) const;
  Rect2 operator-() const;
  Rect2 operator+() const;

  [[nodiscard]] std::string to_string() const;
  Vector2 get_position() const;
  Vector2 get_size() const;
  bool has_point(const Vector2 &point) const;
  bool intersects(const Rect2 &rect2, const bool include_borders = false) const;

  void set_position(const Vector2 &new_position);
  void set_size(const Vector2 &new_size);

  [[nodiscard]] SDL_Rect to_sdl_rect() const;
  [[nodiscard]] SDL_FRect to_sdl_frect() const;

  static const Rect2 EMPTY;
  static SDL_Rect to_sdl_rect(const Rect2 &rect2);
  static SDL_FRect to_sdl_frect(const Rect2 &rect);
};

struct Rect2i {
  int_t x;
  int_t y;
  int_t w;
  int_t h;

  Rect2i();
  Rect2i(const Vector2i &position, const Vector2i &size);
  Rect2i(const int_t x, const int_t y, const int_t w, const int_t h);
  Rect2i(const Rect2 &rect);
  Rect2i(const Rect2i &rect);
  Rect2i(const SDL_Rect &rect);
  Rect2i(const SDL_FRect &frect);

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
  Rect2i operator*(const int_t right) const;

  Rect2i operator/(const Rect2i &right) const;
  Rect2i operator/(const int_t right) const;

  void operator+=(const Rect2i &right);
  void operator-=(const Rect2i &right);

  void operator*=(const Rect2i &right);
  void operator*=(const int_t right);

  void operator/=(const Rect2i &right);
  void operator/=(const int_t right);

  int_t operator[](const int index) const;
  Rect2i operator-() const;
  Rect2i operator+() const;

  Vector2i get_position() const;
  Vector2i get_size() const;

  [[nodiscard]] std::string to_string() const;
  void set_position(const Vector2i &new_position);
  void set_size(const Vector2i &new_size);
  bool has_point(const Vector2i &point) const;
  bool intersects(const Rect2i &rect2i, const bool include_borders = false) const;

  [[nodiscard]] SDL_Rect to_sdl_rect() const;
  [[nodiscard]] SDL_FRect to_sdl_frect() const;

  static const Rect2i EMPTY;
  static SDL_Rect to_sdl_rect(const Rect2i &rect2i);
  static SDL_FRect to_sdl_frect(const Rect2i &rect2i);
};

}
