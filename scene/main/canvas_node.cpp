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
#include <scene/main/canvas_node.hpp>
#include <scene/main/scene_tree.hpp>
#include <servers/rendering_server.hpp>

using namespace Toof;

void CanvasNode::_update() {
	Optional<RenderingServer*> rendering_server = get_rendering_server();
	update_queued = false;

	if (rendering_server) {
		rendering_server.get_value()->canvas_item_set_transform(canvas_item, get_transform());
		rendering_server.get_value()->canvas_item_set_modulate(canvas_item, modulation);
		rendering_server.get_value()->canvas_item_set_blend_mode(canvas_item, blend_mode);
		rendering_server.get_value()->canvas_item_set_scale_mode(canvas_item, scale_mode);
		rendering_server.get_value()->canvas_item_set_visible(canvas_item, visible);
		rendering_server.get_value()->canvas_item_set_zindex(canvas_item, zindex);
		rendering_server.get_value()->canvas_item_set_zindex_relative(canvas_item, zindex_relative);
	}
}

void CanvasNode::_on_parent_changed(Node *parent) {
	Optional<RenderingServer*> rendering_server = get_rendering_server();

	if (!rendering_server || !parent)
		return;

	CanvasNode *canvas_node = dynamic_cast<CanvasNode*>(parent);
	if (canvas_node)
		rendering_server.get_value()->canvas_item_set_parent(canvas_item, canvas_node->get_canvas_item());
}

void CanvasNode::_on_tree_enter() {
	Optional<RenderingServer*> rendering_server = get_rendering_server();

	if (rendering_server)
		canvas_item = rendering_server.get_value()->create_canvas_item();
}

void CanvasNode::_on_tree_exit() {
	Optional<RenderingServer*> rendering_server = get_rendering_server();

	if (rendering_server)
		rendering_server.get_value()->remove_uid(canvas_item);
}

Optional<RenderingServer*> CanvasNode::get_rendering_server() const {
	if (is_inside_tree())
		return get_tree()->get_rendering_server().get();
	return NullOption;
}

void CanvasNode::_notification(int what) {
	switch (what) {
		case NOTIFICATION_ENTER_TREE:
			queue_redraw();
			_on_tree_enter();
			break;
		case NOTIFICATION_EXIT_TREE:
			_on_tree_exit();
			break;
		case NOTIFICATION_DRAW:
			draw();
			_draw();
			break;
		case NOTIFICATION_PARENTED:
			_on_parent_changed(get_parent());
			break;
		default:
			break;
	}
}

void CanvasNode::_draw() const {
}

CanvasNode::CanvasNode() : canvas_item(0),
    modulation(ColorV::WHITE()),
	blend_mode(SDL_BLENDMODE_BLEND),
	scale_mode(SDL_ScaleModeLinear),
	visible(true),
	zindex_relative(true),
	update_queued(false),
	zindex(0) {
}

void CanvasNode::queue_redraw() {
	if (!is_inside_tree() || update_queued)
		return;

	SceneTree *tree = get_tree();
	tree->deferred_signals.connect(std::bind(&CanvasNode::_update, this));
	tree->deferred_signals.connect(std::bind(&Node::notification, this, NOTIFICATION_DRAW));
}

Transform2D CanvasNode::get_transform() const {
	Optional<RenderingServer*> rendering_server = get_rendering_server();
	Transform2D transform = Transform2D::IDENTITY;

	if (rendering_server)
		transform = rendering_server.get_value()->canvas_item_get_transform(canvas_item).value_or(Transform2D::IDENTITY);

	return transform;
}

Transform2D CanvasNode::get_global_transform() const {
	Optional<RenderingServer*> rendering_server = get_rendering_server();
	Transform2D transform = Transform2D::IDENTITY;

	if (rendering_server)
		transform = rendering_server.get_value()->canvas_item_get_global_transform(canvas_item).value_or(Transform2D::IDENTITY);

	return transform;
}

void CanvasNode::hide() {
	if (!visible)
		return;

	visible = false;
	hidden();
	visibility_changed();
	queue_redraw();
}

