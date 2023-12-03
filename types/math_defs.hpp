#ifndef MATH_DEFS
#define MATH_DEFS

#include <cstdint>

namespace sdl {

#ifdef REAL_T_IS_DOUBLE
typedef double real_t;
#pragma message("DOUBLE")
#else
typedef float real_t;
#pragma message("FLOAT")
#endif

#ifdef INT_IS_64BIT
typedef int64_t int_t;
typedef uint64_t uint_t;
#pragma message("64BIT")
#else
typedef int32_t int_t;
typedef uint32_t uint_t;
#pragma message("32BIT")
#endif

}

#endif // !MATH_DEFS
