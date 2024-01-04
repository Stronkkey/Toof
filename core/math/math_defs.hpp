#pragma once

#include <cstdint>

namespace sdl {

const double PI = 3.1415926535897;
const double TAU = PI * 2.0;

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

}
