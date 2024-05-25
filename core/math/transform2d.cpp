/*  This file is part of the Toof Engine. */
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
#include <core/math/transform2d.hpp>

#ifdef B2_INCLUDED
#include <box2d/b2_math.h>
#endif

#include <core/string/string_def.hpp>
#include <stringify/format.hpp>

using namespace Toof;

const Transform2D Transform2D::IDENTITY = Transform2D(Angle::ZERO_ROTATION(), 0, 0, 1, 1);

#ifdef B2_INCLUDED

Transform2D::Transform2D(const b2Transform &b2_transform): rotation(Angle::from_radians(b2_transform.q.GetAngle())), origin(b2_transform.p), scale(Vector2(1, 1)) {
}

b2Transform Transform2D::to_b2_transform() const {
	return b2Transform(origin.to_b2_vec2(), b2Rot(rotation.get_angle_radians()));
}

#endif

std::ostream &Toof::operator<<(std::ostream &stream, const Transform2D &transform) {
	S_STREAM_FORMAT(stream, "[Scale: ({}, {}), Origin: ({}, {}), Rotation: {}]",
	    transform.scale.x,
	    transform.scale.y,
	    transform.origin.x,
	    transform.origin.y,
	    transform.rotation);
	return stream;
}

Transform2D::operator String() const {
	return S_FORMAT("[Scale: ({}, {}), Origin: ({}, {}), Rotation: {}]", scale.x, scale.y, origin.x, origin.y, rotation);
}
