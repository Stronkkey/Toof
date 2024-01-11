#pragma once

#include <core/math/math_defs.hpp>

#include <string>

namespace sdl {

namespace UtilityFunctions {

/**
* Returns the amount of time passed in seconds since the program started.
*/
real_t get_passed_time();

/**
* Prints the @param string to the standard output.
*/
void print(const std::string &string);

/**
* Prints the @param string to the standard error output.
*/
void print_err(const std::string &string);

}

}
