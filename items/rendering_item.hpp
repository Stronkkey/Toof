#ifndef RENDERING_ITEM
#define RENDERING_ITEM

#include <tree.hpp>
#include <items/item.hpp>

namespace sdl {

class RenderingItem : public Item {

protected:
  Vector2 position;
  Vector2 scale;
  uid canvas_item;

  RenderingServer *get_rendering_server() const;
  void update();
  void ready() override;
  void on_parent_changed(Item*) override;

public:
  ~RenderingItem();
  uid get_canvas_item() const;

  void set_position(const Vector2 &new_position);
  Vector2 get_position() const;

  void set_scale(const Vector2 &new_scale);
  Vector2 get_scale() const;

};

}

#endif // !RENDERING_ITEM
