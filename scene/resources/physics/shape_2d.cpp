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
#include <scene/resources/physics/shape_2d.hpp>
#include <servers/physics_server_2d.hpp>

#if TOOF_PHYSICS_ENABLED

using namespace Toof;

uid Shape2D::_get_uid() const {
	return shape_uid;
}

void Shape2D::_draw(RenderingServer*, uid, const ColorV&) const {
}

Shape2D::Shape2D() : shape_uid(0),
    physics_server_2d(nullptr) {
}

void Shape2D::draw(RenderingServer *rendering_server, uid canvas_item, const ColorV &modulation) const {
	_draw(rendering_server, canvas_item, modulation);
}

void Shape2D::set_physics_server_2d(PhysicsServer2D *physics_server_2d) {
	if (this->physics_server_2d)
		this->physics_server_2d->free_uid(shape_uid);
	this->physics_server_2d = physics_server_2d;

	if (physics_server_2d)
		shape_uid = _create_shape();
	else
		shape_uid = 0;
}

#endif