void CanvasNode::show() {
	if (visible)
		return;

	visible = true;
	hidden();
	visibility_changed();
	queue_redraw();
}

void CanvasNode::set_modulation(const ColorV &modulation) {
	this->modulation = modulation;
	queue_redraw();
}

const ColorV &CanvasNode::get_modulation() const {
	return modulation;
}

ColorV CanvasNode::get_absolute_modulation() const {
	Optional<RenderingServer*> rendering_server = get_rendering_server();

	if (rendering_server)
		return rendering_server.get_value()->canvas_item_get_global_modulate(canvas_item).value_or(modulation);

	return modulation;
}

void CanvasNode::set_blend_mode(SDL_BlendMode blend_mode) {
	this->blend_mode = blend_mode;
	queue_redraw();
}

void CanvasNode::set_scale_mode(SDL_ScaleMode scale_mode) {
	this->scale_mode = scale_mode;
	queue_redraw();
}

void CanvasNode::set_zindex(int zindex) {
	this->zindex = zindex;
}

int CanvasNode::get_absolute_zindex() const {
	Optional<RenderingServer*> rendering_server = get_rendering_server();

	if (rendering_server)
		return rendering_server.get_value()->canvas_item_get_absolute_zindex(canvas_item).value_or(zindex);

	return zindex;
}

void CanvasNode::set_zindex_relative(bool zindex_relative) {
	this->zindex_relative = zindex_relative;
	queue_redraw();
}

bool CanvasNode::is_visible_in_tree() const {
	Optional<RenderingServer*> rendering_server = get_rendering_server();

	if (rendering_server)
		return rendering_server.get_value()->canvas_item_is_globally_visible(canvas_item).value_or(visible);

	return visible;
}

bool CanvasNode::is_visible_inside_viewport() const {
	Optional<RenderingServer*> rendering_server = get_rendering_server();

	if (rendering_server)
		return rendering_server.get_value()->canvas_item_is_visible_inside_viewport(canvas_item).value_or(false);

	return false;
}

void CanvasNode::draw_texture(uid texture_uid, const Transform2D &texture_transform, const ColorV &modulation) const {
	Optional<RenderingServer*> rendering_server = get_rendering_server();

	if (rendering_server)
		rendering_server.get_value()->canvas_item_add_texture(texture_uid, canvas_item, SDL_FLIP_NONE, modulation, texture_transform);
}

void CanvasNode::draw_texture_rect(uid texture_uid, const Rect2i &region, const Transform2D &texture_transform, const ColorV &modulation) const {
	Optional<RenderingServer*> rendering_server = get_rendering_server();

	if (rendering_server)
		rendering_server.get_value()->canvas_item_add_texture_region(texture_uid, canvas_item, region, SDL_FLIP_NONE, modulation, texture_transform);
}

void CanvasNode::draw_line(const Vector2f &start, const Vector2f &end, const ColorV &modulation) const {
	Optional<RenderingServer*> rendering_server = get_rendering_server();

	if (rendering_server)
		rendering_server.get_value()->canvas_item_add_line(canvas_item, start, end,  modulation);
}

void CanvasNode::draw_lines(const std::vector<SDL_FPoint> &points, const ColorV &modulation) const {
	Optional<RenderingServer*> rendering_server = get_rendering_server();
	if (rendering_server)
		rendering_server.get_value()->canvas_item_add_lines(canvas_item, points, modulation);
}

void CanvasNode::draw_rect(const Rect2f &rect, const ColorV &modulation) const {
	Optional<RenderingServer*> rendering_server = get_rendering_server();
	if (rendering_server)
		rendering_server.get_value()->canvas_item_add_rect(canvas_item, rect, modulation);
}

void CanvasNode::draw_rects(const std::vector<SDL_FRect> &rects, const ColorV &modulation) const {
	Optional<RenderingServer*> rendering_server = get_rendering_server();
	if (rendering_server)
		rendering_server.get_value()->canvas_item_add_rects(canvas_item, rects, modulation);
}

