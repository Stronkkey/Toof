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
#include <servers/rendering/2d/canvas_item.hpp>
#include <servers/rendering/2d/drawing_item.hpp>
#include <servers/rendering_server.hpp>
#include <servers/rendering/viewport.hpp>
#include <servers/rendering/texture.hpp>

#include <SDL_image.h>

#include <algorithm>

using namespace Toof;

RenderingServer::RenderingServer(Viewport *viewport): viewport(viewport),
    textures(),
    canvas_items(),
    background_color(ColorV(77, 77, 77, 255)),
    uid_index(1) {
}

RenderingServer::~RenderingServer() {
	for (auto &iterator: textures)
		destroy_texture(iterator.second);

	textures.clear();
	canvas_items.clear();
}

Vector2i RenderingServer::get_screen_size() const {
	return viewport->get_viewport_size();
}

void RenderingServer::render() {
	SDL_Renderer *renderer = viewport->get_renderer();

	SDL_RenderClear(renderer);
	render_canvas_items();
	SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, background_color.a);
	SDL_RenderPresent(renderer);
}

const std::shared_ptr<Toof::detail::Texture_Ref> &RenderingServer::get_texture_from_uid(const uid texture_uid) const {
	const auto &iterator = textures.find(texture_uid);
	if (iterator != textures.end())
		return iterator->second;

	const std::shared_ptr<detail::Texture_Ref> _t, *t = &_t;
	return *t;
}

const std::shared_ptr<Toof::detail::CanvasItem> &RenderingServer::get_canvas_item_from_uid(const uid canvas_item_uid) const {
	const auto &iterator = canvas_items.find(canvas_item_uid);
	if (iterator != canvas_items.end())
		return iterator->second;

	const std::shared_ptr<detail::CanvasItem> _t, *t = &_t;
	return *t;
}

void RenderingServer::remove_uid(const uid destroying_uid) {
	destroy_uid(destroying_uid);
}

void RenderingServer::destroy_texture(std::shared_ptr<detail::Texture_Ref> &texture) {
	SDL_DestroyTexture(texture->texture_reference);
}

void RenderingServer::destroy_texture_uid(const uid texture_uid) {
	const auto &iterator = textures.find(texture_uid);

	if (iterator != textures.end()) {
		destroy_texture(iterator->second);
		textures.erase(iterator);
	}
}

void RenderingServer::destroy_canvas_item_uid(const uid canvas_item_uid) {
	canvas_items.erase(canvas_item_uid);
}

void RenderingServer::destroy_uid(const uid destroying_uid) {
	destroy_canvas_item_uid(destroying_uid);
	destroy_texture_uid(destroying_uid);
}

void RenderingServer::render_canvas_item(const std::shared_ptr<detail::CanvasItem> &canvas_item) {
	if (!canvas_item->is_globally_visible() || canvas_item->drawing_items.empty())
		return;

	const Rect2i screen_rect = Rect2i(Vector2i(), get_screen_size());
	const Transform2D canvas_transform = viewport->get_canvas_transform();

	for (const auto &drawing_item: canvas_item->drawing_items) {
		bool inside_viewport = screen_rect.intersects(rect2f_add_transform(drawing_item->get_draw_rect(canvas_item), canvas_transform));

		if (inside_viewport)
			drawing_item->draw(canvas_item, viewport);
	}
}

bool comparison_function(const std::shared_ptr<Toof::detail::CanvasItem> &left, const std::shared_ptr<detail::CanvasItem> &right) {
	return left->get_global_zindex() < right->get_global_zindex();
}

void RenderingServer::render_canvas_items() {
	std::vector<std::shared_ptr<detail::CanvasItem>> sorted_canvas_items;

	for (const auto &iterator: canvas_items)
		sorted_canvas_items.push_back(iterator.second);
	std::sort(sorted_canvas_items.begin(), sorted_canvas_items.end(), &comparison_function);

	for (const auto &canvas_item: sorted_canvas_items)
		render_canvas_item(canvas_item);
}

Optional<RenderingServer::TextureInfo> RenderingServer::get_texture_info_from_uid(const uid texture_uid) const {
	const std::shared_ptr<detail::Texture_Ref> &texture = get_texture_from_uid(texture_uid);
	TextureInfo texture_info;

	if (!texture)
		return texture_info;

	texture_info.size = texture->size;
	texture_info.format = texture->format;
	texture_info.texture = texture->texture_reference;
	return texture_info;
}

