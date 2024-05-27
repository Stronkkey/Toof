/*  This file is part of the Toof Engine. */
/** @file physics_info.hpp */
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
#ifdef TOOF_PHYSICS_ENABLED

#pragma once

#ifndef __PHYSICS_PX_METER_RATIO__
#define __PHYSICS_PX_METER_RATIO__ 100
#endif

#ifndef __DEFAULT_GRAVITY_X__
#define __DEFAULT_GRAVITY_X__ 0
#endif

#ifndef __DEFAULT_GRAVITY_Y__
#define __DEFAULT_GRAVITY_Y__ 9.8
#endif

#include <ratio>

#include <core/math/vector2.hpp>

namespace Toof {

namespace Physics {

const Vector2f default_gravity = Vector2f(__DEFAULT_GRAVITY_X__, __DEFAULT_GRAVITY_Y__);
const std::ratio px_to_meter_ratio = std::ratio<1, __PHYSICS_PX_METER_RATIO__>();
#ifdef TOOF_PHYSICS_ENABLED
const bool physics_enabled = true;
#else
const bool physics_enabled = false;
#endif

}

}

#endif // !TOOF_PHYSICS_ENABLED