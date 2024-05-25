/*  This file is part of the Toof Engine. */
/** @file transform2d_hash.hpp
    @brief Specialization of @b std::hash for @b Transform2D. */
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

#include <core/math/transform2d.hpp>

#include <functional>

template<>
struct std::hash<Toof::Transform2D> {
	size_t operator()(const Toof::Transform2D &transform2d) const noexcept {
		const size_t x_hash = std::hash<Toof::real>()(transform2d.origin.x);
		const size_t y_hash = std::hash<Toof::real>()(transform2d.origin.y);
		const size_t w_hash = std::hash<Toof::real>()(transform2d.scale.x);
		const size_t h_hash = std::hash<Toof::real>()(transform2d.scale.y);
		const size_t angle_hash = std::hash<Toof::real>()(transform2d.rotation.get_angle_degrees());
		return angle_hash ^ (((w_hash ^ (h_hash << 1)) ^ ((x_hash ^ (y_hash << 1)) << 1)) << 1);
	}
};