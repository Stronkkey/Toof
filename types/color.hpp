#pragma once

#include <string>
#include <types/math_defs.hpp>

#include <SDL_pixels.h>

namespace sdl {

struct Color {
  Color();
  Color(const Color &from, const uint16_t alpha);
  Color(const Color &from);
  Color(const uint16_t red, const uint16_t green, const uint16_t blue);
  Color(const uint16_t red, const uint16_t green, const uint16_t blue, const uint16_t alpha);

  uint16_t r;
  uint16_t g;
  uint16_t b;
  uint16_t a;

  Color blend(const Color &over) const;
  Color darkened(const float amount) const;

  void operator=(const Color &right);
  bool operator!=(const Color &right) const;
  bool operator==(const Color &right) const;

  Color operator*(const Color &right) const;
  Color operator*(const float right) const;
  void operator*=(const Color &right);
  void operator*=(const float right);

  Color operator+(const Color &right) const;
  Color operator-(const Color &right) const;
  void operator+=(const Color &right);
  void operator-=(const Color &right);

  Color operator/(const Color &right) const;
  Color operator/(const float right) const;
  void operator/=(const Color &right);
  void operator/=(const float right);

  SDL_Color to_sdl_color() const;

  [[nodiscard]] std::string to_string() const;

  Color operator+() const;
  Color operator-() const;
  uint16_t operator[](const int index) const;

  static const Color WHITE;
  static const Color BLACK;
  static const Color TRANSPARENT;
  static const Color RED;
  static const Color GREEN;
  static const Color BLUE;
};

typedef Color Colour;

}
