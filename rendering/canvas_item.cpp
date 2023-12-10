#include <rendering/canvas_item.hpp>

#include <iostream>

using namespace sdl;

Transform2D CanvasItem::get_global_transform() const {
  Transform2D absolute_transform = transform;
  std::shared_ptr<CanvasItem> parent_canvas_item = parent;

  while (parent_canvas_item) {
    Vector2 new_position = absolute_transform.origin + parent_canvas_item->transform.origin;
    Vector2 new_scale = absolute_transform.scale * parent_canvas_item->transform.scale;
    double new_rotation = absolute_transform.rotation + parent_canvas_item->transform.rotation;

    absolute_transform = Transform2D(new_rotation, new_position, new_scale);
    parent_canvas_item = parent_canvas_item->parent;
  }

  return absolute_transform;
}

void TextureDrawingItem::draw(SDL_Renderer *renderer) {
  if (!canvas_item || !texture)
    return;

  Transform2D global_transform = canvas_item->get_global_transform();

  Rect2 src_region = Rect2(Vector2::ZERO, texture->size);
  Rect2 destination = Rect2(global_transform.origin + transform.origin, (global_transform.scale * transform.scale) * src_region.get_size());

  SDL_Rect final_src_region = src_region.to_sdl_rect();
  SDL_FRect final_destination = destination.to_sdl_frect();

  SDL_FPoint final_offset = transform.origin.to_sdl_fpoint();
  double rotation = global_transform.rotation + transform.rotation;

  SDL_RenderCopyExF(renderer, texture->texture_reference, &final_src_region, &final_destination, rotation, &final_offset, flip);
}

void TextureRectDrawingItem::draw(SDL_Renderer *renderer) {
  if (!canvas_item || !texture)
    return;

  Transform2D global_transform = canvas_item->get_global_transform();
  Rect2 destination = Rect2(global_transform.origin, (global_transform.scale * transform.scale) * src_region.get_size());

  SDL_Rect final_src_region = src_region.to_sdl_rect();
  SDL_FRect final_destination = destination.to_sdl_frect();
  SDL_FPoint offset = transform.origin.to_sdl_fpoint();
  
  double rotation = global_transform.rotation + transform.rotation;
  SDL_RenderCopyExF(renderer, texture->texture_reference, &final_src_region, &final_destination, rotation, &offset, flip);
}

/*void LineDrawingItem::draw(SDL_Renderer *renderer) {
  SDL_RenderDrawLineF(renderer, rect.x, rect.y, rect.x, rect.y);
}

void RectDrawingItem::draw(SDL_Renderer *renderer) {
  SDL_FRect frect = rect.to_sdl_frect();
  SDL_RenderDrawRectF(renderer, &frect);
}*/
