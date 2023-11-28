#include "rendering_item.hpp"

using namespace sdl;

RenderingItem::RenderingItem() {
}

RenderingItem::RenderingItem(Window *new_window) {
  window = new_window;
  canvas_item = window->rendering_server->create_canvas_item();
}

RenderingItem::~RenderingItem() {
  if (window != nullptr)
    window->rendering_server->remove_uid(canvas_item);
}

uid RenderingItem::get_canvas_item() const {
  return canvas_item;
}

