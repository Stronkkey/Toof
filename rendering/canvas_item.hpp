#pragma once

#include <rendering/texture.hpp>
#include <types/transform2d.hpp>

#include <vector>
#include <memory>

namespace sdl {

struct DrawingItem;

struct CanvasItem {
  Transform2D transform = Transform2D::IDENTITY;
  Color modulate = Color::WHITE;
  bool visible = true;

  SDL_BlendMode blend_mode = SDL_BLENDMODE_BLEND;

  std::shared_ptr<CanvasItem> parent;
  std::vector<std::shared_ptr<DrawingItem>> drawing_items;

  Transform2D get_global_transform() const;
  Color get_absolute_modulate() const;
  bool is_visible() const;
};

// DrawingItem

}
