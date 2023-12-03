#include "types/vector2.hpp"

using namespace sdl;

const Vector2 Vector2::ONE = Vector2(1, 1);
const Vector2 Vector2::ZERO = Vector2();
const Vector2i Vector2i::ONE = Vector2i(1, 1);
const Vector2i Vector2i::ZERO = Vector2i();

Vector2::Vector2(const double new_x, const double new_y): x(new_x),
  y(new_y)
{}

Vector2::Vector2(): x(0),
  y(0)
{}

Vector2::Vector2(const Vector2 &vector2): x(vector2.x),
  y(vector2.y)
{}

Vector2::Vector2(const Vector2i &vector2i): x(vector2i.x),
  y(vector2i.y)
{}

void Vector2::operator=(const Vector2 &right) {
  x = right.x;
  y = right.y;
}

bool Vector2::operator==(const Vector2 &right) const {
  return x == right.x && y == right.y;
}

bool Vector2::operator!=(const Vector2 &right) const {
  return x != right.x && y != right.y;
}

bool Vector2::operator<(const Vector2 &right) const {
  return x < right.x && y < right.y;
}

bool Vector2::operator<=(const Vector2 &right) const {
  return x <= right.x && y <= right.y;
}

bool Vector2::operator>(const Vector2 &right) const {
  return x > right.x && y > right.y;
}

bool Vector2::operator>=(const Vector2 &right) const {
  return x >= right.x && y >= right.y;
}

Vector2 Vector2::operator+(const Vector2 &right) const {
  return Vector2(x + right.x, y + right.y);
}

Vector2 Vector2::operator-(const Vector2 &right) const {
  return Vector2(x - right.x, y - right.y);
}

Vector2 Vector2::operator*(const Vector2 &right) const {
  return Vector2(x * right.x, y * right.y);
}

Vector2 Vector2::operator*(const double right) const {
  return Vector2(x * right, y * right);
}

Vector2 Vector2::operator*(const int64_t right) const {
  return Vector2(x * right, y * right);
}

Vector2 Vector2::operator/(const Vector2 &right) const {
  return Vector2(x / right.x, y / right.y);
}

Vector2 Vector2::operator/(const double right) const {
  return Vector2(x / right, y / right);
}

Vector2 Vector2::operator/(const int64_t right) const {
  return Vector2(x / right, y / right);
}
 
void Vector2::operator+=(const Vector2 &right) {
  x += right.x;
  y += right.y;
}

void Vector2::operator-=(const Vector2 &right) {
 x -= right.x;
 y -= right.y;
}

void Vector2::operator*=(const Vector2 &right) {
  x *= right.x;
  y *= right.y;
}

void Vector2::operator*=(const double right) {
  x *= right;
  y *= right;
}

void Vector2::operator*=(const int64_t right) {
  x *= right;
  y *= right;
}

void Vector2::operator/=(const Vector2 &right) {
  x /= right.x;
  y /= right.y;
}

void Vector2::operator/=(const double right) {
  x /= right;
  y /= right;
}

void Vector2::operator/=(const int64_t right) {
  x /= right;
  y /= right;
}

double Vector2::operator[](const int64_t index) const {
  if (index == 0)
    return x;
  else if (index == 1)
    return y;
  return 0.0;
}

Vector2 Vector2::operator+() const {
  return Vector2(+x, +y);
}

Vector2 Vector2::operator-() const {
  return Vector2(-x, -y);
}

std::string Vector2::to_string() const {
  return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

// Vector2i //


Vector2i::Vector2i(const int64_t new_x, const int64_t new_y): x(new_x),
  y(new_y)
{}

Vector2i::Vector2i(): x(0),
  y(0)
{}

Vector2i::Vector2i(const Vector2 &vector2): x(vector2.x),
  y(vector2.y)
{}

Vector2i::Vector2i(const Vector2i &vector2i): x(vector2i.x),
  y(vector2i.y)
{}

void Vector2i::operator=(const Vector2i &right) {
  x = right.x;
  y = right.y;
}

bool Vector2i::operator==(const Vector2i &right) const {
  return x == right.x && y == right.y;
}

bool Vector2i::operator!=(const Vector2i &right) const {
  return x != right.x && y != right.y;
}

bool Vector2i::operator<(const Vector2i &right) const {
  return x < right.x && y < right.y;
}

bool Vector2i::operator<=(const Vector2i &right) const {
  return x <= right.x && y <= right.y;
}

bool Vector2i::operator>(const Vector2i &right) const {
  return x > right.x && y > right.y;
}

bool Vector2i::operator>=(const Vector2i &right) const {
  return x >= right.x && y >= right.y;
}

Vector2i Vector2i::operator+(const Vector2i &right) const {
  return Vector2i(x + right.x, y + right.y);
}

Vector2i Vector2i::operator-(const Vector2i &right) const {
  return Vector2i(x - right.x, y - right.y);
}

Vector2i Vector2i::operator*(const Vector2i &right) const {
  return Vector2i(x * right.x, y * right.y);
}

Vector2i Vector2i::operator*(const double right) const {
  return Vector2i(x * right, y * right);
}

Vector2i Vector2i::operator*(const int64_t right) const {
  return Vector2i(x * right, y * right);
}

Vector2i Vector2i::operator/(const Vector2 &right) const {
  return Vector2(x / right.x, y / right.y);
}

Vector2i Vector2i::operator/(const double right) const {
  return Vector2(x / right, y / right);
}

Vector2i Vector2i::operator/(const int64_t right) const {
  return Vector2i(x / right, y / right);
}
 
void Vector2i::operator+=(const Vector2i &right) {
  x += right.x;
  y += right.y;
}

void Vector2i::operator-=(const Vector2i &right) {
 x -= right.x;
 y -= right.y;
}

void Vector2i::operator*=(const Vector2i &right) {
  x *= right.x;
  y *= right.y;
}

void Vector2i::operator*=(const double right) {
  x *= right;
  y *= right;
}

void Vector2i::operator*=(const int64_t right) {
  x *= right;
  y *= right;
}

void Vector2i::operator/=(const Vector2i &right) {
  x /= right.x;
  y /= right.y;
}

void Vector2i::operator/=(const double right) {
  x /= right;
  y /= right;
}

void Vector2i::operator/=(const int64_t right) {
  x /= right;
  y /= right;
}

int64_t Vector2i::operator[](const int64_t index) const {
  if (index == 0)
    return x;
  else if (index == 1)
    return y;
  return 0;
}

Vector2i Vector2i::operator+() const {
  return Vector2i(+x, +y);
}

Vector2i Vector2i::operator-() const {
  return Vector2i(-x, -y);
}

std::string Vector2i::to_string() const {
  return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}
