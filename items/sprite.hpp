#ifndef SPRITE_ITEM
#define SPRITE_ITEM

#include <items/rendering_item.hpp>

namespace sdl {

class SpriteItem : public RenderingItem {

private:
  uid texture;
  Rect2i texture_region;

  void update_texture();

public:
  void set_texture(const uid &new_texture);
  uid get_texture() const;

  void set_texture_region(const Rect2i &new_texture_region);
  Rect2i get_texture_region() const;

};

}

#endif // !SPRITE_ITEM
