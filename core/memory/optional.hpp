#pragma once

#include <algorithm>

namespace sdl {

struct NullOptionT {
};

constexpr const NullOptionT NullOption = NullOptionT();

template<class T>
class Optional {
private:
	T value;
	bool valid;
public:
	constexpr Optional(): value(), valid(false) {
	}

	constexpr Optional(const T &value): value(value), valid(true) {
	}

	constexpr Optional(T &&value): value(std::move(value)), valid(true) {
	}

	constexpr Optional(const NullOptionT&): value(), valid(false) {
	}

	constexpr Optional(const Optional &optional): value(optional.value), valid(optional.valid) {
	}

	constexpr Optional(Optional &&optional): value(optional.value), valid(optional.valid) {
	}

	constexpr operator bool() const {
		return valid;
	}

	constexpr void operator=(const NullOptionT&) noexcept {
		valid = false;
	}

	constexpr void operator=(const Optional &other) noexcept {
		value = other.value;
		valid = other.valid;
	}

	constexpr void operator=(Optional &&other) noexcept {
		value = std::move(other.value);
		valid = other.valid;
	}

	template<class U = T>
	constexpr void operator=(U &&value) {
		this->value = std::move(value);
		valid = true;
	}

	template<class U = T>
	constexpr void operator=(const Optional<U> &other) {
		value = other.value;
		valid = other.valid;
	}

	template<class U = T>
	constexpr void operator=(Optional<U> &&other) {
		value = std::move(other.value);
		valid = other.valid;
	}

	constexpr T &operator--(int) const & {
		return value;
	}

	constexpr T &&operator--(int) const && {
		return std::move(value);
	}

	constexpr bool has_value() const {
		return valid;
	}

	constexpr T &get_value() & {
		return value;
	}

	constexpr T &&get_value() && {
		return std::move(value);
	}

	constexpr const T &get_value() const & {
		return value;
	}

	constexpr const T &&get_value() const && {
		return std::move(value);
	}

	constexpr T *operator->() noexcept {
		return &value;
	}

	constexpr const T *operator->() const noexcept {
		return &value;
	}

	constexpr T& operator*() & noexcept {
		return value;
	}

	constexpr const T& operator*() const& noexcept {
		return value;
	}

	constexpr T&& operator*() && noexcept {
		return value;
	}

	constexpr const T&& operator*() const&& noexcept {
		return value;
	}

	template<class U>
	constexpr T value_or(U &&default_value) const& {
		return valid ? value : default_value;
	}

	template<class U>
	constexpr T value_or(U&& default_value ) && {
		return valid ? value : default_value;
	}
};

template<class T>
class Optional<T&> {
private:
	T &value;
	bool valid;

	constexpr T &__get_null_value__() {
		T *_t = nullptr;
		T **_b = &_t;
		T &_g = *(*_b);
		return _g;
	}
public:
	constexpr Optional(): value(__get_null_value__()), valid(false) {
	}

	constexpr Optional(T &value): value(value), valid(true) {
	}

	constexpr Optional(T &&value): value(value), valid(true) {
	}

	constexpr Optional(const NullOptionT&): value(__get_null_value__()), valid(false) {
	}

	constexpr operator bool() const {
		return valid;
	}

	constexpr void operator=(const NullOptionT&) noexcept {
		valid = false;
	}

	constexpr void operator=(const Optional &other) noexcept {
		value = other.value;
		valid = other.valid;
	}

	constexpr void operator=(Optional &&other) noexcept {
		value = other.value;
		valid = other.valid;
	}

	template<class U = T>
	constexpr void operator=(U &&value) {
		this->value = std::move(value);
		valid = true;
	}

	template<class U = T>
	constexpr void operator=(const Optional<U> &other) {
		value = other.value;
		valid = other.valid;
	}

	template<class U = T>
	constexpr void operator=(Optional<U> &&other) {
		value = std::move(other.value);
		valid = other.valid;
	}

	constexpr T &operator--(int) const & {
		return value;
	}

	constexpr T &&operator--(int) const && {
		return std::move(value);
	}

	constexpr bool has_value() const {
		return valid;
	}

	constexpr T &get_value() & {
		return value;
	}

	constexpr T &&get_value() && {
		return std::move(value);
	}

	constexpr const T &get_value() const & {
		return value;
	}

	constexpr const T &&get_value() const && {
		return std::move(value);
	}

	constexpr T *operator->() noexcept {
		return &value;
	}

	constexpr const T *operator->() const noexcept {
		return &value;
	}

	constexpr T& operator*() & noexcept {
		return value;
	}

	constexpr const T& operator*() const& noexcept {
		return value;
	}

	constexpr T&& operator*() && noexcept {
		return value;
	}

	constexpr const T&& operator*() const&& noexcept {
		return value;
	}

	template<class U>
	constexpr T &value_or(U &&default_value) const& {
		if (valid)
			return value;
		return default_value;
	}

	template<class U>
	constexpr T &value_or(U&& default_value ) && {
		return valid ? value : default_value;
	}
};

template<class T>
class Optional<T&&> {
private:
	T &&value;
	bool valid;

	constexpr T &&__get_null_value__() {
		T *_t = nullptr;
		T **_b = &_t;
		T &&_g = std::move(*(*_b));
		return _g;
	}
public:
	constexpr Optional(): value(__get_null_value__()), valid(false) {
	}

	constexpr Optional(T &&value): value(std::move(value)), valid(true) {
	}

	constexpr Optional(const NullOptionT&): value(__get_null_value__()), valid(false) {
	}

	constexpr void operator=(const NullOptionT&) noexcept {
		valid = false;
	}

	constexpr void operator=(const Optional &other) noexcept {
		value = other.value;
		valid = other.valid;
	}

	constexpr void operator=(Optional &&other) noexcept {
		value = std::move(other.value);
		valid = other.valid;
	}

	template<class U = T>
	constexpr void operator=(U &&value) {
		this->value = std::move(value);
		valid = true;
	}

	template<class U = T>
	constexpr void operator=(const Optional<U> &other) {
		value = other.value;
		valid = other.valid;
	}

	template<class U = T>
	constexpr void operator=(Optional<U> &&other) {
		value = std::move(other.value);
		valid = other.valid;
	}

	constexpr T &operator--(int) const & {
		return value;
	}

	constexpr T &&operator--(int) const && {
		return std::move(value);
	}

	constexpr bool has_value() const {
		return valid;
	}

	constexpr operator bool() const {
		return valid;
	}

	constexpr T &get_value() & {
		return value;
	}

	constexpr T &&get_value() && {
		return std::move(value);
	}

	constexpr const T &get_value() const & {
		return value;
	}

	constexpr const T &&get_value() const && {
		return std::move(value);
	}

	constexpr T *operator->() noexcept {
		return &value;
	}

	constexpr const T *operator->() const noexcept {
		return &value;
	}

	constexpr T& operator*() & noexcept {
		return value;
	}

	constexpr const T& operator*() const & noexcept {
		return value;
	}

	constexpr T&& operator*() && noexcept {
		return value;
	}

	constexpr const T&& operator*() const && noexcept {
		return value;
	}

	template<class U>
	constexpr T value_or(U &&default_value) const & {
		return valid ? value : default_value;
	}

	template<class U>
	constexpr T value_or(U&& default_value ) && {
		return valid ? std::move(value) : default_value;
	}
};

}
