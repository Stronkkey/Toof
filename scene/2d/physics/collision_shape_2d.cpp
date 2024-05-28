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
#include <scene/2d/physics/collision_shape_2d.hpp>

#if TOOF_PHYSICS_ENABLED

using namespace Toof;

CollisionShape2D::CollisionShape2D() : draw_color(ColorV::WHITE()), disabled(false), shape(nullptr) {
}

void CollisionShape2D::set_draw_color(const ColorV &draw_color) {
	if (this->draw_color == draw_color)
		return;

	this->draw_color = draw_color;
	queue_redraw();
}

void CollisionShape2D::set_disabled(bool disabled) {
	if (this->disabled == disabled)
		return;

	this->disabled = disabled;
	queue_redraw();
}

void CollisionShape2D::set_shape(Shape2D *shape) {
	if (this->shape == shape)
		return;

	Optional<PhysicsServer2D*> physics_server_2d = get_physics_server_2d();

	this->shape = shape;
	shape->set_physics_server_2d(physics_server_2d.value_or(nullptr));
}

#endif
