#pragma once

#include <types/rect2.hpp>
#include <types/transform2d.hpp>
#include <types/color.hpp>

#include <SDL_render.h>

#include <memory>
#include <optional>
#include <unordered_map>

namespace sdl {

struct Texture;
struct CanvasItem;
struct Transform2D;
struct Rect2i;

class RenderingServer {

private:
  SDL_Renderer *renderer;
  std::unordered_map<uint_t, std::shared_ptr<Texture>> textures;
  std::unordered_map<uint_t, std::shared_ptr<CanvasItem>> canvas_items;
  Color background_color = Color(77, 77, 77, 255);

  uid create_new_uid();
  void destroy_uid(const uid target_uid);
  uint_t index = 1;

  void render_canvas_item(const std::shared_ptr<CanvasItem> &canvas_item);

  std::shared_ptr<CanvasItem> get_canvas_item_from_uid(const uid canvas_item_uid) const;
  std::shared_ptr<Texture> get_texture_from_uid(const uid texture_uid) const;

public:
  struct TextureInfo {
    Vector2i size;
    uint32_t format;
  };

public:
  RenderingServer(SDL_Renderer *new_renderer);
  ~RenderingServer();

  void render();
  void remove_uid(const uid destroying_uid);

  uint_t load_texture_from_path(const std::string &path);
  uint_t create_canvas_item();

  void set_default_background_color(const Color &new_background_color);
  Color get_default_background_color() const;
  Vector2i get_screen_size() const;

  TextureInfo get_texture_info_from_uid(const uid texture_uid) const;

  void canvas_item_add_texture(const uid texture_uid,
    const uid canvas_item_uid,
    const SDL_RendererFlip flip = SDL_FLIP_NONE,
    const Color &modulate = Color::WHITE,
    const Transform2D &transform = Transform2D::IDENTITY);

  void canvas_item_add_texture_region(const uid texture_uid,
    const uid canvas_item_uid,
    const Rect2i &src_region,
    const SDL_RendererFlip flip = SDL_FLIP_NONE,
    const Color &modulate = Color::WHITE,
    const Transform2D &transform = Transform2D::IDENTITY);

  void canvas_item_set_transform(const uid canvas_item_uid, const Transform2D &new_transform);
  void canvas_item_set_parent(const uid canvas_item_uid, const uid parent_item_uid);
  void canvas_item_set_modulate(const uid canvas_item_uid, const Color &new_modulate);
  void canvas_item_set_blend_mode(const uid canvas_item_uid, const SDL_BlendMode blend_mode);
  void canvas_item_clear(const uint_t canvas_item_uid);

  Transform2D canvas_item_get_transform(const uint_t canvas_item_uid) const;
  Transform2D canvas_item_get_global_transform(const uid canvas_item_uid) const;

  Color canvas_item_get_modulate(const uid canvas_item_uid) const;
  Color canvas_item_get_global_modulate(const uid canvas_item_uid) const;

  bool canvas_item_is_visible(const uid canvas_item_uid) const;
  void canvas_item_set_visible(const uid canvas_item_uid, const bool visible);
  bool canvas_item_is_globally_visible(const uid canvas_item_uid) const;
  bool canvas_item_is_visible_inside_viewport(const uid canvas_item_uid) const;
};

}