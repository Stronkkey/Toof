#include "sprite.hpp"

using namespace sdl;

void SpriteItem::set_texture(Texture *new_texture) {
  texture = new_texture;
  RenderingServer *rendering_server = get_rendering_server();
  if (rendering_server && texture) {
    rendering_server->canvas_item_clear(canvas_item);
    rendering_server->canvas_item_add_texture(new_texture, canvas_item);
  }
}

Texture *SpriteItem::get_texture() {
  return texture;
}
