#include <types/transform2d.hpp>
#include <types/rect2.hpp>
#include <algorithm>

using namespace sdl;

const Rect2 Rect2::EMPTY = Rect2();
const Rect2i Rect2i::EMPTY = Rect2i();

Rect2::Rect2(): x(0), y(0), w(0), h(0) {
}

Rect2::Rect2(const Vector2 &position, const Vector2 &size): x(position.x), y(position.y), w(size.x), h(size.y) {
}

Rect2::Rect2(const real_t position_x, const real_t position_y, const real_t size_x, const real_t size_y): x(position_x), y(position_y), w(size_x), h(size_y) {
}

Rect2::Rect2(const Rect2 &rect): x(rect.x), y(rect.y), w(rect.w), h(rect.h) {
}

Rect2::Rect2(const Rect2i &rect): x(rect.x), y(rect.y), w(rect.w), h(rect.h) { 
}

Rect2::Rect2(const SDL_Rect &rect): x(rect.x), y(rect.y), w(rect.w), h(rect.h) {
}

Rect2::Rect2(const SDL_FRect &frect): x(frect.x), y(frect.y), w(frect.w), h(frect.h) {
}

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
	return get_position() != right.get_position() || get_size() != right.get_size();
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

Rect2 Rect2::operator*(const Transform2D &right) const {
	Rect2 rect = *this;
	rect *= right;
	return rect;
}

Rect2 Rect2::operator/(const Rect2 &right) const {
	return Rect2(get_position() / right.get_position(), get_size() / right.get_size());
}

