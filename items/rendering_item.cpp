#include <items/rendering_item.hpp>

#include <typeinfo>

using namespace sdl;

void RenderingItem::ready() {
  transform = transform.IDENTITY;

  canvas_item = get_rendering_server()->create_canvas_item();
  update();
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
    rendering_server->canvas_item_set_transform(canvas_item, transform); 
}

void RenderingItem::on_parent_changed(Item *new_parent) {
  RenderingServer *rendering_server = get_rendering_server();
  if (!rendering_server)
    return;

  RenderingItem *rendering_item = dynamic_cast<RenderingItem*>(new_parent);

  if (rendering_item)
    rendering_server->canvas_item_set_parent(canvas_item, rendering_item->get_canvas_item());
  else
    rendering_server->canvas_item_set_parent(canvas_item, uid());
}

uid RenderingItem::get_canvas_item() const {
  return canvas_item;
}

void RenderingItem::set_position(const Vector2 &new_position) {
  transform.origin = new_position;
  update();
}

Vector2 RenderingItem::get_position() const {
  return transform.origin;
}

void RenderingItem::set_scale(const Vector2 &new_scale) {
  transform.scale = new_scale;
  update();
}

Vector2 RenderingItem::get_scale() const {
  return transform.scale;
}

void RenderingItem::set_global_position(const Vector2 &new_global_position) {
  RenderingServer *rendering_server = get_rendering_server();
  Vector2 global_position = rendering_server ? rendering_server->canvas_item_get_global_transform(canvas_item).origin : transform.origin;
  set_position(-Vector2(global_position - new_global_position));
}

Vector2 RenderingItem::get_global_position() const {
  RenderingServer *rendering_server = get_rendering_server();
  return rendering_server ? rendering_server->canvas_item_get_global_transform(canvas_item).origin : transform.origin;
}

void RenderingItem::set_global_scale(const Vector2 &new_global_scale) {
  RenderingServer *rendering_server = get_rendering_server();
  Vector2 global_scale = rendering_server ? rendering_server->canvas_item_get_global_transform(canvas_item).scale : transform.scale;
  set_scale(-Vector2(global_scale - new_global_scale));
}

Vector2 RenderingItem::get_global_scale() const {
  RenderingServer *rendering_server = get_rendering_server();

  if (rendering_server)
    return rendering_server->canvas_item_get_global_transform(canvas_item).scale;
  return transform.scale;
}

void RenderingItem::set_global_transform(const Transform2D &new_global_transform) {
  transform = new_global_transform;
  update();
}

Transform2D RenderingItem::get_global_transform() const {
  RenderingServer *rendering_server = get_rendering_server();

  if (rendering_server)
    return rendering_server->canvas_item_get_global_transform(canvas_item);
  return transform;
}
