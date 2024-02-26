#pragma once

#ifndef CUSTOM_STRING_TYPE
#include <string>
#define CUSTOM_STRING_TYPE std::string
#endif

#include <cstdint>
#include <typeinfo>

namespace sdl {

typedef CUSTOM_STRING_TYPE String;

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

/**
* @returns a string with both value pairs as strings.
*/
template<class T1, class T2>
[[nodiscard]] String to_string(const std::pair<T1, T2> &pair) {
	return "{" + to_string(pair.first) + ", " + to_string(pair.second) + "}";
}

/**
* @brief generic to_string.
* @returns the @param variant converted to a string in the best possible way.
*/
template<class T>
[[nodiscard]] inline String to_string(const T &variant) {
	if (std::is_pointer<T>().value)
		return "Pointer at \"" + std::to_string((uintptr_t)&variant) + "\" to type \"" + typeid(T).name() + "\"";

	return "";
}

/**
* @returns the parameters converted to a string in the best possible way.
*/
template<class T, class... Args>
[[nodiscard]] inline String to_string(const T &variant, const Args&... args) {
	return (to_string(variant) + to_string(args...));
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

}
