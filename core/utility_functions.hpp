/*  This file is part of the Toof Engine. */
/** @file utility_functions.hpp */
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

#include <core/math/math_defs.hpp>
#include <core/string/string_def.hpp>

#include <stringify/to_string.hpp>

#include <SDL_timer.h>

#include <iostream>

namespace Toof {

namespace UtilityFunctions {

/**
* @brief Returns the amount of time passed in seconds since the program started.
*/
inline double get_passed_time() {
	double time = SDL_GetTicks64();
	time *= 0.001;
	return time;
}

/**
* @brief Prints a new line character into the standard output.
*/
inline void print() {
	std::cout << '\n';
}

/**
* @brief Prints a new line character into the standard error output.
*/
inline void print_err() {
	std::cerr << '\n';
}

/**
* @brief Prints a new line character into the standard output.
*/
inline void prints() {
	std::cout << '\n';
}

/**
* @brief Prints a new line character into the standard error output.
*/
inline void prints_err() {
	std::cerr << '\n';
}

/**
* @brief Converts one or more arguments of any type into a string in the best way possible and prints it to the standard output.
*/
template<class... Args>
inline void print(Args&&... variants) {
	S_WRITE_INTO_STREAM(std::cout, variants..., '\n');
}

/**
* @brief Converts one or more arguments of any type into a string in the best way possible and prints it to the error output.
*/
template<class... Args>
inline void print_err(Args&&... variants) {
	S_WRITE_INTO_STREAM(std::cerr, variants..., '\n');
}


/**
* @brief Prints one or more arguments to the console with a space between each argument to the standard output.
*/
template<class... Args>
inline void prints(Args&&... variants) {
	S_WRITE_INTO_STREAMS(std::cout, variants..., '\n');
}

/**
* @brief Prints one or more arguments to the console with a space between each argument to the error output.
*/
template<class... Args>
inline void prints_err(const Args&... variants) {
	S_WRITE_INTO_STREAMS(std::cerr, variants..., '\n');
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
