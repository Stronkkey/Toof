#ifndef CANVAS_ITEM
#define CANVAS_ITEM

#include <rendering/texture.hpp>

#include <SDL_render.h>

#include <vector>

namespace sdl {

class DrawingItem;

struct CanvasItem {
  Transform2D transform = Transform2D::IDENTITY;
  std::shared_ptr<CanvasItem> parent;
  std::vector<std::shared_ptr<DrawingItem>> drawing_items;

  Transform2D get_global_transform() const;
};

// DrawingItem

class DrawingItem {
public:
  std::shared_ptr<CanvasItem> canvas_item;

  virtual void draw(SDL_Renderer*) {}
};

class TextureRectDrawingItem: public DrawingItem {
public:
  std::shared_ptr<Texture> texture;
  Rect2i src_region;
  Transform2D transform;
  SDL_RendererFlip flip;
  
  void draw(SDL_Renderer *renderer) override;
};

class TextureDrawingItem: public DrawingItem {
public:
  std::shared_ptr<Texture> texture;
  Transform2D transform;
  SDL_RendererFlip flip;

  void draw(SDL_Renderer *renderer) override;
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

#endif // !CANVAS_ITEM
