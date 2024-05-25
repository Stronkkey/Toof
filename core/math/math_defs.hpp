/*  This file is part of the Toof Engine. */
/** @file math_defs.hpp */
/*
  BSD 3-Clause License

  Copyright (c) 2024-present, Stronkkey and Contributors

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
      list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#pragma once

#include <cstdint>

namespace Toof {

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
