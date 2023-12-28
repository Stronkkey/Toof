#include <rendering/canvas_item.hpp>
#include <rendering/drawing_item.hpp>
#include <rendering/viewport.hpp>

using namespace sdl;

void DrawingItem::draw(Viewport*) {
}

Rect2 DrawingItem::get_draw_rect() const {
  return Rect2::EMPTY;
}

Rect2 TextureDrawingItem::get_draw_rect() const {
  Transform2D global_transform = canvas_item->get_global_transform();
  return Rect2(global_transform.origin + transform.origin, (global_transform.scale * transform.scale) * texture->size);
}

void TextureDrawingItem::draw(Viewport *viewport) {
  if (!canvas_item || !texture)
    return;

  Transform2D global_transform = canvas_item->get_global_transform();

  Rect2 src_region = Rect2(Vector2::ZERO, texture->size);

  SDL_Rect final_src_region = src_region.to_sdl_rect();
  SDL_FRect final_destination = get_draw_rect().to_sdl_frect();

  double rotation = global_transform.rotation + transform.rotation;
  Color modulate = texture_modulate * canvas_item->get_absolute_modulate();

  SDL_SetTextureAlphaMod(texture->texture_reference, modulate.a);
  SDL_SetTextureColorMod(texture->texture_reference, modulate.r, modulate.g, modulate.b);
  SDL_SetTextureBlendMode(texture->texture_reference, canvas_item->blend_mode);

  if (rotation == 0.0)
    SDL_RenderCopyF(viewport->get_renderer(),
	    texture->texture_reference,
		&final_src_region,
		&final_destination);
  else
    SDL_RenderCopyExF(viewport->get_renderer(),
	    texture->texture_reference,
		&final_src_region,
		&final_destination,
		rotation,
		NULL, flip);
}


Rect2 TextureRectDrawingItem::get_draw_rect() const {
  Transform2D global_transform = canvas_item->get_global_transform();
  return Rect2(global_transform.origin, (global_transform.scale * transform.scale) * src_region.get_size());
}

void TextureRectDrawingItem::draw(Viewport *viewport) {
  if (!canvas_item || !texture)
    return;

  Transform2D global_transform = canvas_item->get_global_transform();

  SDL_Rect final_src_region = src_region.to_sdl_rect();
  SDL_FRect final_destination = get_draw_rect().to_sdl_frect();

  double rotation = global_transform.rotation + transform.rotation;
  Color modulate = texture_modulate * canvas_item->get_absolute_modulate();

  SDL_SetTextureColorMod(texture->texture_reference, modulate.r, modulate.g, modulate.b);
  SDL_SetTextureAlphaMod(texture->texture_reference, modulate.a);
  SDL_SetTextureBlendMode(texture->texture_reference, canvas_item->blend_mode);

  if (rotation == 0.0)
    SDL_RenderCopyF(viewport->get_renderer(),
	    texture->texture_reference,
		&final_src_region,
		&final_destination);
  else
    SDL_RenderCopyExF(viewport->get_renderer(),
	    texture->texture_reference,
		&final_src_region,
		&final_destination,
		rotation,
		NULL,
		flip);
}

/*void LineDrawingItem::draw(SDL_Renderer *renderer) {
  SDL_RenderDrawLineF(renderer, rect.x, rect.y, rect.x, rect.y);
}

void RectDrawingItem::draw(SDL_Renderer *renderer) {
  SDL_FRect frect = rect.to_sdl_frect();
  SDL_RenderDrawRectF(renderer, &frect);
}*/
