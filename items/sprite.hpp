#ifndef SPRITE_ITEM
#define SPRITE_ITEM

#include "rendering_item.hpp"

namespace sdl {

class SpriteItem : public RenderingItem {
private:
  Texture *texture;

public:
  void set_texture(Texture *new_texture);
  Texture *get_texture();

};

}

#endif // !SPRITE_ITEM
