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

// An EPSILON constant. Which can be used to compare 2 floating point numbers.
constexpr const real_t CMP_EPSILON = 0.0000000001;
// A PI constant (3.141592). A ration of circle's circumference to its diameter and amount of radians in half turn.
constexpr const real_t PI = 3.1415926535897;
// A TAU constant (6.283185). An equivalent of PI * 2 and amount of radians in full turn.
constexpr const real_t TAU = PI * 2.0;
// The ratio between one degree and one radian.
constexpr const real_t DEGREES_RADIAN_SCALAR = 180.0 / PI;

/**
* @returns the @param rotation_degrees converted to degrees rotation. @see also DEGREES_RADIAN_SCALAR.
*/
constexpr real_t radians_to_degrees(const real_t rotation_radians) {
	return rotation_radians * DEGREES_RADIAN_SCALAR;
}

/**
* @returns the @param rotation_degrees converted to radians rotation. @see also DEGREES_RADIAN_SCALAR.
*/
constexpr real_t degrees_to_radians(const real_t rotation_degrees) {
	return rotation_degrees / DEGREES_RADIAN_SCALAR;
}

/**
* @returns true if @param left approximately equals @param right; 
*/
constexpr bool is_equal_approx(const real_t left, const real_t right) {
	return left >= (right - CMP_EPSILON) && left <= (right + CMP_EPSILON);
}

/**
* @returns true if @param left approximately equals @param right; 
*/
bool is_equal_approx(const Vector2 &left, const Vector2 &right);

/**
* @returns true if @param left approximately equals @param right; 
*/
bool is_equal_approx(const Rect2 &left, const Rect2 &right);

/**
* @returns true if @param left approximately equals @param right; 
*/
bool is_equal_approx(const Transform2D &left, const Transform2D &right);

/**
* @returns true if @param number is approximately equal to 0. 
*/
constexpr bool is_zero_approx(const real_t number) {
	return number >= (0.0 - CMP_EPSILON) && number <= (0.0 + CMP_EPSILON);
}

/**
* @returns true if the components of @param transform2d approximately equal to 0. 
*/
bool is_zero_approx(const Vector2 &vector2);

/**
* @returns true if the components of @param rect2 approximately equal to 0. 
*/
bool is_zero_approx(const Rect2 &rect2);

/**
* @returns true if the components of @param transform2d approximately equal to 0. 
*/
bool is_zero_approx(const Transform2D &transform2d);

}

}
