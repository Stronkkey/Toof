/*  This file is part of the Toof Engine. */
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
#include <core/string/string_name.hpp>

using String = Toof::String;
using StringName = Toof::StringName;

std::unordered_set<StringName::__String_Storer__> StringName::stored_strings = {};

StringName::StringName(): saved_string(_allocate_string("")) {
	saved_string.increment();
}

StringName::StringName(const CharT *string): saved_string(_allocate_string(string)) {
	saved_string.increment();
}

StringName::StringName(const_reference string): saved_string(_allocate_string(string)) {
	saved_string.increment();
}

StringName::~StringName() {
	_reset();
}

void StringName::_set_string(const_reference string, const bool copy) {
	if (saved_string == string)
		return;

	_reset();
	saved_string = _allocate_string(string, copy);
	saved_string.increment();
}

void StringName::_set_string(const CharT *string, const bool copy) {
	if ((get_string()) == string)
		return;

	_reset();
	saved_string = _allocate_string(string, copy);
	saved_string.increment();
}

void StringName::_reset() {
	if (!saved_string.stored_string)
		return;

	if (saved_string.is_used())
		saved_string.decrement();
	else
		return;

	if (!saved_string.is_used()) {
		saved_string.delete_stored_string();
		stored_strings.erase(*saved_string.stored_string);
	}
}

const StringName::__String_Storer__ *StringName::_allocate_str(const CharT *string, const bool copy) const {
	__String_Storer__ storer = string;

	auto iterator = stored_strings.find(storer);
	if (iterator != stored_strings.end())
		return &*iterator;

	if (copy) {
		const StringView::size_type str_size = storer.view.size();
		char *str_copy = new char[str_size];

		storer.view.copy(str_copy, str_size);
		str_copy[str_size] = '\0';
		storer = str_copy;
	}

	return &*stored_strings.insert(storer).first;
}

const StringName::__String_Storer__ *StringName::_allocate_str(const_reference string, const bool copy) const {
	__String_Storer__ storer;
	storer.string = string.data();
	storer.uses = 0;
	storer.view = string;

	auto iterator = stored_strings.find(storer);
	if (iterator != stored_strings.end())
		return &*iterator;

	if (copy) {
		const StringView::size_type str_size = storer.view.size();
		char *str_copy = new char[str_size];

		storer.view.copy(str_copy, str_size);
		str_copy[str_size] = '\0';
		storer = str_copy;
	}

	return &*stored_strings.insert(storer).first;
}

const StringName::__String_Storer__ *StringName::_allocate_string(const_reference string, const bool copy) const {
	return _allocate_str(string, copy);
}

const StringName::__String_Storer__ *StringName::_allocate_string(const CharT *string, const bool copy) const {
	return _allocate_str(string, copy);
}

std::pair<const char*, size_t> _concat_string(StringName::const_reference view1, StringName::const_reference view2) {
	const size_t str_size = view1.size() + view2.size() + 1;
	char *string = new char[str_size];
	
	size_t i = 0;

	for (const StringName::CharT &character: view1) {
		string[i] = character;
		i++;
	}

	for (const StringName::CharT &character: view2) {
		string[i] = character;
		i++;
	}

	string[str_size - 1] = '\0';

	return {string, str_size};
}

StringName::operator String() const {
	return String(get_string());
}

void StringName::remove_prefix(const size_type n) {
	value_type str = get_string();
	str.remove_prefix(n);
	_set_string(std::move(str));
}

void StringName::remove_suffix(const size_type n) {
	value_type str = get_string();
	str.remove_suffix(n);
	_set_string(std::move(str));
}

StringName::size_type StringName::copy(CharT *dest, const size_type pos, const size_type count) const {
	return saved_string->copy(dest, count, pos);
}

StringName StringName::substr(const size_type pos, const size_type count) const {
	return saved_string->substr(pos, count);
}

void StringName::operator=(const_reference string) {
	_set_string(string);
}

void StringName::operator+=(const_reference string) {
	const auto &pair = _concat_string(get_string(), string);
	_set_string(pair.first, false);
}

void StringName::operator+=(const StringName &string_name) {
	const auto &pair = _concat_string(get_string(), string_name.get_string());
	_set_string(pair.first, false);
}

StringName StringName::operator+(const_reference string) const {
	StringName string_name;
	const auto &pair = _concat_string(get_string(), string);
	string_name._set_string(pair.first, false);
	return string_name;
}

StringName StringName::operator+(const StringName &string_name) const {
	StringName string_name_v;
	const auto &pair = _concat_string(get_string(), *string_name.saved_string);
	string_name_v._set_string(pair.first, false);
	return string_name_v;
}

StringName::__os_type__ &operator<<(StringName::__os_type__ &left, const StringName &right) {
	return (left << right.get_string());
}
