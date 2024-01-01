#include <types/vector2.hpp>

#include <cmath>

using namespace sdl;

const Vector2 Vector2::ONE = Vector2(1, 1);
const Vector2 Vector2::ZERO = Vector2(0, 0);
const Vector2 Vector2::LEFT = Vector2(-1, 0);
const Vector2 Vector2::RIGHT = Vector2(1, 0);
const Vector2 Vector2::DOWN = Vector2(0, 1);
const Vector2 Vector2::UP = Vector2(0, -1);

const Vector2i Vector2i::ONE = Vector2i(1, 1);
const Vector2i Vector2i::ZERO = Vector2i(0, 0);
const Vector2i Vector2i::LEFT = Vector2i(-1, 0);
const Vector2i Vector2i::RIGHT = Vector2i(1, 0);
const Vector2i Vector2i::DOWN = Vector2i(0, 1);
const Vector2i Vector2i::UP = Vector2i(0, -1);

Vector2::Vector2(const real_t new_x, const real_t new_y): x(new_x), y(new_y) {
}

Vector2::Vector2(): x(0), y(0) {
}

Vector2::Vector2(const Vector2 &vector2): x(vector2.x), y(vector2.y) {
}

Vector2::Vector2(const Vector2i &vector2i): x(vector2i.x), y(vector2i.y) {
}

Vector2::Vector2(const SDL_FPoint &fpoint): x(fpoint.x), y(fpoint.y) {
}

Vector2::Vector2(const SDL_Point &point): x(point.x), y(point.y) {
}

void Vector2::operator=(const Vector2 &right) {
	x = right.x;
	y = right.y;
}

bool Vector2::operator==(const Vector2 &right) const {
	return x == right.x && y == right.y;
}

bool Vector2::operator!=(const Vector2 &right) const {
	return x != right.x || y != right.y;
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

Vector2 Vector2::operator*(const real_t right) const {
	return Vector2(x * right, y * right);
}

Vector2 Vector2::operator/(const Vector2 &right) const {
	return Vector2(x / right.x, y / right.y);
}

Vector2 Vector2::operator/(const real_t right) const {
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

void Vector2::operator*=(const real_t right) {
	x *= right;
	y *= right;
}

void Vector2::operator/=(const Vector2 &right) {
	x /= right.x;
	y /= right.y;
}

void Vector2::operator/=(const real_t right) {
	x /= right;
	y /= right;
}

real_t Vector2::operator[](const int index) const {
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

void Vector2::normalize() {
	real_t length = (x * x) + (y * y);
	if (length != 0.0) {
		length = std::sqrt(length);
		x /= length;
		y /= length;
	}
}

void Vector2::rounded() {
	x = std::round(x);
	y = std::round(y);
}

void Vector2::floored() {
	x = std::floor(x);
	y = std::floor(y);
}

void Vector2::ceiled() {
	x = std::ceil(x);
	y = std::ceil(y);
}

Vector2 Vector2::move_toward(const Vector2 &to, const real_t delta) const {
	Vector2 vector = *this;
	Vector2 from_vector = to - vector;
	real_t length = from_vector.length();
	return length <= delta ? to : vector + from_vector / length * delta;
}

real_t Vector2::length() const {
	return std::sqrt(x * x + y * y);
}

real_t Vector2::length_squared() const {
	return x * x + y * y;
}

Vector2 Vector2::normalized() const {
	Vector2 vector = *this;
	vector.normalize();
	return vector;
}

Vector2 Vector2::ceil() const {
	Vector2 vector = *this;
	vector.ceiled();
	return vector;
}

Vector2 Vector2::round() const {
	Vector2 vector = *this;
	vector.rounded();
	return vector;
}

Vector2 Vector2::floor() const {
	Vector2 vector = *this;
	vector.floored();
	return vector;
}

std::string Vector2::to_string() const {
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

SDL_FPoint Vector2::to_sdl_fpoint() const {
	SDL_FPoint fpoint;
	fpoint.x = x;
	fpoint.y = y;
	return fpoint;
}

SDL_Point Vector2::to_sdl_point() const {
	SDL_Point point;
	point.x = x;
	point.y = y;
	return point;
}

// Vector2i //


Vector2i::Vector2i(const int_t new_x, const int_t new_y): x(new_x), y(new_y) {
}

Vector2i::Vector2i(): x(0), y(0) {
}

Vector2i::Vector2i(const Vector2 &vector2): x(vector2.x), y(vector2.y) {
}

Vector2i::Vector2i(const Vector2i &vector2i): x(vector2i.x), y(vector2i.y) {
}

Vector2i::Vector2i(const SDL_FPoint &fpoint): x(fpoint.x), y(fpoint.y) {
}

Vector2i::Vector2i(const SDL_Point &point): x(point.x), y(point.y) {
}

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

Vector2i Vector2i::operator*(const int_t right) const {
	return Vector2i(x * right, y * right);
}

Vector2i Vector2i::operator/(const Vector2 &right) const {
	return Vector2(x / right.x, y / right.y);
}

Vector2i Vector2i::operator/(const int_t right) const {
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

void Vector2i::operator*=(const int_t right) {
	x *= right;
	y *= right;
}

void Vector2i::operator/=(const Vector2i &right) {
	x /= right.x;
	y /= right.y;
}

void Vector2i::operator/=(const int_t right) {
	x /= right;
	y /= right;
}

int_t Vector2i::operator[](const int index) const {
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

SDL_FPoint Vector2i::to_sdl_fpoint() const {
	SDL_FPoint fpoint;
	fpoint.x = x;
	fpoint.y = y;
	return fpoint;
}

SDL_Point Vector2i::to_sdl_point() const {
	SDL_Point point;
	point.x = x;
	point.y = y;
	return point;
}
