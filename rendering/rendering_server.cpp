#include <SDL_render.h>
#include <rendering/rendering_server.hpp>

using namespace sdl;

Transform2D CanvasItem::get_global_transform() const {
  Transform2D absolute_transform = transform;
  std::shared_ptr<CanvasItem> parent_canvas_item = parent;

  if (!parent_canvas_item)
    return absolute_transform;

  while (parent_canvas_item) {
    Vector2 new_position = absolute_transform.origin + parent_canvas_item->transform.origin;
    Vector2 new_scale = absolute_transform.scale * parent_canvas_item->transform.scale;
    double new_rotation = absolute_transform.rotation + parent_canvas_item->transform.rotation;

    absolute_transform = Transform2D(new_rotation, new_position, new_scale);
    parent_canvas_item = parent_canvas_item->parent;
  }

  return absolute_transform;
}

void LineDrawingItem::draw(SDL_Renderer *renderer) {
  SDL_RenderDrawLineF(renderer, rect.x, rect.y, rect.x, rect.y);
}

void RectDrawingItem::draw(SDL_Renderer *renderer) {
  SDL_FRect frect = rect.to_sdl_frect();
  SDL_RenderDrawRectF(renderer, &frect);
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

    Transform2D global_transform = canvas_item->get_global_transform();

    Rect2 src_region = texture.src_region.to_sdl_rect();
    Rect2 destination = Rect2(global_transform.origin, global_transform.scale * src_region.get_size());

    SDL_Rect final_src_region = src_region.to_sdl_rect();
    SDL_FRect final_destination = destination.to_sdl_frect();
    SDL_Texture *texture_reference = texture.texture_reference;
    SDL_FPoint offset = (texture.offset + (destination.get_position() / 2.0)).to_sdl_fpoint();
    double rotation = global_transform.rotation;

    SDL_RenderCopyExF(renderer, texture_reference, &final_src_region, &final_destination, rotation, &offset, texture.flip);

  }

  for (DrawingItem drawing_item: canvas_item->drawing_items)
    drawing_item.draw(renderer);
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

void RenderingServer::canvas_item_set_transform(const uid &canvas_item_uid, const Transform2D &new_transform) {
  std::shared_ptr<CanvasItem> canvas_item = get_canvas_item_from_uid(canvas_item_uid);
  if (canvas_item)
    canvas_item->transform = new_transform;
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
  canvas_item_iterator->second->drawing_items.clear();
}

Transform2D RenderingServer::canvas_item_get_transform(const uid &canvas_item_uid) const {
  std::shared_ptr<CanvasItem> canvas_item = get_canvas_item_from_uid(canvas_item_uid);
  return canvas_item ? canvas_item->transform : Transform2D::IDENTITY;
}

Transform2D RenderingServer::canvas_item_get_global_transform(const uid &canvas_item_uid) const {
  std::shared_ptr<CanvasItem> canvas_item = get_canvas_item_from_uid(canvas_item_uid);
  return canvas_item ? canvas_item->get_global_transform() : Transform2D::IDENTITY;
}
