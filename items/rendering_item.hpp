#pragma once

#include <items/item.hpp>

#include <types/transform2d.hpp>
#include <types/color.hpp>
#include <rendering/rendering_server.hpp>

namespace sdl {

class RenderingItem : public Item {

public:
  enum {
    NOTIFICATION_DRAW = 900,
    NOTIFICATION_VISIBILITY_CHANGED,
    NOTIFICATION_ENTER_CANVAS,
    NOTIFICATION_EXIT_CANVAS
  };

private:
  Transform2D transform;
  uid canvas_item;
  Color modulate = Color::WHITE;
  SDL_BlendMode blend_mode = SDL_BLENDMODE_BLEND;
  bool visible = true;

  void update();
  void on_parent_changed(Item *new_parent);
  void ready();

protected:
  RenderingServer *get_rendering_server() const;

  void _notification(const int what);
  virtual void _draw() const;

public:
  ~RenderingItem();

  uid get_canvas_item() const;
  void redraw();

  void set_position(const Vector2 &new_position);
  Vector2 get_position() const;

  void set_scale(const Vector2 &new_scale);
  Vector2 get_scale() const;

  void set_rotation(const double new_rotation);
  double get_rotation() const;

  void set_global_position(const Vector2 &new_global_position);
  Vector2 get_global_position() const;

  void set_global_scale(const Vector2 &new_global_scale);
  Vector2 get_global_scale() const;

  void set_global_rotation(const double new_global_rotation);
  double get_global_rotation() const;

  void set_transform(const Transform2D &new_transform);
  Transform2D get_transform() const;

  void set_global_transform(const Transform2D &new_global_transform);
  Transform2D get_global_transform() const;

  void set_modulate(const Color &new_modulate);
  Color get_modulate() const;
  Color get_absolute_modulate() const;

  void set_blend_mode(const SDL_BlendMode new_blend_mode);
  SDL_BlendMode get_blend_mode() const;

  void set_visible(const bool new_visible);
  bool is_visible() const;
  bool is_visible_in_tree() const;
};

}
