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
#include <scene/2d/sprite2d.hpp>
#include <scene/resources/texture2d.hpp>

using namespace Toof;

Sprite2D::Sprite2D(): texture(nullptr),
    texture_region(),
    texture_transform(Transform2D::IDENTITY),
    flip(SDL_FLIP_NONE),
    centered(true) {
}

Transform2D Sprite2D::_get_placement_texture_transform() const {
	Transform2D placement_texture_transform = texture_transform;
	if (centered) {
		const Vector2f texture_size = texture->get_size();
		placement_texture_transform.origin -= ((texture_size / 2.0) * texture_transform.scale);
	}

	return placement_texture_transform;
}

void Sprite2D::_draw_full_texture() const {
	texture->draw(texture->get_uid(), get_canvas_item(), flip, ColorV::WHITE(), _get_placement_texture_transform());
}

void Sprite2D::_draw_rect_texture() const {
	texture->draw_region(texture->get_uid(), get_canvas_item(), texture_region, flip, ColorV::WHITE(), _get_placement_texture_transform());
}

void Sprite2D::_draw_texture() const {
	Optional<RenderingServer*> rendering_server = get_rendering_server();
	if (!rendering_server || !texture)
		return;

	rendering_server.get_value()->canvas_item_clear(get_canvas_item());
	if (texture_region == Rect2i())
		_draw_full_texture();
	else
		_draw_rect_texture();
}

void Sprite2D::_notification(const int what) {
	Node2D::_notification(what);

	if (what == NOTIFICATION_DRAW)
		_draw_texture();

	if (what == NOTIFICATION_ENTER_TREE && texture)
		texture->set_rendering_server(get_rendering_server().get_value());

	if (what == NOTIFICATION_EXIT_TREE && texture)
		texture->set_rendering_server(nullptr);
}

void Sprite2D::set_texture(const std::shared_ptr<Texture2D> &new_texture) {
	texture = new_texture;

	if (texture && is_inside_tree())
		texture->set_rendering_server(get_rendering_server().get_value());

	texture_changed();
	queue_redraw();
}

void Sprite2D::set_texture_region(const Rect2i &new_texture_region) {
	texture_region = new_texture_region;
	queue_redraw();
}

void Sprite2D::set_offset(const Vector2f &new_offset) {
	texture_transform.origin = new_offset;
	queue_redraw();
}

void Sprite2D::set_flip(const SDL_RendererFlip new_flip) {
	flip = new_flip;
	queue_redraw();
}

void Sprite2D::set_texture_rotation(const Angle new_rotation) {
	texture_transform.rotation = new_rotation;
	queue_redraw();
}

void Sprite2D::set_texture_scale(const Vector2f &new_texture_scale) {
	texture_transform.scale = new_texture_scale;
	queue_redraw();
}

void Sprite2D::set_texture_transform(const Transform2D &new_texture_transform) {
	texture_transform = new_texture_transform;
	queue_redraw();
}

void Sprite2D::set_centered(const bool new_centered) {
	centered = new_centered;
	queue_redraw();
}
