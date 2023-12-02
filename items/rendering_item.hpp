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

  void set_global_position(const Vector2 &new_global_position);
  Vector2 get_global_position() const;

  void set_global_scale(const Vector2 &new_global_scale);
  Vector2 get_global_scale() const;

  void set_global_destination(const Rect2 &new_global_destination);
  Rect2 get_global_destination() const;
};

}

#endif // !RENDERING_ITEM
