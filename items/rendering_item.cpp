#include <items/rendering_item.hpp>
#include <rendering_server.hpp>
#include <tree.hpp>
#include <window.hpp>
#include <types/vector2.hpp>

#include <typeinfo>

using namespace sdl;

void RenderingItem::ready() {
  RenderingServer *rendering_server = get_rendering_server();
  if (!rendering_server)
    return;

  canvas_item = rendering_server->create_canvas_item();
  rendering_server->canvas_item_set_destination(canvas_item, Rect2(0, 0, 1, 1));
}

RenderingItem::~RenderingItem() {
  RenderingServer *rendering_server = get_rendering_server();
  if (rendering_server)
    rendering_server->remove_uid(canvas_item);
}

RenderingServer *RenderingItem::get_rendering_server() const {
  Window *window = get_tree() ? get_tree()->get_window() : nullptr;
  return window ? window->rendering_server : nullptr;
}

void RenderingItem::update() {
  RenderingServer *rendering_server = get_rendering_server();
  if (rendering_server)
    rendering_server->canvas_item_set_destination(canvas_item, Rect2(position, scale)); 
}

void RenderingItem::on_parent_changed(Item *new_parent) {
  RenderingServer *rendering_server = get_rendering_server();
  if (!rendering_server)
    return;

  RenderingItem *rendering_item = static_cast<RenderingItem*>(new_parent);
  if (new_parent == nullptr || typeid(new_parent) != typeid(RenderingItem))
    rendering_server->canvas_item_set_parent(canvas_item, uid());
  else if (new_parent != nullptr)
    rendering_server->canvas_item_set_parent(canvas_item, rendering_item->canvas_item);
}

uid RenderingItem::get_canvas_item() const {
  return canvas_item;
}

void RenderingItem::set_position(const Vector2 &new_position) {
  position = new_position;
  update();
}

Vector2 RenderingItem::get_position() const {
  return position;
}

void RenderingItem::set_scale(const Vector2 &new_scale) {
  scale = new_scale;
  update();
}

Vector2 RenderingItem::get_scale() const {
  return scale;
}
