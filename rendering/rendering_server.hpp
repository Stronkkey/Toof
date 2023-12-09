#ifndef RENDERING_SERVER
#define RENDERING_SERVER

#include <types/transform2d.hpp>
#include <types/rect2.hpp>
#include <types/uid.hpp>

#include <SDL2/SDL_image.h>

#include <memory>

namespace sdl {

struct DrawingItem {
  virtual void draw(SDL_Renderer*) {}
};

struct Texture {
  SDL_Texture *texture_reference;
  Rect2i src_region;
  Vector2 offset;
  SDL_RendererFlip flip;
};

struct CanvasItem {
  Transform2D transform = Transform2D::IDENTITY;
  std::shared_ptr<CanvasItem> parent;
  std::vector<Texture> textures;
  std::vector<DrawingItem> drawing_items;

  Transform2D get_global_transform() const;
};

struct LineDrawingItem: public DrawingItem {
  Rect2 rect;
  void draw(SDL_Renderer *renderer) override;
};

struct RectDrawingItem: public DrawingItem {
  Rect2 rect;
  void draw(SDL_Renderer *renderer) override;
};

class RenderingServer {

private:
  SDL_Renderer *renderer;
  std::unordered_map<uid, Texture> textures;
  std::unordered_map<uid, std::shared_ptr<CanvasItem>> canvas_items;

  uid create_new_uid();
  void destroy_uid(uid &destroying_uid);
  uint_t index = 1;

  void render_canvas_item(const std::shared_ptr<CanvasItem> canvas_item);

  std::shared_ptr<CanvasItem> get_canvas_item_from_uid(const uid &grab_uid) const;
  Texture get_texture_from_uid(const uid &uid) const;

public:
  RenderingServer();
  RenderingServer(SDL_Renderer *new_renderer);
  ~RenderingServer();

  void render();
  void remove_uid(uid &destroying_uid);

  uid load_texture_from_path(const std::string &path);
  uid create_canvas_item();

  void texture_set_source_region(const uid &texture_uid, const Rect2i &src_region);

  Rect2i texture_get_source_region(const uid &texture_uid) const;

  void canvas_item_add_texture(const uid &texture_uid, const uid &canvas_item_uid);
  void canvas_item_add_texture_region(const uid &texture_uid, const uid &canvas_item_uid, const Rect2i &src_region);
  void canvas_item_set_transform(const uid &canvas_item_uid, const Transform2D &new_transform);
  void canvas_item_set_parent(const uid &canvas_item_uid, const uid &parent_item_uid);
  void canvas_item_clear(const uid &canvas_item_uid);

  Transform2D canvas_item_get_transform(const uid &canvas_item_uid) const;
  Transform2D canvas_item_get_global_transform(const uid &canvas_item_uid) const;
};
}

#endif // !RENDERING_SERVER
