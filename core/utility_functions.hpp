#pragma once

#include <core/math/math_defs.hpp>

#include <any>
#include <initializer_list>
#include <string>

namespace sdl {

namespace UtilityFunctions {

/**
* @returns the amount of time passed in seconds since the program started.
*/
real_t get_passed_time();

/**
* @returns the @param variant converted to a string in the best possible way.
*/
[[nodiscard]] std::string to_string(const std::any &variant);

/**
* Converts @param variant into a string in the best way possible and prints it to the standard output.
*/
void print(const std::any &variant = "");

/**
* Converts one or more arguments of any type into a string in the best way possible and prints it to the standard output.
*/
void print(const std::initializer_list<std::any> &variants);


/**
* Converts @param variant into a string in the best way possible and prints it to the error output.
*/
void print_err(const std::any &variant = "");

/**
* Converts one or more arguments of any type into a string in the best way possible and prints it to the error output.
*/
void print_err(const std::initializer_list<std::any> &variants);

/**
* Acts identical to print.
*/
void prints(const std::any &variant = "");

/**
* Prints one or more arguments to the console with a space between each argument to the standard output.
*/
void prints(const std::initializer_list<std::any> &variants);

/**
* Acts identical to print_err.
*/
void prints_err(const std::any &variant = "");

/**
* Prints one or more arguments to the console with a space between each argument to the error output.
*/
void prints_err(const std::initializer_list<std::any> &variants);

}

}
