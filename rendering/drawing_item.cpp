#include <rendering/canvas_item.hpp>
#include <rendering/drawing_item.hpp>
#include <rendering/viewport.hpp>

using namespace sdl;

void DrawingItem::draw(const Viewport*) {
}

Rect2 DrawingItem::get_draw_rect() const {
	return Rect2::EMPTY;
}

Rect2 TextureDrawingItem::get_draw_rect() const {
	Transform2D global_transform = canvas_item->get_global_transform();
	return Rect2(global_transform.origin + transform.origin, (global_transform.scale * transform.scale) * texture->size);
}

void TextureDrawingItem::draw(const Viewport *viewport) {
	if (!canvas_item || !texture)
		return;

	Transform2D global_transform = canvas_item->get_global_transform() * viewport->get_canvas_transform();
	Rect2 src_region = Rect2(Vector2::ZERO, texture->size);

	double rotation = global_transform.rotation + transform.rotation;
	Color modulate = texture_modulate * canvas_item->get_absolute_modulate();
	Rect2 final_draw_rect = (get_draw_rect() * viewport->get_canvas_transform());

	SDL_SetTextureAlphaMod(texture->texture_reference, modulate.a);
	SDL_SetTextureColorMod(texture->texture_reference, modulate.r, modulate.g, modulate.b);
	SDL_SetTextureBlendMode(texture->texture_reference, canvas_item->blend_mode);

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

Rect2 TextureRectDrawingItem::get_draw_rect() const {
	Transform2D global_transform = canvas_item->get_global_transform();
	return Rect2(global_transform.origin, (global_transform.scale * transform.scale) * src_region.get_size());
}

void TextureRectDrawingItem::draw(const Viewport *viewport) {
	if (!canvas_item || !texture)
		return;

	Transform2D global_transform = canvas_item->get_global_transform();

	double rotation = global_transform.rotation + transform.rotation;
	Color modulate = texture_modulate * canvas_item->get_absolute_modulate();
	Rect2 final_draw_rect = get_draw_rect() * viewport->get_canvas_transform();

	SDL_SetTextureColorMod(texture->texture_reference, modulate.r, modulate.g, modulate.b);
	SDL_SetTextureAlphaMod(texture->texture_reference, modulate.a);
	SDL_SetTextureBlendMode(texture->texture_reference, canvas_item->blend_mode);

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

void RectDrawingItem::draw(const Viewport *viewport) {
	if (!canvas_item)
		return;

	const Transform2D global_transform = canvas_item->get_global_transform();
	SDL_Renderer *renderer = viewport->get_renderer();
	SDL_FRect rect = rectangle;

	rect.x += global_transform.origin.x;
	rect.y += global_transform.origin.y;
	rect.w *= global_transform.scale.x;
	rect.h *= global_transform.scale.y;

	SDL_SetRenderDrawColor(renderer, modulate.r, modulate.g, modulate.b, modulate.a);
	SDL_SetRenderDrawBlendMode(renderer, canvas_item->blend_mode);
	SDL_RenderFillRectF(renderer, &rect);
}

Rect2 RectDrawingItem::get_draw_rect() const {
	return Rect2(rectangle);
}

void RectsDrawingItem::draw(const Viewport *viewport) {
	if (!canvas_item)
		return;

	const Transform2D global_transform = canvas_item->get_global_transform();
	const size_t rectangles_size = rectangles.size();
	SDL_Renderer *renderer = viewport->get_renderer();

	SDL_SetRenderDrawColor(viewport->get_renderer(), modulate.r, modulate.g, modulate.b, modulate.a);
	SDL_SetRenderDrawBlendMode(viewport->get_renderer(), canvas_item->blend_mode);

	for (size_t i = 0; i < rectangles_size; i++) {
		SDL_FRect rect = rectangles[i];
		rect.x += global_transform.origin.x;
		rect.y += global_transform.origin.y;
		rect.w *= global_transform.scale.x;
		rect.h *= global_transform.scale.y;

		SDL_RenderDrawRectF(renderer, &rect);
	}
}

Rect2 RectsDrawingItem::get_draw_rect() const {
	Rect2 final_rect;

	for (SDL_FRect frect: rectangles)
		final_rect = final_rect.merge(Rect2(frect));

	return final_rect;
}

void LineDrawingItem::draw(const Viewport *viewport) {
	if (!canvas_item)
		return;

	const Vector2 global_position = canvas_item->get_global_transform().origin;
	SDL_Renderer *renderer = viewport->get_renderer();

	int x_1 = start_point.x + global_position.x;
	int y_1 = start_point.y + global_position.y;
	int x_2 = end_point.x + global_position.x;
	int y_2 = end_point.y + global_position.y;

	SDL_SetRenderDrawColor(renderer, modulate.r, modulate.g, modulate.b, modulate.a);
	SDL_SetRenderDrawBlendMode(renderer, canvas_item->blend_mode);
	SDL_RenderDrawLineF(renderer, x_1, y_1, x_2, y_2);
}

Rect2 LineDrawingItem::get_draw_rect() const {
	const Vector2 global_position;
	return Rect2(start_point, end_point).remove_negative_size();
}

void LinesDrawingItem::draw(const Viewport *viewport) {
	if (!canvas_item || points.size() < 2)
		return;

	const Vector2 global_position = canvas_item->get_global_transform().origin;
	const size_t points_size = points.size();
	SDL_Renderer *renderer = viewport->get_renderer();

	SDL_SetRenderDrawColor(renderer, modulate.r, modulate.g, modulate.b, modulate.a);
	SDL_SetRenderDrawBlendMode(renderer, canvas_item->blend_mode);

	for (size_t i = 0; i < points_size; i++) {
		if (i + 1 >= points_size)
			break;

		int x_1 = points[i].x + global_position.x;
		int y_1 = points[i].y + global_position.y;
		int x_2 = points[i + 1].x + global_position.x;
		int y_2 = points[i + 1].y + global_position.y;

		SDL_RenderDrawLineF(renderer, x_1, y_1, x_2, y_2);
	}
}

Rect2 LinesDrawingItem::get_draw_rect() const {
	Rect2 rect;

	for (SDL_FPoint point: points)
		rect.expand_to(point);

	return rect;
}