#include "sprite.hpp"

using namespace sdl;

void SpriteItem::set_texture(const uid &new_texture) {
  texture = new_texture;
  RenderingServer *rendering_server = get_rendering_server();
  if (rendering_server) {
    rendering_server->canvas_item_clear(canvas_item);
    rendering_server->canvas_item_add_texture(new_texture, canvas_item);
  }
}

uid SpriteItem::get_texture() const {
  return texture;
}
