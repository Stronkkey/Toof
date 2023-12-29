#include <rendering/canvas_item.hpp>
#include <rendering/drawing_item.hpp>
#include <rendering/viewport.hpp>

using namespace sdl;

void DrawingItem::draw(const Viewport*) {
}

Rect2 DrawingItem::get_draw_rect(const Viewport*) const {
	return Rect2::EMPTY;
}

Rect2 TextureDrawingItem::get_draw_rect(const Viewport *viewport) const {
	Transform2D global_transform = canvas_item->get_global_transform() * viewport->get_canvas_transform();
	return Rect2(global_transform.origin + transform.origin, (global_transform.scale * transform.scale) * texture->size);
}

void TextureDrawingItem::draw(const Viewport *viewport) {
	if (!canvas_item || !texture)
		return;

	Transform2D global_transform = canvas_item->get_global_transform() * viewport->get_canvas_transform();
	Rect2 src_region = Rect2(Vector2::ZERO, texture->size);

	double rotation = global_transform.rotation + transform.rotation;
	Color modulate = texture_modulate * canvas_item->get_absolute_modulate();

	SDL_SetTextureAlphaMod(texture->texture_reference, modulate.a);
	SDL_SetTextureColorMod(texture->texture_reference, modulate.r, modulate.g, modulate.b);
	SDL_SetTextureBlendMode(texture->texture_reference, canvas_item->blend_mode);

	draw_texture(viewport, src_region.to_sdl_rect(), get_draw_rect(viewport).to_sdl_frect(), rotation, SDL_FPoint());
}

void TextureDrawingItem::draw_texture(const Viewport *viewport,
        const SDL_Rect &src_region,
        const SDL_FRect &destination,
        const double rotation,
        const SDL_FPoint &center)	{
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

Rect2 TextureRectDrawingItem::get_draw_rect(const Viewport *viewport) const {
	Transform2D global_transform = canvas_item->get_global_transform() * viewport->get_canvas_transform();
	return Rect2(global_transform.origin, (global_transform.scale * transform.scale) * src_region.get_size());
}

void TextureRectDrawingItem::draw(const Viewport *viewport) {
	if (!canvas_item || !texture)
		return;

	Transform2D global_transform = canvas_item->get_global_transform();

	double rotation = global_transform.rotation + transform.rotation;
	Color modulate = texture_modulate * canvas_item->get_absolute_modulate();

	SDL_SetTextureColorMod(texture->texture_reference, modulate.r, modulate.g, modulate.b);
	SDL_SetTextureAlphaMod(texture->texture_reference, modulate.a);
	SDL_SetTextureBlendMode(texture->texture_reference, canvas_item->blend_mode);

	draw_texture(viewport,
	    src_region.to_sdl_rect(),
	    get_draw_rect(viewport).to_sdl_frect(),
	    rotation);
}

void TextureRectDrawingItem::draw_texture(const Viewport *viewport,
      const SDL_Rect &src_region,
      const SDL_FRect &destination,
      const double rotation,
      const SDL_FPoint &center)
{
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
