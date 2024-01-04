#include <servers/rendering/2d/canvas_item.hpp>
#include <servers/rendering/2d/drawing_item.hpp>
#include <servers/rendering/viewport.hpp>
#include <servers/rendering/texture.hpp>

using namespace sdl;

void DrawingItem::draw(const Viewport *viewport) {
	if (canvas_item)
		_draw(viewport);
}

Rect2 DrawingItem::get_draw_rect() const {
	if (canvas_item)
		return _get_draw_rect();
	return Rect2::EMPTY;
}

Rect2 TextureDrawingItem::_get_draw_rect() const {
	Transform2D global_transform = canvas_item->get_global_transform();
	return Rect2(global_transform.origin + transform.origin, (global_transform.scale * transform.scale) * texture->size).round();
}

void TextureDrawingItem::_draw(const Viewport *viewport) {
	if (!texture)
		return;

	Transform2D global_transform = canvas_item->get_global_transform() * viewport->get_canvas_transform();
	Rect2 src_region = Rect2(Vector2::ZERO, texture->size);

	double rotation = global_transform.rotation + transform.rotation;
	Color modulate = texture_modulate * canvas_item->get_absolute_modulate();
	Rect2 final_draw_rect = (_get_draw_rect() * viewport->get_canvas_transform());

	final_draw_rect.rounded();

	SDL_SetTextureAlphaMod(texture->texture_reference, modulate.a);
	SDL_SetTextureColorMod(texture->texture_reference, modulate.r, modulate.g, modulate.b);
	SDL_SetTextureBlendMode(texture->texture_reference, canvas_item->blend_mode);
	SDL_SetTextureScaleMode(texture->texture_reference, canvas_item->scale_mode);

	draw_texture(viewport, src_region.to_sdl_rect(), final_draw_rect.to_sdl_frect(), rotation, SDL_FPoint());
}

void TextureDrawingItem::draw_texture(const Viewport *viewport,
        const SDL_Rect &src_region,
        const SDL_FRect &destination,
        const double rotation,
		const SDL_FPoint &center) {
	if (rotation == 0.0)
		SDL_RenderCopyF(
		viewport->get_renderer(),
		texture->texture_reference,
		&src_region,
		&destination);
	else
		SDL_RenderCopyExF(viewport->get_renderer(),
		    texture->texture_reference,
		    &src_region,
		    &destination,
		    rotation,
		    (center.x == 0.0f && center.y == 0.0f) ? NULL : &center,
		        flip);
}

Rect2 TextureRectDrawingItem::_get_draw_rect() const {
	Transform2D global_transform = canvas_item->get_global_transform();
	return Rect2(global_transform.origin, (global_transform.scale * transform.scale) * src_region.get_size());
}

void TextureRectDrawingItem::_draw(const Viewport *viewport) {
	if (!texture)
		return;

	Transform2D global_transform = canvas_item->get_global_transform();

	double rotation = global_transform.rotation + transform.rotation;
	Color modulate = texture_modulate * canvas_item->get_absolute_modulate();
	Rect2 final_draw_rect = _get_draw_rect() * viewport->get_canvas_transform();

	final_draw_rect.rounded();

	SDL_SetTextureColorMod(texture->texture_reference, modulate.r, modulate.g, modulate.b);
	SDL_SetTextureAlphaMod(texture->texture_reference, modulate.a);
	SDL_SetTextureBlendMode(texture->texture_reference, canvas_item->blend_mode);
	SDL_SetTextureScaleMode(texture->texture_reference, canvas_item->scale_mode);

	draw_texture(viewport,
	    src_region.to_sdl_rect(),
	    final_draw_rect.to_sdl_frect(),
	    rotation);
}

void TextureRectDrawingItem::draw_texture(const Viewport *viewport,
      const SDL_Rect &src_region,
      const SDL_FRect &destination,
      const double rotation,
      const SDL_FPoint &center) {
	if (rotation == 0.0)
		SDL_RenderCopyF(
		    viewport->get_renderer(),
		    texture->texture_reference,
		    &src_region,
		    &destination);
	else
		SDL_RenderCopyExF(viewport->get_renderer(),
		    texture->texture_reference,
	        &src_region,
		    &destination,
		    rotation,
		    (center.x == 0.0f && center.y == 0.0f) ? NULL : &center,
		    flip);
}