Optional<uid> RenderingServer::load_texture_from_path(const String &path) {
	SDL_Texture *texture = IMG_LoadTexture(viewport->get_renderer(), path.c_str());
	if (texture == NULL)
		return NullOption;

	uid new_uid = assign_uid();
	auto new_texture = std::make_shared<detail::Texture_Ref>();
	new_texture->texture_reference = texture;

	int width;
	int height;
	SDL_QueryTexture(texture, &new_texture->format, NULL, &width, &height);

	new_texture->size = Vector2i(width, height);
	textures.insert({new_uid, new_texture});

	return new_uid;
}

uid RenderingServer::create_canvas_item() {
	uid new_uid = assign_uid();
	auto canvas_item = std::make_shared<detail::CanvasItem>();

	canvas_items.insert({new_uid, canvas_item});
	return new_uid;
}

void RenderingServer::canvas_item_add_texture(const uid texture_uid, const uid canvas_item_uid, const SDL_RendererFlip flip, const ColorV &modulate, const Transform2D &transform) {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);
	const std::shared_ptr<detail::Texture_Ref> &texture = get_texture_from_uid(texture_uid);

	if (!canvas_item || !texture)
		return;
	
	auto texture_drawing_item = std::make_unique<detail::TextureDrawingItem>();

	texture_drawing_item->texture = texture;
	texture_drawing_item->flip = flip;
	texture_drawing_item->transform = transform;
	texture_drawing_item->texture_modulate = modulate;
	texture_drawing_item->use_region = false;

	canvas_item->drawing_items.push_back(std::move(texture_drawing_item));
}

void RenderingServer::canvas_item_add_texture_region(const uid texture_uid, const uid canvas_item_uid ,const Rect2i &src_region, const SDL_RendererFlip flip, const ColorV &modulate, const Transform2D &transform) {
	const std::shared_ptr<detail::Texture_Ref> &texture = get_texture_from_uid(texture_uid);
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (!canvas_item || !texture || !src_region.has_area())
		return;

	auto texture_rect_drawing_item = std::make_unique<detail::TextureDrawingItem>();

	texture_rect_drawing_item->texture = texture;
	texture_rect_drawing_item->src_region = src_region;
	texture_rect_drawing_item->transform = transform;
	texture_rect_drawing_item->flip = flip;
	texture_rect_drawing_item->texture_modulate = modulate;
	texture_rect_drawing_item->use_region = true;

	canvas_item->drawing_items.push_back(std::move(texture_rect_drawing_item));
}

void RenderingServer::canvas_item_add_line(const uid canvas_item_uid, const Vector2f &start, const Vector2f &end, const ColorV &modulate) {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (!canvas_item)
		return;

	auto line_drawing_item = std::make_unique<detail::LineDrawingItem>();

	line_drawing_item->start_point = start.to_sdl_fpoint();
	line_drawing_item->end_point = end.to_sdl_fpoint();
	line_drawing_item->modulate = modulate;

	canvas_item->drawing_items.push_back(std::move(line_drawing_item));
}

void RenderingServer::canvas_item_add_lines(const uid canvas_item_uid, const std::vector<SDL_FPoint> &points, const ColorV &modulate) {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (!canvas_item || points.empty())
		return;

	auto lines_drawing_item = std::make_unique<detail::LinesDrawingItem>();

	lines_drawing_item->points = points;
	lines_drawing_item->modulate = modulate;

	canvas_item->drawing_items.push_back(std::move(lines_drawing_item));
}

void RenderingServer::canvas_item_add_rect(const uid canvas_item_uid, const Rect2f &rect, const ColorV &modulate) {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (!canvas_item || !rect.has_area())
		return;

	auto rect_drawing_item = std::make_unique<detail::RectDrawingItem>();

	rect_drawing_item->rectangle = rect.to_sdl_frect();
	rect_drawing_item->modulate = modulate;

	canvas_item->drawing_items.push_back(std::move(rect_drawing_item));
}

void RenderingServer::canvas_item_add_rects(const uid canvas_item_uid, const std::vector<SDL_FRect> &rectangles, const ColorV &modulate) {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (!canvas_item || rectangles.empty())
		return;

	auto rects_drawing_item = std::make_unique<detail::RectsDrawingItem>();

	rects_drawing_item->rectangles = rectangles;
	rects_drawing_item->modulate = modulate;

	canvas_item->drawing_items.push_back(std::move(rects_drawing_item));
}

void RenderingServer::canvas_item_set_transform(const uid canvas_item_uid, const Transform2D &new_transform) {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (canvas_item)
		canvas_item->transform = new_transform;
}

void RenderingServer::canvas_item_set_parent(const uid canvas_item_uid, const uid parent_item_uid) {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);
	const std::shared_ptr<detail::CanvasItem> &parent_canvas_item = get_canvas_item_from_uid(parent_item_uid);

	if (!canvas_item)
		return;

	if (parent_canvas_item)
		canvas_item->parent = parent_canvas_item;
	else
		canvas_item->parent = std::weak_ptr<detail::CanvasItem>();
}

