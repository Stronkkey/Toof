#ifndef SPRITE_ITEM
#define SPRITE_ITEM

#include <items/rendering_item.hpp>

namespace sdl {

class SpriteItem : public RenderingItem {
private:
  uid texture;

public:
  void set_texture(const uid &new_texture);
  uid get_texture() const;

};

}

#endif // !SPRITE_ITEM
