#pragma once

#include <cstdint>

namespace sdl {

struct Vector2;
struct Rect2;
struct Transform2D;

#ifdef REAL_T_IS_DOUBLE
typedef double real_t;
#else
typedef float real_t;
#endif

#ifdef INT_IS_64BIT
typedef int64_t int_t;
typedef uint64_t uint_t;
#else
typedef int32_t int_t;
typedef uint32_t uint_t;
#endif

typedef uint_t uid;

namespace Math {

const real_t CMP_EPSILON = 0.0000000001;
const real_t PI = 3.1415926535897;
const real_t TAU = PI * 2.0;
const real_t DEGREES_RADIAN_SCALAR = 180.0 / PI;

real_t radians_to_degrees(const real_t rotation_radians);
real_t degrees_to_radians(const real_t rotation_degrees);

bool is_equal_approx(const real_t left, const real_t right);
bool is_equal_approx(const Vector2 &left, const Vector2 &right);
bool is_equal_approx(const Rect2 &left, const Rect2 &right);
bool is_equal_approx(const Transform2D &left, const Transform2D &right);
bool is_zero_approx(const real_t number);
bool is_zero_approx(const Vector2 &vector2);
bool is_zero_approx(const Rect2 &rect2);
bool is_zero_approx(const Transform2D &transform2d);

}

}
