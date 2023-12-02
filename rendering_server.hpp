#ifndef RENDERING_SERVER
#define RENDERING_SERVER

#include <types/rect2.hpp>
#include <types/ref.hpp>
#include <types/uid.hpp>

#include <SDL2/SDL_image.h>

namespace sdl {

struct Texture {
  SDL_Texture *texture_reference;
  Rect2i src_region;
};

struct CanvasItem {
  Ref<CanvasItem> parent;
  Rect2 destination = Rect2(0, 0, 1, 1);
  std::vector<Texture> textures;

  Rect2 get_global_destination() const;
};

class RenderingServer {

private:
  SDL_Renderer *renderer;
  std::unordered_map<uid, Texture> textures;
  std::unordered_map<uid, Ref<CanvasItem>> canvas_items;

  uid create_new_uid();
  void destroy_uid(uid &destroying_uid);
  uint64_t index = 1;

  void render_canvas_item(const CanvasItem *canvas_item);

  Ref<CanvasItem> get_canvas_item_from_uid(const uid &grab_uid) const;
  Texture get_texture_from_uid(const uid &uid) const;

public:
  RenderingServer(SDL_Renderer *new_renderer);
  ~RenderingServer();

  void render();
  void remove_uid(uid &destroying_uid);

  uid load_texture_from_path(const std::string &path);
  uid create_canvas_item();

  void texture_set_source_region(const uid &texture_uid, const Rect2i &src_region);

  void canvas_item_add_texture(const uid &texture_uid, const uid &canvas_item_uid);
  void canvas_item_add_texture_region(const uid &texture_uid, const uid &canvas_item_uid, const Rect2i &src_region);
  void canvas_item_set_destination(const uid &canvas_item_uid, const Rect2 &new_destination);
  void canvas_item_set_parent(const uid &canvas_item_uid, const uid &parent_item_uid);
  void canvas_item_clear(const uid &canvas_item_uid);
};
}

#endif // !RENDERING_SERVER
