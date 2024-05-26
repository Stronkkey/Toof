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
#include <servers/rendering/viewport.hpp>
#include <servers/rendering/texture.hpp>

using namespace Toof;

void detail::DrawingItem::draw(const std::shared_ptr<CanvasItem> &canvas_item, const Viewport *viewport) {
	_draw(canvas_item, viewport);
}

Toof::Rect2f detail::DrawingItem::get_draw_rect(const std::shared_ptr<CanvasItem> &canvas_item) const {
	return _get_draw_rect(canvas_item);
}

void detail::DrawingItem::_draw(const std::shared_ptr<CanvasItem>&, const Viewport*) {
}

Toof::Rect2f detail::DrawingItem::_get_draw_rect(const std::shared_ptr<CanvasItem>&) const {
	return Rect2f();
}

Toof::Rect2f detail::TextureDrawingItem::_get_draw_rect(const std::shared_ptr<CanvasItem> &canvas_item) const {
	const Transform2D &global_transform = canvas_item->get_global_transform();
	const Vector2 position = global_transform.origin + transform.origin;
	const Vector2 size = global_transform.scale * transform.scale * (use_region ? src_region.get_size() : texture.lock()->size);

	return Rect2(position, size);
}

void detail::TextureDrawingItem::_draw(const std::shared_ptr<CanvasItem> &canvas_item, const Viewport *viewport) {
	if (texture.expired())
		return;

	const std::shared_ptr<Texture_Ref> texture = this->texture.lock();

	const ColorV &modulate = texture_modulate * canvas_item->get_global_modulate();

	SDL_SetTextureAlphaMod(texture->texture_reference, modulate.a);
	SDL_SetTextureColorMod(texture->texture_reference, modulate.r, modulate.g, modulate.b);
	SDL_SetTextureBlendMode(texture->texture_reference, canvas_item->blend_mode);
	SDL_SetTextureScaleMode(texture->texture_reference, canvas_item->scale_mode);

	const Transform2D &global_transform = canvas_item->get_global_transform() * viewport->get_canvas_transform();
	const Rect2i &source_region = use_region ? src_region : Rect2i(Vector2i(), texture->size);
	const Angle rotation = global_transform.rotation + transform.rotation;
	Rect2f final_draw_rect = rect2f_add_transform(_get_draw_rect(canvas_item), viewport->get_canvas_transform());
	final_draw_rect.rounded();

	SDL_Rect final_source_region = source_region.to_sdl_rect();
	SDL_FRect final_destination = final_draw_rect.to_sdl_frect();

	if (rotation.is_zero_angle())
		SDL_RenderCopyF(viewport->get_renderer(), texture->texture_reference, &final_source_region, &final_destination);
	else
		SDL_RenderCopyExF(viewport->get_renderer(), texture->texture_reference, &final_source_region, &final_destination, rotation.get_angle_degrees(), nullptr, flip);
}

void detail::RectDrawingItem::_draw(const std::shared_ptr<CanvasItem> &canvas_item, const Viewport *viewport) {
	const Transform2D &global_transform = canvas_item->get_global_transform() * viewport->get_canvas_transform();

	SDL_Renderer *renderer = viewport->get_renderer();
	SDL_FRect rect = rectangle;

	rect.x = std::round(rect.x + global_transform.origin.x);
	rect.y = std::round(rect.y + global_transform.origin.y);
	rect.w = std::round(rect.w * global_transform.scale.x);
	rect.h = std::round(rect.h * global_transform.scale.y);

	SDL_SetRenderDrawColor(renderer, modulate.r, modulate.g, modulate.b, modulate.a);
	SDL_SetRenderDrawBlendMode(renderer, canvas_item->blend_mode);
	SDL_RenderFillRectF(renderer, &rect);
}

Toof::Rect2f detail::RectDrawingItem::_get_draw_rect(const std::shared_ptr<CanvasItem> &canvas_item) const {
	return rect2f_add_transform(rectangle, canvas_item->get_global_transform());
}

