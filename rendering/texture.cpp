#include <rendering/texture.hpp>
#include <rendering/rendering_server.hpp>

using namespace sdl;

void Texture2D::set_rendering_server(RenderingServer *new_rendering_server) {
  rendering_server = new_rendering_server;
}

UidTexture::UidTexture() {
}

UidTexture::UidTexture(const uid &from_uid) {
  texture_uid = from_uid;
}

Vector2i UidTexture::get_size() const {
  if (!rendering_server)
    return Vector2i::ZERO;
  return rendering_server->get_texture_info_from_uid(texture_uid).size;
}

void UidTexture::draw(const RenderingServer::CanvasItemTexture &draw_operation) const {
  if (!rendering_server)
    return;

  rendering_server->canvas_item_add_texture(draw_operation);
}

void UidTexture::draw_region(const RenderingServer::CanvasItemRectTexture &rect_draw_operation) const {
  if (!rendering_server)
    return;

  rendering_server->canvas_item_add_texture_region(rect_draw_operation);
}

void UidTexture::load_from_path(const std::string &file_path) {
  if (!rendering_server)
    return;
  texture_uid = rendering_server->load_texture_from_path(file_path);
}
