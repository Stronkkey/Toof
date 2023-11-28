#ifndef RENDERING_SERVER
#define RENDERING_SERVER

#include "rect2.hpp"
#include "uid.hpp"

#include <SDL_image.h>

#include <string>
#include <vector>

namespace sdl {

struct Texture {
  SDL_Texture *texture_reference;
  Rect2i src_region;
};

struct CanvasItem {
  Rect2 destination;
  std::unordered_map<uid, Texture*> textures;
};

class RenderingServer {
private:
  SDL_Renderer *renderer;
  std::unordered_map<uid, Texture*> textures;
  std::unordered_map<uid, CanvasItem*> canvas_items;

  uid create_new_uid();
  void destroy_uid(uid &destroying_uid);
  uint64_t index = 0;

  void render_canvas_item(const CanvasItem *canvas_item);

public:
  RenderingServer(SDL_Renderer *new_renderer);
  ~RenderingServer();

  void render();
  void remove_uid(uid &destroying_uid);

  uid load_texture_from_path(const std::string &path);
  uid create_canvas_item();

  void canvas_item_add_texture(const uid &texture_uid, const uid &canvas_item_uid);
  void canvas_item_add_texture_region(const uid &texture_uid, const uid &canvas_item_uid, const Rect2i &src_region);
  void canvas_item_remove_texture(const uid &texture_uid, const uid &canvas_item_uid);
};
}

#endif // !RENDERING_SERVER
