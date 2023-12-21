#include <rendering/texture.hpp>
#include <rendering/rendering_server.hpp>

using namespace sdl;

void Texture2D::set_rendering_server(RenderingServer *new_rendering_server) {
  rendering_server = new_rendering_server;
}

RenderingServer *Texture2D::get_rendering_server() const {
  return rendering_server;
}

void Texture2D::draw(const uid, const uid, const SDL_RendererFlip, const Color&, const Transform2D&) const {
}

void Texture2D::draw_region(const uid, const uid, const Rect2i&, const SDL_RendererFlip, const Color&, const Transform2D&) const {
}


UidTexture::UidTexture() {
}

UidTexture::UidTexture(const uid from_uid) {
  texture_uid = from_uid;
}

Vector2i UidTexture::get_size() const {
  RenderingServer *rendering_server = get_rendering_server();

  return rendering_server ? rendering_server->get_texture_info_from_uid(texture_uid).size : Vector2i::ZERO;
}

void UidTexture::draw(const uid texture_uid,
    const uid canvas_item_uid,
    const SDL_RendererFlip flip,
    const Color &modulate,
    const Transform2D &transform) const
{
  RenderingServer *rendering_server = get_rendering_server();
  if (rendering_server)
    rendering_server->canvas_item_add_texture(texture_uid, canvas_item_uid, flip, modulate, transform);
}

void UidTexture::draw_region(const uid texture_uid,
    const uid canvas_item_uid,
    const Rect2i &src_region,
    const SDL_RendererFlip flip,
    const Color &modulate,
    const Transform2D &transform ) const
{
  RenderingServer *rendering_server = get_rendering_server();
  if (rendering_server)
    rendering_server->canvas_item_add_texture_region(texture_uid, canvas_item_uid, src_region, flip, modulate, transform);
}

void UidTexture::load_from_path(const std::string &file_path) {
  RenderingServer *rendering_server = get_rendering_server();
  if (rendering_server)
    texture_uid = rendering_server->load_texture_from_path(file_path);
}
