#ifndef RENDERING_SERVER
#define RENDERING_SERVER

#include "uid.hpp"

#include <SDL.h>

#include <string>
#include <vector>

namespace sdl {

class RenderingServer {
private:
  SDL_Renderer *renderer;
  std::unordered_map<uid, SDL_Texture*> textures;

  uid create_new_uid();
  void destroy_uid(uid &destroying_uid);
  uint64_t index = 0;

public:
  RenderingServer(SDL_Renderer *new_renderer);
  ~RenderingServer();

  void render();
  void remove_uid(uid &destroying_uid);

  uid load_texture_from_path(const std::string &path);
};
}

#endif // !RENDERING_SERVER
