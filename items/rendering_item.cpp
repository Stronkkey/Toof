#include <iostream>
#include <items/rendering_item.hpp>

#include <typeinfo>

using namespace sdl;

void RenderingItem::ready() {
  scale = Vector2::ONE;
  position = Vector2::ZERO;
  RenderingServer *rendering_server = get_rendering_server();
  
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

  RenderingItem *rendering_item = dynamic_cast<RenderingItem*>(new_parent);

  if (rendering_item)
    rendering_server->canvas_item_set_parent(canvas_item, rendering_item->canvas_item);
  else
    rendering_server->canvas_item_set_parent(canvas_item, uid());
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
