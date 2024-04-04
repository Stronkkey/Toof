#pragma once

#include <cstdint>

namespace sdl {

#ifdef REAL_T_IS_DOUBLE
using real = double;
#else
using real = float;
#endif

#ifdef INT_IS_64BIT
using natural = uint64_t;
using integer = int64_t;
#else
using natural = uint32_t;
using integer = int32_t;
#endif

#ifdef REAL_T_IS_DOUBLE
constexpr const bool REAL_IS_DOUBLE = true;
#else
constexpr const bool REAL_IS_DOUBLE = false;
#endif

#ifdef INT_IS_64BIT
constexpr const bool INTEGER_IS_64BIT = true;
#else
constexpr const bool INTEGER_IS_64BIT = false;
#endif

using uid = natural;

namespace Math {

// An EPSILON constant. Which can be used to compare 2 floating point numbers.
constexpr const double CMP_EPSILON = 0.0000000001;
// A PI constant (3.141592). A ration of circle's circumference to its diameter and amount of radians in half turn.
constexpr const double PI = 3.1415926535897932384626433833;
// A TAU constant (6.283185). An equivalent of PI * 2 and amount of radians in full turn.
constexpr const double TAU = PI * 2.0;
// The ratio between one degree and one radian.
constexpr const double DEGREES_RADIAN_SCALAR = 180.0 / PI;

}

}
