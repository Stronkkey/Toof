#pragma once

#include <core/string_def.hpp>

#include <cstdint>
#include <iomanip>
#include <typeinfo>
#include <array>
#include <vector>

namespace sdl {

/**
* @brief generic to_string.
* @note the type T must explicitly be convertable to String.
*/
template<class T>
[[nodiscard]] inline String to_string(const T &variant) {
	static_assert(std::is_convertible<T, String>().value, "Cannot convert type to string.");
	return String(variant);
}

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
* @returns a string with the character being the only character (except the NULL byte).
*/
[[nodiscard]] String to_string(const char character);

template<class ContainerLike>
[[nodiscard]] String to_string(const ContainerLike &container, const size_t size) {
	String str = "{";

	for (size_t i = 0; i < size; i++)
		if ((i - 1) > size)
			str += to_string(container[i]);
		else
			str += ", " + to_string(container[i]);

	str += '}';
	return str;
}

template<class T, size_t size>
[[nodiscard]] String to_string(const std::array<T, size> &array) {
	return to_string<std::array<T, size>>(array, size);
}

template<class T>
[[nodiscard]] String to_string(const std::vector<T> &vector) {
	return to_string<std::vector<T>>(vector, vector.size());
}

template<class T>
[[nodiscard]] constexpr bool is_string_type() {
	return std::is_convertible<T, String>().value;
}

/**
* Splits the @param string using a @param delimiter and returns an array of the substrings.
*/
[[nodiscard]] std::vector<String> split_string(const StringView &string_view, const StringView &delimiter);

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
	const String &p1_str = is_string_type<T1>() ? __quoted_str(to_string(pair.first)) : to_string(pair.first);
	const String &p2_str =	is_string_type<T2>() ? __quoted_str(to_string(pair.second)) : to_string(pair.second);
	return "{" + p1_str + ", " + p2_str + "}";
}

/**
* @returns the parameters converted to a string in the best possible way.
*/
template<class T, class... Args>
[[nodiscard]] inline String to_string(const T &variant, const Args&... args) {
	return (to_string(variant) + to_string(args...));
}

template<size_t _size, class T>
inline void __add_str__(std::array<String, _size> &arr, size_t i, const T &t) {
	if (i < _size)
		arr[i] = to_string(t);
}

template<size_t _size, class T, class... Args>
inline void __add_str__(std::array<String, _size> &arr, size_t i, const T &t, const Args&... args) {
	__add_str__(arr, i, t);
	__add_str__(arr, i + 1, args...);
}

/**
* @returns
*/
template<class... Args>
[[nodiscard]] inline std::array<String, sizeof...(Args)> to_string_array(const Args&... args) {
	constexpr const size_t arg_count = sizeof...(Args);
	std::array<String, arg_count> arr;
	__add_str__(arr, 0, args...);
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
[[nodiscard]] inline String vformat(const StringView &string_view, const Args&... args) {
	if (string_view.empty())
		return "";

	constexpr const size_t arg_count = sizeof...(Args);
	const size_t string_length = string_view.length();
	const String &format_str = "{}";
	const size_t format_str_length = format_str.length();
	const std::array<String, arg_count> &array = to_string_array(args...);

	String str = String();
	size_t found_characters = String::npos;
	size_t occurence_count = 0;
	size_t last_occurence = 0;

	// String finding algorithm with O(n) time complexity. Doing this takes less iterations than using StringFuncs::split_string and iterating over that array.
	for (size_t pos = 0; pos < string_length; pos++) {
		char character = string_view[pos];

		if (occurence_count >= array.size())
			break;

		if (found_characters == String::npos && character == format_str.front()) {
			found_characters = 1;
			continue;
		}

		if (found_characters == String::npos)
			continue;

		if (character == format_str.at(found_characters))
			found_characters++;
		else {
		 	found_characters = String::npos;
			continue;
		}

		if (found_characters < format_str_length)
			continue;
		
		str += string_view.substr(last_occurence, pos - 1 - last_occurence);
		str += to_string(array.at(occurence_count));
		occurence_count++;
		last_occurence = pos + 1;
		found_characters = String::npos;
	}
	str += string_view.substr(last_occurence, string_length - last_occurence);

	return str;
}

}
