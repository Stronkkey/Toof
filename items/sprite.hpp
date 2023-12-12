#ifndef SPRITE_ITEM
#define SPRITE_ITEM

#include <items/rendering_item.hpp>
#include <rendering/texture.hpp>

namespace sdl {

class SpriteItem : public RenderingItem {

private:
  std::shared_ptr<Texture2D> texture;
  Rect2i texture_region;
  Transform2D texture_transform;
  SDL_RendererFlip flip;

  void update_texture();

public:
  void set_texture(const std::shared_ptr<Texture2D> &new_texture);
  std::shared_ptr<Texture2D> get_texture() const;

  void set_texture_region(const Rect2i &new_texture_region);
  Rect2i get_texture_region() const;

  void set_offset(const Vector2 &new_offset);
  Vector2 get_offset() const;

  void set_texture_rotation(const double new_rotation);
  double get_texture_rotation() const;

  void set_texture_scale(const Vector2 &new_texture_scale);
  Vector2 get_texture_scale() const;

  void set_texture_transform(const Transform2D &new_texture_transform);
  Transform2D get_texture_transform() const;

  void set_flip(const SDL_RendererFlip new_flip);
  SDL_RendererFlip get_flip() const;
};

}

#endif // !SPRITE_ITEM
