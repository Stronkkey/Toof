#include <rendering/rendering_server.hpp>

using namespace sdl;

Rect2 CanvasItem::get_global_destination() const {
  Rect2 absolute_destination = destination;
  std::shared_ptr<CanvasItem> parent_canvas_item = parent;

  if (parent_canvas_item)
    return destination;

  while (parent_canvas_item) {
    Vector2 new_position = absolute_destination.get_position() + parent_canvas_item->destination.get_position();
    Vector2 new_scale = absolute_destination.get_size() * parent_canvas_item->destination.get_size();

    absolute_destination = Rect2(new_position, new_scale);
    parent_canvas_item = parent_canvas_item->parent;
  }

  return absolute_destination;
}

RenderingServer::RenderingServer(): renderer(nullptr) {
}

RenderingServer::RenderingServer(SDL_Renderer *new_renderer): renderer(new_renderer) {
}

RenderingServer::~RenderingServer() {
  for (std::pair<uid, std::shared_ptr<CanvasItem>> iterator: canvas_items)
    destroy_uid(iterator.first);
}

void RenderingServer::render() {
  if (!renderer)
    return;

  SDL_RenderClear(renderer);
  for (auto iterator: canvas_items) {
    render_canvas_item(iterator.second);
  }
  SDL_RenderPresent(renderer);
}

Texture RenderingServer::get_texture_from_uid(const uid &grab_uid) const {
  auto iterator = textures.find(grab_uid);
  return iterator != textures.end() ? iterator->second : Texture();
}

std::shared_ptr<CanvasItem> RenderingServer::get_canvas_item_from_uid(const uid &grab_uid) const {
  auto iterator = canvas_items.find(grab_uid);
  return iterator != canvas_items.end() ? iterator->second : std::shared_ptr<CanvasItem>(nullptr);
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
    canvas_item_iterator->second.reset();
  }

  if (texture_iterator != textures.end()) {
    textures.erase(texture_iterator);
    SDL_DestroyTexture(texture_iterator->second.texture_reference);
    texture_iterator->second.texture_reference = nullptr;
  }

}

void RenderingServer::render_canvas_item(const std::shared_ptr<CanvasItem> canvas_item) {
  for (Texture texture: canvas_item->textures) {
    if (!texture.texture_reference)
      continue;

    Rect2 src_region = texture.src_region.to_sdl_rect();
    Rect2 global_destination = canvas_item->get_global_destination();
    Rect2 destination = Rect2(global_destination.get_position(), global_destination.get_size() * src_region.get_size());

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
  std::shared_ptr<CanvasItem> canvas_item = std::shared_ptr<CanvasItem>(new CanvasItem);
  new_uid.type = UID_RENDERING;
  canvas_items.insert({new_uid, canvas_item});
  return new_uid;
}

void RenderingServer::texture_set_source_region(const uid &texture_uid, const Rect2i &src_region) {
  Texture texture = get_texture_from_uid(texture_uid);
  texture.src_region = src_region;
}

Rect2i RenderingServer::texture_get_source_region(const uid &texture_uid) const {
  Texture texture = get_texture_from_uid(texture_uid);
  return texture.src_region;
}

void RenderingServer::canvas_item_add_texture(const uid &texture_uid, const uid &canvas_item_uid) {
  std::shared_ptr<CanvasItem> canvas_item = get_canvas_item_from_uid(canvas_item_uid);
  Texture texture = get_texture_from_uid(texture_uid);

  if (canvas_item && texture.texture_reference)
    canvas_item->textures.push_back(texture);
}

void RenderingServer::canvas_item_add_texture_region(const uid &texture_uid, const uid &canvas_item_uid, const Rect2i &src_region) {
  Texture texture = get_texture_from_uid(texture_uid);
  std::shared_ptr<CanvasItem> canvas_item = get_canvas_item_from_uid(canvas_item_uid);

  if (canvas_item && texture.texture_reference) {
    texture.src_region = src_region;
    canvas_item->textures.push_back(texture);
  }
}

void RenderingServer::canvas_item_set_destination(const uid &canvas_item_uid, const Rect2 &new_destination) {
  std::shared_ptr<CanvasItem> canvas_item = get_canvas_item_from_uid(canvas_item_uid);
  if (canvas_item)
    canvas_item->destination = new_destination;
}

void RenderingServer::canvas_item_set_parent(const uid &canvas_item_uid, const uid &parent_item_uid) {
  std::shared_ptr<CanvasItem> canvas_item = get_canvas_item_from_uid(canvas_item_uid);
  std::shared_ptr<CanvasItem> parent_canvas_item = get_canvas_item_from_uid(parent_item_uid);

  if (canvas_item)
    canvas_item->parent = parent_canvas_item;
  else
    canvas_item->parent = std::shared_ptr<CanvasItem>(nullptr);
}

void RenderingServer::canvas_item_clear(const uid &canvas_item_uid) {
  auto canvas_item_iterator = canvas_items.find(canvas_item_uid);

  if (canvas_item_iterator == canvas_items.end())
    return;

  canvas_item_iterator->second->textures.clear();
}

Rect2 RenderingServer::canvas_item_get_destination(const uid &canvas_item_uid) const {
  std::shared_ptr<CanvasItem> canvas_item = get_canvas_item_from_uid(canvas_item_uid);
  return canvas_item ? canvas_item->destination : Rect2::EMPTY;
}

Rect2 RenderingServer::canvas_item_get_global_destination(const uid &canvas_item_uid) const {
  std::shared_ptr<CanvasItem> canvas_item = get_canvas_item_from_uid(canvas_item_uid);
  return canvas_item ? canvas_item->get_global_destination() : Rect2::EMPTY;
}
