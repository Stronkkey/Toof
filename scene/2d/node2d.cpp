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
#include <scene/2d/node2d.hpp>
#include <servers/rendering/window.hpp>
#include <scene/main/scene_tree.hpp>
#include <scene/resources/texture2d.hpp>

using namespace Toof;

void Node2D::set_scale(const Vector2f &new_scale) {
	transform.scale = new_scale;
	queue_redraw();
}

void Node2D::set_rotation(const Angle new_rotation) {
	transform.rotation = new_rotation;
	queue_redraw();
}

void Node2D::set_position(const Vector2f &position) {
	transform.origin = position;
	queue_redraw();
}

void Node2D::set_global_position(const Vector2f &new_global_position) {
	Vector2 global_position = get_global_position();
	transform.origin = -Vector2(global_position - new_global_position);
	queue_redraw();
}

const Vector2f Node2D::get_global_position() const {
	return get_global_transform().origin;
}

void Node2D::set_global_scale(const Vector2f &new_global_scale) {
	Vector2 global_scale = get_global_scale();
	transform.scale = -Vector2(global_scale - new_global_scale);
	queue_redraw();
}

const Vector2f Node2D::get_global_scale() const {
	return get_global_transform().scale;
}

void Node2D::set_global_rotation(const Angle new_global_rotation) {
	Angle global_rotation = get_global_rotation();
	transform.rotation = -(global_rotation - new_global_rotation);
}

Angle Node2D::get_global_rotation() const {
	return get_global_transform().rotation;
}

void Node2D::set_transform(const Transform2D &new_transform) {
	transform = new_transform;
	queue_redraw();
}

Transform2D Node2D::get_transform() const {
	return transform;
}

void Node2D::set_global_transform(const Transform2D &new_global_transform) {
	const Transform2D global_transform = get_global_transform();
	Transform2D new_transform = new_global_transform;

	transform.origin = -(global_transform.origin - new_global_transform.origin);
	transform.rotation = -(global_transform.rotation - new_transform.rotation);
	transform.scale = -(global_transform.scale - new_transform.scale);
	queue_redraw();
}