void detail::RectsDrawingItem::_draw(const std::shared_ptr<CanvasItem> &canvas_item, const Viewport *viewport) {
	if (rectangles.empty())
		return;

	const Transform2D &global_transform = canvas_item->get_global_transform();
	SDL_Renderer *renderer = viewport->get_renderer();

	SDL_SetRenderDrawColor(viewport->get_renderer(), modulate.r, modulate.g, modulate.b, modulate.a);
	SDL_SetRenderDrawBlendMode(viewport->get_renderer(), canvas_item->blend_mode);

	for (const auto &rectangle: rectangles) {
		SDL_FRect frect = rectangle;

		frect.x = std::round(frect.x + global_transform.origin.x);
		frect.y = std::round(frect.y + global_transform.origin.y);
		frect.w = std::round(frect.w * global_transform.scale.x);
		frect.h = std::round(frect.h * global_transform.scale.y);

		SDL_RenderFillRectF(renderer, &frect);
	}
}

Toof::Rect2f detail::RectsDrawingItem::_get_draw_rect(const std::shared_ptr<CanvasItem> &canvas_item) const {
	const Transform2D &global_transform = canvas_item->get_global_transform();
	Rect2f final_rect = Rect2f();

	for (const auto &frect: rectangles)
		final_rect = final_rect.merge(Rect2f(frect));

	final_rect.x += global_transform.origin.x;
	final_rect.y += global_transform.origin.y;
	final_rect.w += global_transform.scale.x;
	final_rect.h += global_transform.scale.y;
	final_rect.rounded();
	return final_rect;
}

void detail::LineDrawingItem::_draw(const std::shared_ptr<CanvasItem> &canvas_item, const Viewport *viewport) {
	const Transform2D &global_transform = canvas_item->get_global_transform() * viewport->get_canvas_transform();
	SDL_Renderer *renderer = viewport->get_renderer();

	float x_1 = std::round(start_point.x + global_transform.origin.x);
	float y_1 = std::round(start_point.y + global_transform.origin.y);
	float x_2 = std::round((end_point.x + global_transform.origin.x) * global_transform.scale.x);
	float y_2 = std::round((end_point.y + global_transform.origin.y) * global_transform.scale.y);

	SDL_SetRenderDrawColor(renderer, modulate.r, modulate.g, modulate.b, modulate.a);
	SDL_SetRenderDrawBlendMode(renderer, canvas_item->blend_mode);
	SDL_RenderDrawLineF(renderer, x_1, y_1, x_2, y_2);
}

Toof::Rect2f detail::LineDrawingItem::_get_draw_rect(const std::shared_ptr<CanvasItem> &canvas_item) const {
	const Transform2D &global_transform = canvas_item->get_global_transform();
	return Rect2f(Vector2f(start_point) + global_transform.origin, end_point).remove_negative_size().round();
}

void detail::LinesDrawingItem::_draw(const std::shared_ptr<CanvasItem> &canvas_item, const Viewport *viewport) {
	if (points.size() < 2)
		return;

	const Transform2D &global_transform = canvas_item->get_global_transform();
	const size_t points_size = points.size();
	SDL_Renderer *renderer = viewport->get_renderer();

	SDL_SetRenderDrawColor(renderer, modulate.r, modulate.g, modulate.b, modulate.a);
	SDL_SetRenderDrawBlendMode(renderer, canvas_item->blend_mode);

	for (size_t i = 0; i < points_size; i++) {
		float x_1 = std::round(points[i].x + global_transform.origin.x);
		float y_1 = std::round(points[i].y + global_transform.origin.y);
		float x_2 = std::round(points[i + 1].x + global_transform.scale.x);
		float y_2 = std::round(points[i + 1].y + global_transform.scale.y);

		SDL_RenderDrawLineF(renderer, x_1, y_1, x_2, y_2);
	}
}

Toof::Rect2f detail::LinesDrawingItem::_get_draw_rect(const std::shared_ptr<CanvasItem> &canvas_item) const {
	Rect2f rect = Rect2f();

	const Transform2D &global_transform = canvas_item->get_global_transform();

	for (const auto &point: points)
		rect.expand_to(point);

	rect.x += global_transform.origin.x;
	rect.y += global_transform.origin.y;
	rect.w *= global_transform.scale.x;
	rect.h *= global_transform.scale.y;
	rect.rounded();
	return rect;
}