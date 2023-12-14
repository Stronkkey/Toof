#include <items/sprite.hpp>

using namespace sdl;

void SpriteItem::draw_texture() {
  RenderingServer::CanvasItemTexture canvas_item_texture;
  uid texture_uid = texture->get_uid();
  Transform2D new_transform = texture_transform; 

  if (centered)
    new_transform.origin -= texture->get_size() / 2;
  
  canvas_item_texture.canvas_item_uid = canvas_item;
  canvas_item_texture.texture_uid = texture_uid;
  canvas_item_texture.flip = flip;
  canvas_item_texture.transform = &new_transform;

  get_rendering_server()->canvas_item_add_texture(canvas_item_texture);
}

void SpriteItem::draw_rect_texture() {
  RenderingServer::CanvasItemRectTexture canvas_item_rect_texture;
  uid texture_uid = texture->get_uid();
  Transform2D new_transform = texture_transform; 

  if (centered)
    new_transform.origin += texture->get_size() / 2;

  canvas_item_rect_texture.canvas_item_uid = canvas_item;
  canvas_item_rect_texture.texture_uid = texture_uid;
  canvas_item_rect_texture.flip = flip;
  canvas_item_rect_texture.src_region = &texture_region;
  canvas_item_rect_texture.transform = &new_transform;

  get_rendering_server()->canvas_item_add_texture_region(canvas_item_rect_texture);
}

void SpriteItem::update_texture() {
  RenderingServer *rendering_server = get_rendering_server();
  if (!rendering_server || !texture)
    return;

  rendering_server->canvas_item_clear(canvas_item);
  if (texture_region == Rect2i::EMPTY)
    draw_texture();
  else
    draw_rect_texture();
}

void SpriteItem::set_texture(const std::shared_ptr<Texture2D> &new_texture) {
  texture = new_texture;
  update_texture();
}

std::shared_ptr<Texture2D> SpriteItem::get_texture() const {
  return texture;
}

void SpriteItem::set_texture_region(const Rect2i &new_texture_region) {
  texture_region = new_texture_region;
  update_texture();
}

Rect2i SpriteItem::get_texture_region() const {
  return texture_region;
}

void SpriteItem::set_offset(const Vector2 &new_offset) {
  texture_transform.origin = new_offset;
  update_texture();
}

Vector2 SpriteItem::get_offset() const {
  return texture_transform.origin;
}

void SpriteItem::set_flip(const SDL_RendererFlip new_flip) {
  flip = new_flip;
  update_texture();
}

SDL_RendererFlip SpriteItem::get_flip() const {
  return flip;
}

void SpriteItem::set_texture_rotation(const double new_rotation) {
  texture_transform.rotation = new_rotation;
  update_texture();
}

double SpriteItem::get_texture_rotation() const {
  return texture_transform.rotation;
}

void SpriteItem::set_texture_scale(const Vector2 &new_texture_scale) {
  texture_transform.scale = new_texture_scale;
  update_texture();
}

Vector2 SpriteItem::get_texture_scale() const {
  return texture_transform.scale;
}

void SpriteItem::set_texture_transform(const Transform2D &new_texture_transform) {
  texture_transform = new_texture_transform;
  update_texture();
}

void SpriteItem::set_centered(const bool new_centered) {
  centered = new_centered;
  update_texture();
}

bool SpriteItem::is_centered() const {
  return centered;
}
