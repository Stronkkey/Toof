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
#include <scene/resources/physics/rectangle_shape_2d.hpp>
#include <servers/physics_server_2d.hpp>
#include <servers/rendering_server.hpp>

#if TOOF_PHYSICS_ENABLED

using namespace Toof;

void RectangleShape2D::_update() {
	PhysicsServer2D *physics_server_2d = get_physics_server_2d();
	if (physics_server_2d) {
	}
}

void RectangleShape2D::_draw(RenderingServer *rendering_server, uid canvas_item, const ColorV &modulation) const {
	rendering_server->canvas_item_add_rect(canvas_item, Rect2f({}, size), modulation);
}

uid RectangleShape2D::_create_shape() const {
	return get_physics_server_2d()->rect_shape_create(size);
}

RectangleShape2D::RectangleShape2D() : size(Vector2f(20, 20)) {
}

void RectangleShape2D::set_size(const Vector2f &size) {
	this->size = size;
	_update();
}

#endif