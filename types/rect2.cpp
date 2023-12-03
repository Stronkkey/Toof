#include "types/rect2.hpp"
#include <cstdlib>

using namespace sdl;

const Rect2 Rect2::EMPTY = Rect2();
const Rect2i Rect2i::EMPTY = Rect2i();

Rect2::Rect2(): x(0),
  y(0),
  w(0),
  h(0)
{}

Rect2::Rect2(const Vector2 &position, const Vector2 &size): x(position.x),
  y(position.y),
  w(size.x),
  h(size.y)
{}

Rect2::Rect2(const real_t position_x, const real_t position_y, const real_t size_x, const real_t size_y): x(position_x),
  y(position_y),
  w(size_x),
  h(size_y)
{}

Rect2::Rect2(const Rect2 &rect): x(rect.x),
  y(rect.y),
  w(rect.w),
  h(rect.h)
{}

Rect2::Rect2(const Rect2i &rect): x(rect.x),
  y(rect.y),
  w(rect.w),
  h(rect.h)
{}

Rect2::Rect2(const SDL_Rect &rect): x(rect.x),
  y(rect.y),
  w(rect.w),
  h(rect.h)
{}

void Rect2::operator=(const Rect2 &right) {
  x = right.x;
  y = right.y;
  w = right.w;
  h = right.h;
}

bool Rect2::operator==(const Rect2 &right) const {
  return get_position() == right.get_position() && get_size() == right.get_size();
}

bool Rect2::operator!=(const Rect2 &right) const {
  return get_position() != right.get_position() && get_size() != right.get_size();
}

bool Rect2::operator<(const Rect2 &right) const {
  return get_position() < right.get_position() && get_size() < right.get_size();
}

bool Rect2::operator<=(const Rect2 &right) const {
  return get_position() <= right.get_position() && get_size() <= right.get_size();
}

bool Rect2::operator>(const Rect2 &right) const {
  return get_position() > right.get_position() && get_size() > right.get_size();
}

bool Rect2::operator>=(const Rect2 &right) const {
  return get_position() >= right.get_position() && get_size() >= right.get_size();
}

Rect2 Rect2::operator+(const Rect2 &right) const {
  return Rect2(get_position() + right.get_position(), get_size() + right.get_size());
}

Rect2 Rect2::operator-(const Rect2 &right) const {
  return Rect2(get_position() - right.get_position(), get_size() - right.get_size());
}

Rect2 Rect2::operator*(const Rect2 &right) const {
  return Rect2(get_position() * right.get_position(), get_size() - right.get_size());
}

Rect2 Rect2::operator*(const real_t right) const {
  return Rect2(get_position() * right, get_size() * right);
}

Rect2 Rect2::operator*(const int_t right) const {
  return Rect2(get_position() * right, get_size() * right);
}

Rect2 Rect2::operator/(const Rect2 &right) const {
  return Rect2(get_position() / right.get_position(), get_size() / right.get_size());
}

Rect2 Rect2::operator/(const real_t right) const {
  return Rect2(get_position() / right, get_size() / right);
}

Rect2 Rect2::operator/(const int_t right) const {
  return Rect2(get_position() / right, get_size() / right);
}
 
void Rect2::operator+=(const Rect2 &right) {
  x += right.x;
  y += right.y;
  w += right.w;
  h += right.h;
}

void Rect2::operator-=(const Rect2 &right) {
  x -= right.x;
  y -= right.y;
  w -= right.w;
  h -= right.h;
}

void Rect2::operator*=(const Rect2 &right) {
  x *= right.x;
  y *= right.y;
  w *= right.w;
  h *= right.h;
}

void Rect2::operator*=(const real_t right) {
  x *= right;
  y *= right;
  w *= right;
  h *= right;
}

void Rect2::operator*=(const int_t right) {
  x *= right;
  y *= right;
  w *= right;
  h *= right;
}

void Rect2::operator/=(const Rect2 &right) {
  x /= right.x;
  y /= right.y;
  w /= right.w;
  h /= right.h;
}

void Rect2::operator/=(const real_t right) {
  x /= right;
  y /= right;
  w /= right;
  h /= right;
}

void Rect2::operator/=(const int_t right) {
  x /= right;
  y /= right;
  w /= right;
  h /= right;
}

real_t Rect2::operator[](const int_t index) const {
  switch (index) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return w;
    case 3:
      return h;
  }
  return 0.0;
}

Rect2 Rect2::operator+() const {
  return Rect2(+x, +y, +w, +h);
}

Rect2 Rect2::operator-() const {
  return Rect2(-x, -y, -w, -h);
}

std::string Rect2::to_string() const {
  return "(" + get_position().to_string() + ", " + get_size().to_string() + ")";
}

Vector2 Rect2::get_position() const {
  return Vector2(x, y);
}

Vector2 Rect2::get_size() const {
  return Vector2(w, h);
}

void Rect2::set_position(const Vector2 &new_position) {
  x = new_position.x;
  y = new_position.y;
}

void Rect2::set_size(const Vector2 &new_size) {
  x = new_size.x;
  y = new_size.y;
}

SDL_Rect Rect2::to_sdl_rect() const {
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;
  return rect;
}

