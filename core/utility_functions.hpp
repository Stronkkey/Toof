#pragma once

#include <core/math/math_defs.hpp>
#include <core/string/string_def.hpp>

#include <stringify/to_string.hpp>

#include <SDL_timer.h>

#include <iostream>

namespace Toof {

namespace UtilityFunctions {

/**
* @returns the amount of time passed in seconds since the program started.
*/
inline double get_passed_time() {
	double time = SDL_GetTicks64();
	time *= 0.001;
	return time;
}

/**
* Prints a new line character into the standard output.
*/
inline void print() {
	std::cout << '\n';
}

/**
* Prints a new line character into the standard error output.
*/
inline void print_err() {
	std::cerr << '\n';
}

/**
* Prints a new line character into the standard output.
*/
inline void prints() {
	std::cout << '\n';
}

/**
* Prints a new line character into the standard error output.
*/
inline void prints_err() {
	std::cerr << '\n';
}

/**
* Converts one or more arguments of any type into a string in the best way possible and prints it to the standard output.
*/
template<class... Args>
inline void print(Args&&... variants) {
	std::cout << S_TO_STRING(variants...) << '\n';
}

/**
* Converts one or more arguments of any type into a string in the best way possible and prints it to the error output.
*/
template<class... Args>
inline void print_err(Args&&... variants) {
	std::cerr << S_TO_STRING(variants...) << '\n';
}


/**
* Prints one or more arguments to the console with a space between each argument to the standard output.
*/
template<class... Args>
inline void prints(Args&&... variants) {
	std::cout << S_TO_STRINGS(variants...) << '\n';
}

/**
* Prints one or more arguments to the console with a space between each argument to the error output.
*/
template<class... Args>
inline void prints_err(const Args&... variants) {
	std::cerr << S_TO_STRINGS(variants...) << '\n';
}

enum TextModifier {
	TEXT_MODIFIER_NONE = 0,
	TEXT_MODIFIER_BOLD = 1,
	TEXT_MODIFIER_CURSIVE = 2,
	TEXT_MODIFIER_UNDERLINED = 4,
	TEXT_MODIFIER_BLINKING = 5,
	TEXT_MODIFIER_REVERSE_VIDEO = 7,
	TEXT_MODIFIER_CUT_THROUGH = 9,
	TEXT_MODIFIER_COLOR_BLACK = 30,
	TEXT_MODIFIER_COLOR_RED = 31,
	TEXT_MODIFIER_COLOR_GREEN = 32,
	TEXT_MODIFIER_COLOR_BROWN = 33,
	TEXT_MODIFIER_COLOR_BLUE = 34,
	TEXT_MODIFIER_COLOR_PURPLE = 35,
	TEXT_MODIFIER_COLOR_CYAN = 36,
	TEXT_MODIFIER_COLOR_WHITE = 37,
};

constexpr StringView text_modifier_to_string_view(TextModifier text_modifier) {
	switch (text_modifier) {
		case TEXT_MODIFIER_NONE:
			return "0";
		case TEXT_MODIFIER_BOLD:
			return "1";
		case TEXT_MODIFIER_CURSIVE:
			return "2";
		case TEXT_MODIFIER_UNDERLINED:
			return "4";
		case TEXT_MODIFIER_BLINKING:
			return "5";
		case TEXT_MODIFIER_REVERSE_VIDEO:
			return "7";
		case TEXT_MODIFIER_CUT_THROUGH:
			return "9";
		case TEXT_MODIFIER_COLOR_BLACK:
			return "30";
		case TEXT_MODIFIER_COLOR_RED:
			return "31";
		case TEXT_MODIFIER_COLOR_GREEN:
			return "32";
		case TEXT_MODIFIER_COLOR_BROWN:
			return "33";
		case TEXT_MODIFIER_COLOR_BLUE:
			return "34";
		case TEXT_MODIFIER_COLOR_PURPLE:
			return "35";
		case TEXT_MODIFIER_COLOR_CYAN:
			return "36";
		case TEXT_MODIFIER_COLOR_WHITE:
			return "37";
		default:
			return "0";
	}
}

void start_text_modifier(String &string, TextModifier text_modifier);
void escape_string_text_modifier(String &string);
void apply_text_modifier_on_string(String &string, TextModifier text_modifier);

void apply_text_modifiers_on_string(String &string);

template<class... Args>
void apply_text_modifiers_on_string(String &string, Args... text_modifiers) {
	constexpr const size_t args_count = sizeof...(Args);

	TextModifier text_modifier_array[args_count] = {text_modifiers...};
	String temp = std::move(string);
	string = "\x1b[";

	for (size_t i = 0; i < args_count; i++) {
		StringView text_modifier_string = text_modifier_to_string_view(text_modifier_array[i]);

		bool is_last_element = ((i + 1) == args_count);
		if (!is_last_element)
			(string += text_modifier_string) += ';';
		else
			string += text_modifier_string;
	}

	string += 'm';

	String::size_type after_string_size = string.size() + temp.size();
	String::size_type prev_str_size = string.size();
	string.resize(string.size() + temp.size() + 4);

	memmove(string.data() + prev_str_size, temp.data(), temp.length());

	string[after_string_size] = '\x1b';
	string[after_string_size + 1] = '[';
	string[after_string_size + 2] = '0';
	string[after_string_size + 3] = 'm';
}

#define PRINT_LINE(...) ::Toof::UtilityFunctions::print(__VA_ARGS__);
#define PRINT_LINE_ERR(...) ::Toof::UtilityFunctions::print_err(__VA_ARGS__);
#define PRINTS_LINE(...) ::Toof::UtilityFunctions::prints(__VA_ARGS__);
#define PRINTS_LINE_ERR(...) ::Toof::UtilityFunctions::prints_err(__VA_ARGS__);

}

}
