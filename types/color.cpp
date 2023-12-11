#include <types/color.hpp>

using namespace sdl;

Color::Color(): r(0),
  g(0),
  b(0),
  a(1)
{}

Color::Color(const Color &from, const uint16_t alpha): r(from.r),
  g(from.g),
  b(from.b),
  a(alpha)
{}

Color::Color(const Color &from): r(from.r),
  g(from.g),
  b(from.b),
  a(from.a)
{}

Color::Color(const uint16_t red, const uint16_t green, const uint16_t blue): r(red),
  g(green),
  b(blue)
{}

Color::Color(const uint16_t red, const uint16_t green, const uint16_t blue, const uint16_t alpha): r(red),
  g(green),
  b(blue),
  a(alpha)
{}

Color Color::blend(const Color &over) const {
  Color blended_color;
  uint16_t inverted_alpha = 255 - over.a;
  blended_color.a = a * inverted_alpha + over.a;
  if (blended_color.a == 0)
    return Color(0, 0, 0, 0);
  blended_color.r = (r * a * inverted_alpha + over.r * over.a) / blended_color.a;
  blended_color.g = (g * a * inverted_alpha + over.g * over.a) / blended_color.a;
  blended_color.b = (b * a * inverted_alpha + over.b * over.a) / blended_color.a;

  return blended_color;
}

Color Color::darkened(const float amount) const {
  Color darkened_color = *this;
  darkened_color.r *= (1.0f - -amount);
  darkened_color.g *= (1.0f - -amount);
  darkened_color.b *= (1.0f - -amount);
  return darkened_color;
}

bool Color::operator!=(const Color &right) const {
  return a != right.a || r != right.r || g != right.g || b != right.b;
}

bool Color::operator==(const Color &right) const {
  return a == right.a && r == right.r && g == right.g && b == right.b;
}

Color Color::operator*(const Color &right) const {
  Color multiplied_color = *this;
  multiplied_color.r *= right.r;
  multiplied_color.g *= right.g;
  multiplied_color.b *= right.b;
  multiplied_color.a *= right.a;
  return multiplied_color;
}

Color Color::operator*(const float right) const {
  Color multiplied_color = *this;
  multiplied_color.r *= right;
  multiplied_color.g *= right;
  multiplied_color.b *= right;
  multiplied_color.a *= right;
  return multiplied_color;
}

Color Color::operator+(const Color &right) const {
  Color added_color = *this;
  added_color.a += right.a;
  added_color.r += right.r;
  added_color.g += right.g;
  added_color.b += right.b;
  return added_color;
}

Color Color::operator-(const Color &right) const {
  Color added_color = *this;
  added_color.a -= right.a;
  added_color.r -= right.r;
  added_color.g -= right.g;
  added_color.b -= right.b;
  return added_color;
}

Color Color::operator+() const {
  Color unary_color = *this;
  unary_color.a = +unary_color.a;
  unary_color.r = +unary_color.r;
  unary_color.g = +unary_color.g;
  unary_color.b = +unary_color.b;
  return unary_color;
}

Color Color::operator-() const {
  Color unary_color = *this;
  unary_color.a = -unary_color.a;
  unary_color.r = -unary_color.r;
  unary_color.g = -unary_color.g;
  unary_color.b = -unary_color.b;
  return unary_color;
}

Color Color::operator/(const Color &right) const {
  Color divided_color = *this;
  divided_color.a /= right.a;
  divided_color.r /= right.r;
  divided_color.g /= right.g;
  divided_color.b /= right.b;
  return divided_color;
}

Color Color::operator/(const float right) const {
  Color divided_color = *this;
  divided_color.a /= right;
  divided_color.r /= right;
  divided_color.g /= right;
  divided_color.b /= right;
  return divided_color;
}

void Color::operator/=(const Color &right) {
  a /= right.a;
  r /= right.r;
  g /= right.g;
  b /= right.b;
}

void Color::operator/=(const float right) {
  a /= right;
  r /= right;
  g /= right;
  b /= right;
}

SDL_Color Color::to_sdl_color() const {
  SDL_Color color;
  color.a = a;
  color.r = r;
  color.b = b;
  color.g = g;
  return color;
}

SDL_Color Color::to_sdl_color(const Color &color) {
  SDL_Color sdl_color;
  sdl_color.a = color.a;
  sdl_color.r = color.r;
  sdl_color.b = color.b;
  sdl_color.g = color.g;
  return sdl_color;
}

uint16_t Color::operator[](const int index) const {
  switch (index) {
    case 0:
      return r;
    case 1:
      return g;
    case 2:
      return b;
    default:
      return 0;
  }
}
