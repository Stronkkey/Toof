#include <iostream>
#include <rendering_server.hpp>

using namespace sdl;

Rect2 CanvasItem::get_global_destination() const {
  Rect2 absolute_destination = destination;
  Ref<CanvasItem> parent_canvas_item = parent;

  if (parent_canvas_item.is_null())
    return destination;

  while (parent_canvas_item.is_valid()) {
    absolute_destination += parent_canvas_item->destination;
    parent_canvas_item = parent_canvas_item->parent;
  }

  return absolute_destination;
}

RenderingServer::RenderingServer(SDL_Renderer *new_renderer) {
  renderer = new_renderer;
}

RenderingServer::~RenderingServer() {
  for (std::pair<uid, Ref<CanvasItem>> iterator: canvas_items)
    destroy_uid(iterator.first);
}

void RenderingServer::render() {
  if (!renderer)
    return;

  SDL_RenderClear(renderer);
  for (auto iterator: canvas_items) {
    render_canvas_item(iterator.second.get_reference());
  }
  SDL_RenderPresent(renderer);
}

Texture RenderingServer::get_texture_from_uid(const uid &grab_uid) const {
  auto iterator = textures.find(grab_uid);
  return iterator != textures.end() ? iterator->second : Texture();
}

Ref<CanvasItem> RenderingServer::get_canvas_item_from_uid(const uid &grab_uid) const {
  auto iterator = canvas_items.find(grab_uid);
  return iterator != canvas_items.end() ? iterator->second : Ref<CanvasItem>();
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
    delete canvas_item_iterator->second.get_reference();
    canvas_item_iterator->second.remove_reference();
    canvas_items.erase(canvas_item_iterator);
  }

  if (texture_iterator != textures.end()) {
    SDL_DestroyTexture(texture_iterator->second.texture_reference);
    texture_iterator->second.texture_reference = nullptr;
    textures.erase(texture_iterator);
  }

}

void RenderingServer::render_canvas_item(const CanvasItem *canvas_item) {
  for (Texture texture: canvas_item->textures) {
    if (texture.texture_reference == nullptr)
      continue;

    Rect2 src_region = texture.src_region.to_sdl_rect();
    Rect2 global_destination = canvas_item->get_global_destination().to_sdl_rect();
    Rect2 destination = Rect2(global_destination.get_position() + src_region.get_position(), global_destination.get_size() * src_region.get_size());

    SDL_Rect final_src_region = src_region.to_sdl_rect();
    SDL_Rect final_destination = destination.to_sdl_rect();
    SDL_RenderCopy(renderer, texture.texture_reference, &final_src_region, &final_destination);
  }
}

uid RenderingServer::load_texture_from_path(const std::string &path) {
  SDL_Texture *texture = IMG_LoadTexture(renderer, path.c_str());

  if (texture == NULL)
    return uid();
  
  uid new_uid = create_new_uid();
  Texture new_texture;

  new_texture.texture_reference = texture;
  new_texture.src_region = Rect2i::EMPTY;
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

void RenderingServer::texture_set_source_region(const uid &texture_uid, const Rect2i &src_region) {
  Texture texture = get_texture_from_uid(texture_uid);
  texture.src_region = src_region;
}

void RenderingServer::canvas_item_add_texture(const uid &texture_uid, const uid &canvas_item_uid) {
  Ref<CanvasItem> canvas_item = get_canvas_item_from_uid(canvas_item_uid);
  Texture texture = get_texture_from_uid(texture_uid);

  if (canvas_item.is_valid() && texture.texture_reference)
    canvas_item->textures.push_back(texture);
}

void RenderingServer::canvas_item_add_texture_region(const uid &texture_uid, const uid &canvas_item_uid, const Rect2i &src_region) {
  Texture texture = get_texture_from_uid(texture_uid);
  Ref<CanvasItem> canvas_item = get_canvas_item_from_uid(canvas_item_uid);

  if (canvas_item.is_valid() && texture.texture_reference) {
    texture.src_region = src_region;
    canvas_item->textures.push_back(texture);
  }
}

void RenderingServer::canvas_item_set_destination(const uid &canvas_item_uid, const Rect2 &new_destination) {
  Ref<CanvasItem> canvas_item = get_canvas_item_from_uid(canvas_item_uid);
  if (canvas_item.is_valid())
    canvas_item->destination = new_destination;
}

void RenderingServer::canvas_item_set_parent(const uid &canvas_item_uid, const uid &parent_item_uid) {
  Ref<CanvasItem> canvas_item = get_canvas_item_from_uid(canvas_item_uid);
  Ref<CanvasItem> parent_canvas_item = get_canvas_item_from_uid(parent_item_uid);

  if (canvas_item.is_valid())
    canvas_item->parent = parent_canvas_item;
  else
    canvas_item->parent = Ref<CanvasItem>();
}

void RenderingServer::canvas_item_clear(const uid &canvas_item_uid) {
  auto canvas_item_iterator = canvas_items.find(canvas_item_uid);

  if (canvas_item_iterator == canvas_items.end())
    return;

  canvas_item_iterator->second->textures.clear();
}
