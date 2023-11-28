#include "rendering_server.hpp"

#include <SDL_image.h>

using namespace sdl;

RenderingServer::RenderingServer(SDL_Renderer *new_renderer) {
  renderer = new_renderer;
}

RenderingServer::~RenderingServer() {
}

void RenderingServer::render() {
  if (!renderer)
    return;

  for (auto iterator: textures) {
    SDL_RenderCopy(renderer, iterator.second, NULL, NULL);
  }
}

void RenderingServer::remove_uid(uid &destroying_uid) {
  destroy_uid(destroying_uid);
}

uid RenderingServer::create_new_uid() {
  uid new_uid;
  new_uid.id = index;
  index++;
  return new_uid;
}

void RenderingServer::destroy_uid(uid &destroying_uid) {
  auto iterator = textures.find(destroying_uid);
  
  if (iterator != textures.end()) {
    textures.erase(iterator);
    delete iterator->second;
  }
}

uid RenderingServer::load_texture_from_path(const std::string &path) {
  uid new_uid = create_new_uid();
  SDL_Texture *texture = IMG_LoadTexture(renderer, path.c_str());

  if (texture == NULL)
    return uid();
  
  textures.insert({new_uid, texture});
  return new_uid;
}