void RenderingServer::canvas_item_set_modulate(const uid canvas_item_uid, const ColorV &new_modulate) {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (canvas_item)
		canvas_item->modulate = new_modulate;
}

void RenderingServer::canvas_item_set_blend_mode(const uid canvas_item_uid, const SDL_BlendMode blend_mode) {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (canvas_item)
		canvas_item->blend_mode = blend_mode;
}

void RenderingServer::canvas_item_set_scale_mode(const uid canvas_item_uid, const SDL_ScaleMode scale_mode) {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (canvas_item)
		canvas_item->scale_mode = scale_mode;
}

void RenderingServer::canvas_item_clear(const uid canvas_item_uid) {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (canvas_item)
		canvas_item->drawing_items.clear();
}

void RenderingServer::canvas_item_set_visible(const uid canvas_item_uid, const bool visible) {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (canvas_item)
		canvas_item->visible = visible;
}

void RenderingServer::canvas_item_set_zindex(const uid canvas_item_uid, const int zindex) {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (canvas_item)
		canvas_item->zindex = zindex;
}

void RenderingServer::canvas_item_set_zindex_relative(const uid canvas_item_uid, const bool zindex_relative) {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (canvas_item)
		canvas_item->zindex_relative = zindex_relative;
}

bool RenderingServer::canvas_item_uid_exists(const uid canvas_item_uid) const {
	return canvas_items.find(canvas_item_uid) != canvas_items.end();
}

bool RenderingServer::texture_uid_exists(const uid texture_uid) const {
	return textures.find(texture_uid) != textures.end();
}

Optional<const Transform2D> RenderingServer::canvas_item_get_transform(const uid canvas_item_uid) const {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (canvas_item)
		return canvas_item->transform;
	return NullOption;
}

Optional<const Transform2D> RenderingServer::canvas_item_get_global_transform(const uid canvas_item_uid) const {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (canvas_item)
		return canvas_item->get_global_transform();
	return NullOption;
}

Optional<const ColorV> RenderingServer::canvas_item_get_modulate(const uid canvas_item_uid) const {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (canvas_item)
		return canvas_item->modulate;
	return NullOption;
}

Optional<const ColorV> RenderingServer::canvas_item_get_global_modulate(const uid canvas_item_uid) const {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (canvas_item)
		return canvas_item->get_global_modulate();
	return NullOption;
}

Optional<bool> RenderingServer::canvas_item_is_visible(const uid canvas_item_uid) const {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (canvas_item)
		return canvas_item->visible;
	return NullOption;
}

Optional<bool> RenderingServer::canvas_item_is_globally_visible(const uid canvas_item_uid) const {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (canvas_item)
		return canvas_item->is_globally_visible();
	return NullOption;
}

Optional<bool> RenderingServer::canvas_item_is_visible_inside_viewport(const uid canvas_item_uid) const {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (!canvas_item)
		return NullOption;

	if (!canvas_item->is_globally_visible() || canvas_item->drawing_items.empty())
		return false;

	const Rect2i screen_rect = Rect2i(Vector2i(), get_screen_size());
	const Transform2D &canvas_transform = viewport->get_canvas_transform();
	bool is_visible = true;

	for (const auto &drawing_item: canvas_item->drawing_items) {
		bool inside_viewport = screen_rect.intersects(rect2f_add_transform(drawing_item->get_draw_rect(canvas_item), canvas_transform));

		if (!inside_viewport) {
			is_visible = false;
			break;
		}
	}

	return is_visible;
}

Optional<SDL_BlendMode> RenderingServer::canvas_item_get_blend_mode(const uid canvas_item_uid) const {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (canvas_item)
		return canvas_item->blend_mode;
	return NullOption;
}

Optional<SDL_ScaleMode> RenderingServer::canvas_item_get_scale_mode(const uid canvas_item_uid) const {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (canvas_item)
		return canvas_item->scale_mode;
	return NullOption;
}

Optional<int> RenderingServer::canvas_item_get_zindex(const uid canvas_item_uid) const {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (canvas_item)
		return canvas_item->zindex;
	return NullOption;
}

Optional<int> RenderingServer::canvas_item_get_absolute_zindex(const uid canvas_item_uid) const {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (canvas_item)
		return canvas_item->get_global_zindex();
	return NullOption;
}

Optional<bool> RenderingServer::canvas_item_is_zindex_relative(const uid canvas_item_uid) const {
	const std::shared_ptr<detail::CanvasItem> &canvas_item = get_canvas_item_from_uid(canvas_item_uid);

	if (canvas_item)
		return canvas_item->zindex_relative;
	return NullOption;
}