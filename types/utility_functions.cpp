#include <cstdarg>
#include <types/utility_functions.hpp>

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

void UtilityFunctions::prints(const std::string &string) {
  std::cout << string + "\n";
}