SDL_Rect Rect2::to_sdl_rect(const Rect2 &rect2) {
  SDL_Rect rect;
  rect.x = rect2.x;
  rect.y = rect2.y;
  rect.w = rect2.w;
  rect.h = rect2.h;
  return rect;
}

// RECT2i //

Rect2i::Rect2i(): x(0),
  y(0),
  w(0),
  h(0)
{}

Rect2i::Rect2i(const Vector2i &position, const Vector2i &size): x(position.x),
  y(position.y),
  w(size.x),
  h(size.y)
{}

Rect2i::Rect2i(const int64_t position_x, const int64_t position_y, const int64_t size_x, const int64_t size_y): x(position_x),
  y(position_y),
  w(size_x),
  h(size_y)
{}

Rect2i::Rect2i(const Rect2 &rect): x(rect.x),
  y(rect.y),
  w(rect.w),
  h(rect.h)
{}

Rect2i::Rect2i(const Rect2i &rect): x(rect.x),
  y(rect.y),
  w(rect.w),
  h(rect.h)
{}

Rect2i::Rect2i(const SDL_Rect &rect): x(rect.x),
  y(rect.y),
  w(rect.w),
  h(rect.h)
{}

void Rect2i::operator=(const Rect2i &right) {
  x = right.x;
  y = right.y;
  w = right.w;
  h = right.h;
}

bool Rect2i::operator==(const Rect2i &right) const {
  return get_position() == right.get_position() && get_size() == right.get_size();
}

bool Rect2i::operator!=(const Rect2i &right) const {
  return get_position() != right.get_position() && get_size() != right.get_size();
}

bool Rect2i::operator<(const Rect2i &right) const {
  return get_position() < right.get_position() && get_size() < right.get_size();
}

bool Rect2i::operator<=(const Rect2i &right) const {
  return get_position() <= right.get_position() && get_size() <= right.get_size();
}

bool Rect2i::operator>(const Rect2i &right) const {
  return get_position() > right.get_position() && get_size() > right.get_size();
}

bool Rect2i::operator>=(const Rect2i &right) const {
  return get_position() >= right.get_position() && get_size() >= right.get_size();
}

Rect2i Rect2i::operator+(const Rect2i &right) const {
  return Rect2i(get_position() + right.get_position(), get_size() + right.get_size());
}

Rect2i Rect2i::operator-(const Rect2i &right) const {
  return Rect2i(get_position() - right.get_position(), get_size() - right.get_size());
}

Rect2i Rect2i::operator*(const Rect2i &right) const {
  return Rect2i(get_position() * right.get_position(), get_size() - right.get_size());
}

Rect2i Rect2i::operator*(const real_t right) const {
  return Rect2i(get_position() * right, get_size() * right);
}

Rect2i Rect2i::operator*(const int_t right) const {
  return Rect2i(get_position() * right, get_size() * right);
}

Rect2i Rect2i::operator/(const Rect2i &right) const {
  return Rect2i(get_position() / right.get_position(), get_size() / right.get_size());
}

Rect2i Rect2i::operator/(const real_t right) const {
  return Rect2i(get_position() / right, get_size() / right);
}

Rect2i Rect2i::operator/(const int_t right) const {
  return Rect2i(get_position() / right, get_size() / right);
}
 
void Rect2i::operator+=(const Rect2i &right) {
  x += right.x;
  y += right.y;
  w += right.w;
  h += right.h;
}

void Rect2i::operator-=(const Rect2i &right) {
  x -= right.x;
  y -= right.y;
  w -= right.w;
  h -= right.h;
}

void Rect2i::operator*=(const Rect2i &right) {
  x *= right.x;
  y *= right.y;
  w *= right.w;
  h *= right.h;
}

void Rect2i::operator*=(const real_t right) {
  x *= right;
  y *= right;
  w *= right;
  h *= right;
}

void Rect2i::operator*=(const int_t right) {
  x *= right;
  y *= right;
  w *= right;
  h *= right;
}

void Rect2i::operator/=(const Rect2i &right) {
  x /= right.x;
  y /= right.y;
  w /= right.w;
  h /= right.h;
}

void Rect2i::operator/=(const real_t right) {
  x /= right;
  y /= right;
  w /= right;
  h /= right;
}

void Rect2i::operator/=(const int_t right) {
  x /= right;
  y /= right;
  w /= right;
  h /= right;
}

int_t Rect2i::operator[](const int_t index) const {
  switch (index) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return w;
    case 3:
      return h;
  }
  return 0;
}

std::string Rect2i::to_string() const {
  return "(" + get_position().to_string() + ", " + get_size().to_string() + ")";
}

Vector2i Rect2i::get_position() const {
  return Vector2i(x, y);
}

Vector2i Rect2i::get_size() const {
  return Vector2i(w, h);
}

void Rect2i::set_position(const Vector2i &new_position) {
  x = new_position.x;
  y = new_position.y;
}

void Rect2i::set_size(const Vector2i &new_size) {
  w = new_size.x;
  h = new_size.y;
}

SDL_Rect Rect2i::to_sdl_rect() const {
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;
  return rect;
}

SDL_Rect Rect2i::to_sdl_rect(const Rect2i &rect2i) {
  SDL_Rect rect;
  rect.x = rect2i.x;
  rect.y = rect2i.y;
  rect.w = rect2i.w;
  rect.h = rect2i.h;
  return rect;
}
