/*  This file is part of the Toof Engine. */
/** @file optional.hpp */
/*
  BSD 3-Clause License

  Copyright (c) 2024-present, Stronkkey and Contributors

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
      list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#pragma once

#include <algorithm>

namespace Toof {

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
