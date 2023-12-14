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

void UtilityFunctions::print(const std::vector<std::string> &strings) {
  std::string full_string;

  for (std::string string_strings: strings)
    full_string += string_strings;
  
  print(full_string);
}

void UtilityFunctions::prints(const std::string &string) {
  std::cout << string + "\n";
}

void UtilityFunctions::prints(const std::vector<std::string> &strings) {
  std::string full_string;

  for (std::string string_strings: strings)
    full_string += string_strings + " ";
  
  print(full_string);
}
