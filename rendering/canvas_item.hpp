#pragma once

#include <rendering/texture.hpp>
#include <types/transform2d.hpp>
#include <types/rect2.hpp>

#include <vector>

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

struct DrawingItem {
  std::shared_ptr<CanvasItem> canvas_item;

  virtual void draw(SDL_Renderer*) {}
  virtual Rect2 get_draw_rect() const { return Rect2::EMPTY; }
};


struct TextureRectDrawingItem: public DrawingItem {
  std::shared_ptr<Texture> texture;

  Color texture_modulate;
  Rect2i src_region;
  Transform2D transform;
  SDL_RendererFlip flip;
 
  void draw(SDL_Renderer *renderer) override;
  Rect2 get_draw_rect() const override;
};


struct TextureDrawingItem: public DrawingItem {
  std::shared_ptr<Texture> texture;

  Color texture_modulate;
  Transform2D transform;
  SDL_RendererFlip flip;

  void draw(SDL_Renderer *renderer) override;
  Rect2 get_draw_rect() const override;
};
/*
struct LineDrawingItem: public DrawingItem {
  Rect2 rect;
  void draw(SDL_Renderer *renderer) override;
};

struct RectDrawingItem: public DrawingItem {
  Rect2 rect;
  void draw(SDL_Renderer *renderer) override;
};*/

}
