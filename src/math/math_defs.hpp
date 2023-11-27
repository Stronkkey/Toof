#ifndef MATH_DEFS
#define MATH_DEFS

#include <cstdint>

namespace sdl {

#ifdef INT_T_IS_64BIT
typedef int64_t int_t;
#else
typedef int32_t int_t;
#endif

#ifdef NATURAL_T_IS_64BIT
typedef uint64_t natural_t;
#else
typedef uint32_t uint_t;
#endif

#ifdef REAL_T_IS_DOUBLE
typedef double real_t;
#else
typedef float real_t;
#endif

}

#endif // !MATH_DEFS
