#pragma once

#include <types/transform2d.hpp>
#include <types/rect2.hpp>
#include <types/color.hpp>

#include <SDL_image.h>

namespace sdl {

class RenderingServer;

struct Texture {
  SDL_Texture *texture_reference;
  Vector2i size;
  uint32_t format;
};

class Texture2D {

public:
  virtual Vector2i get_size() const { return Vector2i::ZERO; }
  virtual int get_width() const { return int(get_size().x); }
  virtual int get_height() const { return int(get_size().y); }
  virtual uid get_uid() const { return 0; }

  virtual void draw(RenderingServer *rendering_server,
    const uid texture_uid,
    const uid canvas_item_uid,
    const SDL_RendererFlip flip = SDL_FLIP_NONE,
    const Color &modulate = Color::WHITE,
    const Transform2D &transform = Transform2D::IDENTITY) const;

  virtual void draw_region(RenderingServer *rendering_server,
    const uid texture_uid,
    const uid canvas_item_uid,
    const Rect2i &src_region,
    const SDL_RendererFlip flip = SDL_FLIP_NONE,
    const Color &modulate = Color::WHITE,
    const Transform2D &transform = Transform2D::IDENTITY) const;

};

class UidTexture : public Texture2D {

private:
  uid texture_uid;

public:
  UidTexture();
  UidTexture(const uid from_uid);

  Vector2i get_size() const override;
  Vector2i get_size(RenderingServer *rendering_server) const;
  uid get_uid() const override { return texture_uid; }

  void draw(RenderingServer *rendering_server,
    const uid texture_uid,
    const uid canvas_item_uid,
    const SDL_RendererFlip flip = SDL_FLIP_NONE,
    const Color &modulate = Color::WHITE,
    const Transform2D &transform = Transform2D::IDENTITY) const override;

  void draw_region(RenderingServer *rendering_server,
    const uid texture_uid,
    const uid canvas_item_uid,
    const Rect2i &src_region,
    const SDL_RendererFlip flip = SDL_FLIP_NONE,
    const Color &modulate = Color::WHITE,
    const Transform2D &transform = Transform2D::IDENTITY) const override;

  void load_from_path(RenderingServer *rendering_server, const std::string &file_path);
};

}
