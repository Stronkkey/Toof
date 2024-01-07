#pragma once

#include <core/math/math_defs.hpp>

#include <string>

namespace sdl {

struct Vector2;
struct Rect2;
struct Transform2D;

namespace UtilityFunctions {

real_t get_passed_time();

void print(const std::string &string);
void prints(const std::string &string);

}

}
