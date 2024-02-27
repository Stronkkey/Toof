#pragma once

#include <core/string_def.hpp>

#include <cstdint>
#include <iomanip>
#include <typeinfo>
#include <array>
#include <vector>

namespace sdl {

namespace StringFuncs {

/**
* @returns the @param number converted to a string using std::to_string.
*/
[[nodiscard]] String to_string(const uint8_t number);

/**
* @returns the @param number converted to a string using std::to_string.
*/
[[nodiscard]] String to_string(const int8_t number);

/**
* @returns the @param number converted to a string using std::to_string.
*/
[[nodiscard]] String to_string(const uint16_t number);

/**
* @returns the @param number converted to a string using std::to_string.
*/
[[nodiscard]] String to_string(const int16_t number);

/**
* @returns the @param number converted to a string using std::to_string.
*/
[[nodiscard]] String to_string(const uint32_t number);

/**
* @returns the @param number converted to a string using std::to_string.
*/
[[nodiscard]] String to_string(const int32_t number);

/**
* @returns the @param number converted to a string using std::to_string.
*/
[[nodiscard]] String to_string(const uint64_t number);

/**
* @returns the @param number converted to a string using std::to_string.
*/
[[nodiscard]] String to_string(const int64_t number);

/**
* @returns the @param number converted to a string using std::to_string.
*/
[[nodiscard]] String to_string(const float number);

/**
* @returns the @param number converted to a string using std::to_string.
*/
[[nodiscard]] String to_string(const double number);

/**
* @returns the @param number converted to a string using std::to_string.
*/
[[nodiscard]] String to_string(const long double number);

/**
* @returns the "true" if boolean is true, otherwise, "false" is returned.
*/
[[nodiscard]] String to_string(const bool boolean);

/**
* @returns the string pointer converted to a String type.
*/
[[nodiscard]] String to_string(const char *string);

/**
* @returns @param string.
*/
[[nodiscard]] String to_string(const String &string);

/**
* @returns a string with the character being the only character (except the NULL byte).
*/
[[nodiscard]] String to_string(const char character);

template<class T>
[[nodiscard]] constexpr bool is_string_type() {
	constexpr const auto &type_info = typeid(T);
	return type_info == typeid(String)
	|| type_info == typeid(char)
	|| type_info == typeid(char*)
	|| type_info == typeid(const char)
	|| type_info == typeid(const char*);
}

/**
* Splits the @param string using a @param delimiter and returns an array of the substrings.
*/
[[nodiscard]] std::vector<String> split_string(const StringView &string_view, const String &delimiter);

/**
* @returns the amount of occurences of @param characters in the @param string_view.
*/
[[nodiscard]] size_t get_occurences_in_string(const StringView &string_view, const StringView &characters);

[[nodiscard]] inline String __quoted_str(const String &str, const char delimiter = '\"') {
	return delimiter + str + delimiter;
}

/**
* @returns a string with both value pairs as strings.
*/
template<class T1, class T2>
[[nodiscard]] inline String to_string(const std::pair<T1, T2> &pair) {
	const std::string &p1_str = is_string_type<T1>() ? __quoted_str(to_string(pair.first)) : to_string(pair.first);
	const std::string &p2_str =	is_string_type<T2>() ? __quoted_str(to_string(pair.second)) : to_string(pair.second);
	return "{" + p1_str + ", " + p2_str + "}";
}

/**
* @brief generic to_string.
* @returns the @param variant converted to a string in the best possible way.
*/
template<class T>
[[nodiscard]] inline String to_string(const T &variant) {
	if (std::is_pointer<T>().value)
		return "Pointer at \"" + std::to_string((uintptr_t)&variant) + "\" to type \"" + typeid(T).name() + "\"";

	return "{}";
}

/**
* @returns the parameters converted to a string in the best possible way.
*/
template<class T, class... Args>
[[nodiscard]] inline String to_string(const T &variant, const Args&... args) {
	return (to_string(variant) + to_string(args...));
}

template<size_t _size, class T>
inline void _add_str(std::array<String, _size> &arr, size_t i, const T &t) {
	if (i < _size)
		arr[i] = to_string(t);
}

template<size_t _size, class T, class... Args>
inline void _add_str(std::array<String, _size> &arr, size_t i, const T &t, const Args&... args) {
	_add_str(arr, i, t);
	_add_str(arr, i + 1, args...);
}

/**
* @returns
*/
template<class... Args>
[[nodiscard]] inline std::array<String, sizeof...(Args)> to_string_array(const Args&... args) {
	constexpr const size_t arg_count = sizeof...(Args);
	std::array<String, arg_count> arr;
	_add_str(arr, 0, args...);
	return arr;
}

/**
* @returns the @param variant converted to a string using to_string, with a space at the end.
*/
template<class T>
[[nodiscard]] inline String to_strings(const T &variant) {
	return to_string(variant) + ' ';
}

/**
* @returns the parameters converted to a string in the best possible way with a space between the parameters.
*/
template<class T, class... Args>
[[nodiscard]] inline String to_strings(const T &variant, const Args&... args) {
	return (to_strings(variant) + to_strings(args...));
}

/**
* @returns a formatted stirng.
*/
template<class... Args>
[[nodiscard]] inline String vformat(const String &string, const Args&... args) {
	constexpr const size_t arg_count = sizeof...(Args);
	constexpr const char format_str[] = "{}";
	constexpr const size_t format_str_length = sizeof(format_str) - 1;
	const std::array<String, arg_count> &array = to_string_array(args...);

	uint64_t pos;
	size_t i = 0;
	String str = string;
	std::vector<String> strings;

	while ((pos = str.find("{}")) != String::npos) {
		strings.push_back(str.substr(0, pos));

		if (i < arg_count) {
			strings.push_back(array[i]);
			i++;
		}

		str.erase(0, pos + format_str_length);
	}

	strings.push_back(str);
	str.clear();
	for (const auto &string: strings)
		str += string;

	return str;
}

}

}