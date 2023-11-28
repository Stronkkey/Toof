#include "rendering_server.hpp"
#include <iostream>

using namespace sdl;

RenderingServer::RenderingServer(SDL_Renderer *new_renderer) {
  renderer = new_renderer;
}

RenderingServer::~RenderingServer() {
}

void RenderingServer::render() {
  if (!renderer)
    return;

  for (auto iterator: canvas_items) {
    render_canvas_item(iterator.second);
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
  auto canvas_item_iterator = canvas_items.find(destroying_uid);
  auto texture_iterator = textures.find(destroying_uid);
  
  if (canvas_item_iterator != canvas_items.end()) {
    canvas_items.erase(canvas_item_iterator);
  }

  if (texture_iterator != textures.end()) {
    SDL_DestroyTexture(texture_iterator->second->texture_reference);
    textures.erase(texture_iterator);
  }

}

void RenderingServer::render_canvas_item(const CanvasItem *canvas_item) {
  for (std::pair<uid, Texture*> iterator: canvas_item->textures) {
    auto texture_iterator = textures.find(iterator.first);

    if (texture_iterator != textures.end()) {
      Texture *texture = texture_iterator->second;
      SDL_Rect src_region = texture->src_region.to_sdl_rect();
      SDL_Rect destination = (canvas_item->destination + src_region).to_sdl_rect();

      SDL_RenderCopy(renderer, texture->texture_reference, &src_region, &destination);
    }

  }
}

uid RenderingServer::load_texture_from_path(const std::string &path) {
  SDL_Texture *texture = IMG_LoadTexture(renderer, path.c_str());

  if (texture == NULL)
    return uid();
  
  uid new_uid = create_new_uid();
  Texture *new_texture = new Texture;

  new_texture->texture_reference = texture;
  new_texture->src_region = Rect2i::EMPTY;
  new_uid.type = UID_RENDERING_TEXTURE;
  
  textures.insert({new_uid, new_texture});
  return new_uid;
}

uid RenderingServer::create_canvas_item() {
  uid new_uid = create_new_uid();
  CanvasItem *canvas_item = new CanvasItem;
  new_uid.type = UID_RENDERING;
  canvas_items.insert({new_uid, canvas_item});
  return new_uid;
}

void RenderingServer::canvas_item_add_texture(const uid &texture_uid, const uid &canvas_item_uid) {
  auto texture_iterator = textures.find(texture_uid);
  auto canvas_item_iterator = canvas_items.find(canvas_item_uid);

  if (texture_iterator == textures.end() || canvas_item_iterator == canvas_items.end())
    return;

  canvas_item_iterator->second->textures.insert({texture_uid, texture_iterator->second});
}

void RenderingServer::canvas_item_add_texture_region(const uid &texture_uid, const uid &canvas_item_uid, const Rect2i &src_region) {
  auto texture_iterator = textures.find(texture_uid);
  auto canvas_item_iterator = canvas_items.find(canvas_item_uid);

  if (texture_iterator == textures.end() || canvas_item_iterator == canvas_items.end())
    return;

  texture_iterator->second->src_region = src_region;
  canvas_item_iterator->second->textures.insert({texture_uid, texture_iterator->second});
}

void RenderingServer::canvas_item_remove_texture(const uid &texture_uid, const uid &canvas_item_uid) {
  auto texture_iterator = textures.find(texture_uid);
  auto canvas_item_iterator = canvas_items.find(canvas_item_uid);

  if (texture_iterator == textures.end() || canvas_item_iterator == canvas_items.end())
    return;

  CanvasItem *canvas_item = canvas_item_iterator->second;
  auto canvas_item_texture_iterator = canvas_item->textures.find(texture_uid);
  if (canvas_item_texture_iterator != canvas_item->textures.end())
    canvas_item_iterator->second->textures.erase(canvas_item_texture_iterator);
}