void RectDrawingItem::_draw(const Viewport *viewport) {
	const Transform2D global_transform = canvas_item->get_global_transform() * viewport->get_canvas_transform();
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

Rect2 RectDrawingItem::_get_draw_rect() const {
	const Transform2D global_transform = canvas_item->get_global_transform();
	return Rect2(rectangle) * global_transform;
}

void RectsDrawingItem::_draw(const Viewport *viewport) {
	if (rectangles.empty())
		return;

	const Transform2D global_transform = canvas_item->get_global_transform();
	SDL_Renderer *renderer = viewport->get_renderer();

	SDL_SetRenderDrawColor(viewport->get_renderer(), modulate.r, modulate.g, modulate.b, modulate.a);
	SDL_SetRenderDrawBlendMode(viewport->get_renderer(), canvas_item->blend_mode);

	for (Rect2 rectangle: rectangles) {
		SDL_FRect frect = rectangle.to_sdl_frect();

		frect.x = std::round(frect.x + global_transform.origin.x);
		frect.y = std::round(frect.y + global_transform.origin.y);
		frect.w = std::round(frect.w * global_transform.scale.x);
		frect.h = std::round(frect.h * global_transform.scale.y);

		SDL_RenderFillRectF(renderer, &frect);
	}
}

Rect2 RectsDrawingItem::_get_draw_rect() const {
	Rect2 final_rect = Rect2();

	for (SDL_FRect frect: rectangles)
		final_rect = final_rect.merge(Rect2(frect));

	final_rect.rounded();
	return final_rect;
}

void LineDrawingItem::_draw(const Viewport *viewport) {
	const Transform2D global_transform = canvas_item->get_global_transform() * viewport->get_canvas_transform();
	SDL_Renderer *renderer = viewport->get_renderer();

	int x_1 = std::round(start_point.x + global_transform.origin.x);
	int y_1 = std::round(start_point.y + global_transform.origin.y);
	int x_2 = std::round((end_point.x + global_transform.origin.x) * global_transform.scale.x);
	int y_2 = std::round((end_point.y + global_transform.origin.y) * global_transform.scale.y);

	SDL_SetRenderDrawColor(renderer, modulate.r, modulate.g, modulate.b, modulate.a);
	SDL_SetRenderDrawBlendMode(renderer, canvas_item->blend_mode);
	SDL_RenderDrawLineF(renderer, x_1, y_1, x_2, y_2);
}

Rect2 LineDrawingItem::_get_draw_rect() const {
	const Vector2 global_position = canvas_item->get_global_transform().origin;
	return Rect2(Vector2(start_point) + global_position, end_point).remove_negative_size().round();
}

void LinesDrawingItem::_draw(const Viewport *viewport) {
	if (points.size() < 2)
		return;

	const Vector2 global_position = canvas_item->get_global_transform().origin;
	const size_t points_size = points.size();
	SDL_Renderer *renderer = viewport->get_renderer();

	SDL_SetRenderDrawColor(renderer, modulate.r, modulate.g, modulate.b, modulate.a);
	SDL_SetRenderDrawBlendMode(renderer, canvas_item->blend_mode);

	for (size_t i = 0; i < points_size; i++) {
		if (i + 1 >= points_size)
			break;

		int x_1 = std::round(points[i].x + global_position.x);
		int y_1 = std::round(points[i].y + global_position.y);
		int x_2 = std::round(points[i + 1].x + global_position.x);
		int y_2 = std::round(points[i + 1].y + global_position.y);

		SDL_RenderDrawLineF(renderer, x_1, y_1, x_2, y_2);
	}
}

Rect2 LinesDrawingItem::_get_draw_rect() const {
	Rect2 rect = Rect2();
	const Vector2 global_position = canvas_item->get_global_transform().origin;

	for (SDL_FPoint point: points)
		rect.expand_to(point);

	rect.x += global_position.x;
	rect.y += global_position.y;
	rect.rounded();
	return rect;
}