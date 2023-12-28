#include <rendering/canvas_item.hpp>
#include <rendering/drawing_item.hpp>

using namespace sdl;

Transform2D CanvasItem::get_global_transform() const {
  Transform2D absolute_transform = transform;
  std::shared_ptr<CanvasItem> parent_canvas_item = parent;

  while (parent_canvas_item) {
    Vector2 new_position = absolute_transform.origin + parent_canvas_item->transform.origin;
    Vector2 new_scale = absolute_transform.scale * parent_canvas_item->transform.scale;
    double new_rotation = absolute_transform.rotation + parent_canvas_item->transform.rotation;

    absolute_transform = Transform2D(new_rotation, new_position, new_scale);
    parent_canvas_item = parent_canvas_item->parent;
  }

  return absolute_transform;
}

Color CanvasItem::get_absolute_modulate() const {
  Color absolute_modulate = modulate;
  std::shared_ptr<CanvasItem> parent_canvas_item = parent;

  while (parent_canvas_item) {
    absolute_modulate *= parent_canvas_item->modulate;
    parent_canvas_item = parent_canvas_item->parent;
  }

  return absolute_modulate;
}

bool CanvasItem::is_visible() const {
  std::shared_ptr<CanvasItem> parent_canvas_item = parent;
  
  while (parent_canvas_item) {
    if (!parent_canvas_item->visible)
      return false;

    parent_canvas_item = parent_canvas_item->parent;
  }

  return true;
}