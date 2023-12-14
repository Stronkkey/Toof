#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H

#include <types/math_defs.hpp>

#include <string>
#include <vector>
#include <SDL_timer.h>

namespace sdl {

namespace UtilityFunctions {

real_t get_passed_time();

void print(const std::string &string);
void print(const std::vector<std::string> &strings);
void prints(const std::string &string);
void prints(const std::vector<std::string> &strings);

}
}

#endif // !UTILITY_FUNCTIONS_H
