#pragma once

#include <types/rect2.hpp>
#include <types/color.hpp>
#include <types/transform2d.hpp>

#include <SDL_render.h>

#include <memory>

namespace sdl {

struct CanvasItem;
struct Texture;
class Viewport;

struct DrawingItem {
  std::shared_ptr<CanvasItem> canvas_item;

  virtual void draw(Viewport *viewport);
  virtual Rect2 get_draw_rect() const;
};


struct TextureRectDrawingItem: public DrawingItem {
  std::shared_ptr<Texture> texture;

  Color texture_modulate;
  Rect2i src_region;
  Transform2D transform;
  SDL_RendererFlip flip;
 
  void draw(Viewport *viewport) override;
  Rect2 get_draw_rect() const override;
};


struct TextureDrawingItem: public DrawingItem {
  std::shared_ptr<Texture> texture;

  Color texture_modulate;
  Transform2D transform;
  SDL_RendererFlip flip;

  void draw(Viewport *viewport) override;
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