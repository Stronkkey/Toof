#ifndef RENDERING_SERVER
#define RENDERING_SERVER

#include <types/rect2.hpp>
#include <types/transform2d.hpp>
#include <types/uid.hpp>

#include <SDL_image.h>

#include <memory>

namespace sdl {

struct Texture;
struct CanvasItem;

class RenderingServer {

private:
  SDL_Renderer *renderer;
  std::unordered_map<uid, std::shared_ptr<Texture>> textures;
  std::unordered_map<uid, std::shared_ptr<CanvasItem>> canvas_items;

  uid create_new_uid();
  void destroy_uid(uid &destroying_uid);
  uint_t index = 1;

  void render_canvas_item(const std::shared_ptr<CanvasItem> &canvas_item);

  std::shared_ptr<CanvasItem> get_canvas_item_from_uid(const uid &grab_uid) const;
  std::shared_ptr<Texture> get_texture_from_uid(const uid &uid) const;

public:
  struct TextureInfo {
    Vector2i size;
    uint32_t format;
  };

public:
  RenderingServer();
  RenderingServer(SDL_Renderer *new_renderer);
  ~RenderingServer();

  void render();
  void remove_uid(uid &destroying_uid);

  uid load_texture_from_path(const std::string &path);
  uid create_canvas_item();

  TextureInfo get_texture_info_from_uid(const uid &texture_uid) const;

  void canvas_item_add_texture(const uid &texture_uid,
    const uid &canvas_item_uid,
    const Transform2D &transform = Transform2D::IDENTITY,
    const SDL_RendererFlip flip = SDL_FLIP_NONE);

  void canvas_item_add_texture_region(const uid &texture_uid,
    const uid &canvas_item_uid,
    const Rect2i &src_region,
    const Transform2D &transform = Transform2D::IDENTITY,
    const SDL_RendererFlip flip = SDL_FLIP_NONE);

  void canvas_item_set_transform(const uid &canvas_item_uid, const Transform2D &new_transform);
  void canvas_item_set_parent(const uid &canvas_item_uid, const uid &parent_item_uid);
  void canvas_item_clear(const uid &canvas_item_uid);

  Transform2D canvas_item_get_transform(const uid &canvas_item_uid) const;
  Transform2D canvas_item_get_global_transform(const uid &canvas_item_uid) const;
};
}

#endif // !RENDERING_SERVER
