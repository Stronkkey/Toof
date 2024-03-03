#pragma once

#include <core/math/math_defs.hpp>
#include <core/string_funcs.hpp>

#include <SDL_timer.h>

#include <iostream>

namespace sdl {

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
* Converts one or more arguments of any type into a string in the best way possible and prints it to the standard output.
*/
template<class... Args>
inline void print(const Args&... variants) {
	std::cout << to_string(variants...) << '\n';
}

/**
* Converts one or more arguments of any type into a string in the best way possible and prints it to the error output.
*/
template<class... Args>
inline void print_err(const Args&... variants) {
	std::cerr << to_string(variants...) << '\n';
}


/**
* Prints one or more arguments to the console with a space between each argument to the standard output.
*/
template<class... Args>
inline void prints(const Args&... variants) {
	std::cout << to_strings(variants...) << '\n';
}

/**
* Prints one or more arguments to the console with a space between each argument to the error output.
*/
template<class... Args>
inline void prints_err(const Args&... variants) {
	std::cerr << to_strings(variants...) << '\n';
}

template<class T>
constexpr uintptr_t uintptr_address(const T *t) {
	return (uintptr_t)t;
}

#define PRINT_LINE(...) ::sdl::UtilityFunctions::print(__VA_ARGS__);
#define PRINT_LINE_ERR(...) ::sdl::UtilityFunctions::print_err(__VA_ARGS__);
#define PRINTS_LINE(...) ::sdl::UtilityFunctions::prints(__VA_ARGS__);
#define PRINTS_LINE_ERR(...) ::sdl::UtilityFunctions::prints_err(__VA_ARGS__);
#define UINTPTR_ADDRESS(name) ::sdl::UtilityFunctions::uintptr_address(name)

}

}