Rect2 Rect2::operator/(const real_t right) const {
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

void Rect2::operator*=(const Transform2D &right) {
	x += right.origin.x;
	y += right.origin.y;
	w *= right.scale.x;
	h *= right.scale.y;
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

real_t Rect2::operator[](const int index) const {
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

bool Rect2::has_point(const Vector2 &point) const {
	if (point.x < x)
		return false;
	if (point.y < y)
		return false;
	if (point.x >= (x + w))
		return false;
	if (point.y >= (y + h))
		return false;

	return true;
}

bool Rect2::intersects(const Rect2 &rect2, const bool include_borders) const {
	if (include_borders) {
		if (x > (rect2.x + rect2.w))
			return false;

		if ((x + w) < rect2.x)
			return false;

		if (y > (rect2.y + rect2.h))
			return false;

		if ((y + h) < rect2.y)
			return false;
	} else {
		if (x >= (rect2.x + rect2.w))
			return false;

		if ((x + w) <= rect2.x)
			return false;

		if (y >= (rect2.y + rect2.h))
			return false;

		if ((y + h) <= rect2.y)
			return false;
	}

	return true;
}

Rect2 Rect2::merge(const Rect2 &right) const {
	Rect2 new_rect;

	new_rect.x = std::min(right.x, x);
	new_rect.y = std::min(right.y, y);

	new_rect.w = std::max(right.x + right.w, x + w);
	new_rect.h = std::max(right.y + right.h, y + h);

	new_rect.w -= new_rect.x;
	new_rect.h -= new_rect.h;

	return new_rect;
}

Rect2 Rect2::abs() const {
	Rect2 rect = Rect2{};

	rect.x = std::abs(rect.x);
	rect.y = std::abs(rect.y);
	rect.w = std::abs(rect.w);
	rect.h = std::abs(rect.h);

	return rect;
}

Rect2 Rect2::remove_negative_size() const {
	Rect2 rect = *this;
	if (w < 0.0) {
		rect.x += w;
		rect.w = std::abs(rect.w);
	}

	if (h < 0.0) {
		rect.y += h;
		rect.h = std::abs(h);
	}

	return rect;
}

Rect2 Rect2::expand(const Vector2 &to) const {
	Rect2 rect = *this;
	rect.expand_to(to);
	return rect;
}

void Rect2::expand_to(const Vector2 &to) {
	Vector2 begin = get_position();
	Vector2 end = begin + get_size();

	if (to.x < begin.x)
		begin.x = to.x;

	if (to.y < begin.y)
		begin.y = to.y;

	if (to.x > end.x)
		end.x = to.x;

	if (to.y > end.y)
		end.y = to.y;

	x = begin.x;
	y = begin.y;
	w = end.x;
	h = end.y;
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

SDL_FRect Rect2::to_sdl_frect() const {
	SDL_FRect rect;
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

SDL_FRect Rect2::to_sdl_frect(const Rect2 &rect2) {
	SDL_FRect rect;
	rect.x = rect2.x;
	rect.y = rect2.y;
	rect.w = rect2.w;
	rect.h = rect2.h;
	return rect;
}

// RECT2i //

Rect2i::Rect2i(): x(0), y(0), w(0), h(0) {
}

Rect2i::Rect2i(const Vector2i &position, const Vector2i &size): x(position.x), y(position.y), w(size.x), h(size.y) {
}

Rect2i::Rect2i(const int_t position_x, const int_t position_y, const int_t size_x, const int_t size_y): x(position_x), y(position_y), w(size_x), h(size_y) {
}

Rect2i::Rect2i(const Rect2 &rect): x(rect.x), y(rect.y), w(rect.w), h(rect.h) {
}

Rect2i::Rect2i(const Rect2i &rect): x(rect.x), y(rect.y), w(rect.w), h(rect.h) {
}

Rect2i::Rect2i(const SDL_Rect &rect): x(rect.x), y(rect.y), w(rect.w), h(rect.h) {
}

Rect2i::Rect2i(const SDL_FRect &frect): x(frect.x), y(frect.y), w(frect.w), h(frect.h) {
}

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

Rect2i Rect2i::operator*(const int_t right) const {
	return Rect2i(get_position() * right, get_size() * right);
}

Rect2i Rect2i::operator/(const Rect2i &right) const {
	return Rect2i(get_position() / right.get_position(), get_size() / right.get_size());
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

void Rect2i::operator/=(const int_t right) {
	x /= right;
	y /= right;
	w /= right;
	h /= right;
}

int_t Rect2i::operator[](const int index) const {
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

bool Rect2i::has_point(const Vector2i &point) const {
	if (point.x < x)
		return false;
	if (point.y < y)
		return false;
	if (point.x >= (x + w))
		return false;
	if (point.y >= (y + h))
		return false;

	return true;
}

bool Rect2i::intersects(const Rect2i &rect2i, const bool include_borders) const {
	if (include_borders) {
		if (x > (rect2i.x + rect2i.w))
			return false;

		if ((x + w) < rect2i.x)
			return false;

		if (y > (rect2i.y + rect2i.h))
			return false;

		if ((y + h) < rect2i.y)
			return false;
	} else {
		if (x >= (rect2i.x + rect2i.w))
			return false;

		if ((x + w) <= rect2i.x)
			return false;

		if (y >= (rect2i.y + rect2i.h))
			return false;

		if ((y + h) <= rect2i.y)
			return false;
	}

	return true;
}

Rect2i Rect2i::merge(const Rect2i &right) const {
	Rect2i new_rect;

	new_rect.x = std::min(right.x, x);
	new_rect.y = std::min(right.y, y);

	new_rect.w = std::max(right.x + right.w, x + w);
	new_rect.h = std::max(right.y + right.h, y + h);

	new_rect.w -= new_rect.x;
	new_rect.h -= new_rect.h;

	return new_rect;
}

Rect2i Rect2i::abs() const {
	Rect2i rect = Rect2i{};

	rect.x = std::abs(rect.x);
	rect.y = std::abs(rect.y);
	rect.w = std::abs(rect.w);
	rect.h = std::abs(rect.h);

	return rect;
}

Rect2i Rect2i::remove_negative_size() const {
	Rect2i rect = *this;
	if (w < 0.0) {
		rect.x += w;
		rect.w = std::abs(rect.w);
	}

	if (h < 0.0) {
		rect.y += h;
		rect.h = std::abs(h);
	}

	return rect;
}

Rect2i Rect2i::expand(const Vector2i &to) const {
	Rect2i rect = *this;
	rect.expand_to(to);
	return rect;
}

void Rect2i::expand_to(const Vector2i &to) {
	Vector2i begin = get_position();
	Vector2i end = begin + get_size();

	if (to.x < begin.x)
		begin.x = to.x;

	if (to.y < begin.y)
		begin.y = to.y;

	if (to.x > end.x)
		end.x = to.x;

	if (to.y > end.y)
		end.y = to.y;

	x = begin.x;
	y = begin.y;
	w = end.x;
	h = end.y;
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

SDL_FRect Rect2i::to_sdl_frect() const {
	SDL_FRect frect;
	frect.x = x;
	frect.y = y;
	frect.w = w;
	frect.h = h;
	return frect;
}

SDL_Rect Rect2i::to_sdl_rect(const Rect2i &rect2i) {
	SDL_Rect rect;
	rect.x = rect2i.x;
	rect.y = rect2i.y;
	rect.w = rect2i.w;
	rect.h = rect2i.h;
	return rect;
}

SDL_FRect Rect2i::to_sdl_frect(const Rect2i &rect2i) {
	SDL_FRect frect;
	frect.x = rect2i.x;
	frect.y = rect2i.y;
	frect.w = rect2i.w;
	frect.h = rect2i.h;
	return frect;
}
