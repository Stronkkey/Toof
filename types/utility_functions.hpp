#pragma once

#include <types/math_defs.hpp>

#include <string>

namespace sdl {

struct Vector2;
struct Rect2;
struct Transform2D;

namespace UtilityFunctions {

const real_t EPSILON = 0.0000000001;

real_t get_passed_time();

void print(const std::string &string);
void prints(const std::string &string);

bool is_equal_approx(const real_t left, const real_t right);
bool is_equal_approx(const Vector2 &left, const Vector2 &right);
bool is_equal_approx(const Rect2 &left, const Rect2 &right);
bool is_equal_approx(const Transform2D &left, const Transform2D &right);

}

}
