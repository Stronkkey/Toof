#include "types/utility_functions.hpp"
#include <items/rendering_item.hpp>
#include <rendering/window.hpp>
#include <items/tree.hpp>

#include <typeinfo>

using namespace sdl;

void RenderingItem::ready() {
  transform = transform.IDENTITY;
  canvas_item = get_rendering_server()->create_canvas_item();

  update();
  sdl::UtilityFunctions::print(std::to_string(canvas_item));
}

RenderingItem::~RenderingItem() {
  RenderingServer *rendering_server = get_rendering_server();

  if (rendering_server)
    rendering_server->remove_uid(canvas_item);
}

RenderingServer *RenderingItem::get_rendering_server() const {
  return get_tree() ? get_tree()->get_rendering_server() : nullptr;
}

void RenderingItem::update() {
  RenderingServer *rendering_server = get_rendering_server();

  if (rendering_server) {
    rendering_server->canvas_item_set_transform(canvas_item, transform);
    rendering_server->canvas_item_set_modulate(canvas_item, modulate);
    rendering_server->canvas_item_set_blend_mode(canvas_item, blend_mode);
    rendering_server->canvas_item_set_visible(canvas_item, visible);
  }
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

void RenderingItem::draw() const {
}

uid RenderingItem::get_canvas_item() const {
  return canvas_item;
}

void RenderingItem::redraw() const {
  draw();
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

void RenderingItem::set_rotation(const double new_rotation) {
  transform.rotation = new_rotation;
  update();
}

double RenderingItem::get_rotation() const {
  return transform.rotation;
}

void RenderingItem::set_global_position(const Vector2 &new_global_position) {
  RenderingServer *rendering_server = get_rendering_server();
  
  Vector2 global_position = transform.origin;
  if (rendering_server)
    global_position = rendering_server->canvas_item_get_global_transform(canvas_item).origin;
  set_position(-Vector2(global_position - new_global_position));
}

Vector2 RenderingItem::get_global_position() const {
  RenderingServer *rendering_server = get_rendering_server();

  if (rendering_server)
    return rendering_server->canvas_item_get_transform(canvas_item).origin;
  return transform.origin;
}

void RenderingItem::set_global_scale(const Vector2 &new_global_scale) {
  RenderingServer *rendering_server = get_rendering_server();

  Vector2 global_scale = transform.scale;
  if (rendering_server)
    global_scale = rendering_server->canvas_item_get_global_transform(canvas_item).scale;
  set_scale(-Vector2(global_scale - new_global_scale));
}

Vector2 RenderingItem::get_global_scale() const {
  RenderingServer *rendering_server = get_rendering_server();

  if (rendering_server)
    return rendering_server->canvas_item_get_global_transform(canvas_item).scale;
  return transform.scale;
}

void RenderingItem::set_global_rotation(const double new_global_rotation) {
  RenderingServer *rendering_server = get_rendering_server();

  double global_rotation = transform.rotation;
  if (rendering_server)
    global_rotation = rendering_server->canvas_item_get_global_transform(canvas_item).rotation;
  set_rotation(-(global_rotation - new_global_rotation));
}

double RenderingItem::get_global_rotation() const {
  RenderingServer *rendering_server = get_rendering_server();

  if (rendering_server)
    return rendering_server->canvas_item_get_global_transform(canvas_item).rotation;
  return transform.rotation;
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

void RenderingItem::set_modulate(const Color &new_modulate) {
  modulate = new_modulate;
  update();
}

Color RenderingItem::get_modulate() const {
  return modulate;
}

Color RenderingItem::get_absolute_modulate() const {
  RenderingServer *rendering_server = get_rendering_server();
  return rendering_server ? rendering_server->canvas_item_get_global_modulate(canvas_item) : modulate;
}

void RenderingItem::set_blend_mode(const SDL_BlendMode new_blend_mode) {
  blend_mode = new_blend_mode;
  update();
}

SDL_BlendMode RenderingItem::get_blend_mode() const {
  return blend_mode;
}

void RenderingItem::set_visible(const bool new_visible) {
  visible = new_visible;
  update();
}

bool RenderingItem::is_visible() const {
  return visible;
}

bool RenderingItem::is_visible_in_tree() const {
  RenderingServer *rendering_server = get_rendering_server();
  return rendering_server ? rendering_server->canvas_item_is_globally_visible(canvas_item) : true;
}
