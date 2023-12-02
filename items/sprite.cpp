#include <items/sprite.hpp>

using namespace sdl;

void SpriteItem::update_texture() {
  RenderingServer *rendering_server = get_rendering_server();
  if (!rendering_server)
    return;

  rendering_server->canvas_item_clear(canvas_item);

  if (texture_region == Rect2i::EMPTY)
    rendering_server->canvas_item_add_texture_region(texture, canvas_item, rendering_server->texture_get_source_region(texture));
  else
   rendering_server->canvas_item_add_texture_region(texture, canvas_item, texture_region);
}

void SpriteItem::set_texture(const uid &new_texture) {
  texture = new_texture;
  update_texture();
}

uid SpriteItem::get_texture() const {
  return texture;
}

void SpriteItem::set_texture_region(const Rect2i &new_texture_region) {
  texture_region = new_texture_region;
  update_texture();
}

Rect2i SpriteItem::get_texture_region() const {
  return texture_region;
}
