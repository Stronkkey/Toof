#ifndef RENDERING_ITEM
#define RENDERING_ITEM

#include "window.hpp"

namespace sdl {

class RenderingItem {

private:
  uid canvas_item;
  Window *window = nullptr;

public:
  RenderingItem();
  RenderingItem(Window *new_window);
  ~RenderingItem();

  Vector2 position;
  Vector2 scale;

  uid get_canvas_item() const;

};

}

#endif // !RENDERING_ITEM
