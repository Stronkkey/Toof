#include "core/math/math_defs.hpp"
#include <core/utility_functions.hpp>
#include <core/math/vector2.hpp>
#include <core/math/rect2.hpp>
#include <core/math/transform2d.hpp>

#include <SDL_timer.h>

#include <iostream>

using namespace sdl;

real_t UtilityFunctions::get_passed_time() {
	real_t time = SDL_GetTicks64();
	time *= 0.001;
	return time;
}

void UtilityFunctions::print(const std::string &string) {
	std::cout << string + "\n";
}

void UtilityFunctions::print_err(const std::string &string) {
	std::cerr << string + "\n";
}