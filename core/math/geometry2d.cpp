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
#include <core/math/geometry2d.hpp>
#include <core/math/rect2.hpp>

bool Toof::Geometry2D::rect_intersects_circle(const Rect2f &rect, const real circle_radius, const Vector2f &circle_position) {
	const real circle_radius_squared = circle_radius * circle_radius;
	const bool position_intersection = circle_position.distance_to_squared(rect.get_position()) <= circle_radius_squared;
	const bool size_intersection = circle_position.distance_to_squared(rect.get_position() + rect.get_size()) <= circle_radius_squared;
	return position_intersection || size_intersection;
}

Toof::Vector2f Toof::Geometry2D::rotate_point_around(const double rotation_degrees, const Vector2f &point)  {
	real rotation_radians = Math::degrees_to_radians(rotation_degrees);
	real x_rot = -(point.x * cos(rotation_radians)) + (point.y * cos(rotation_radians));
	real y_rot = -(point.x * sin(rotation_radians)) + (point.y * sin(rotation_radians));
	
	return Vector2f(x_rot, y_rot);
}