#pragma once

#include <core/math/rect2.hpp>
#include <core/math/transform2d.hpp>
#include <core/math/color.hpp>
#include <core/memory/optional.hpp>

#include <SDL_render.h>

#include <memory>
#include <unordered_map>
#include <vector>

namespace Toof {

struct __Texture_Ref__;
struct __CanvasItem__;
template<class>
struct Rect2;
typedef Rect2<real> Rect2f;
class Viewport;

class RenderingServer {
private:
	Viewport *viewport;
	std::unordered_map<uid, std::shared_ptr<__Texture_Ref__>> textures;
	std::unordered_map<uid, std::shared_ptr<__CanvasItem__>> canvas_items;
	ColorV background_color;
	uid uid_index;

	constexpr uid assign_uid() {
		if (++uid_index == 0)
			return ++uid_index;
		return uid_index++;
	}

	void render_canvas_item(const std::shared_ptr<__CanvasItem__> &canvas_item);
	void render_canvas_items();
	void destroy_texture(std::shared_ptr<__Texture_Ref__> &texture);
	void destroy_texture_uid(const uid texture_uid);
	void destroy_canvas_item_uid(const uid canvas_item_uid);
	void destroy_uid(const uid target_uid);

	const std::shared_ptr<__CanvasItem__> &get_canvas_item_from_uid(const uid canvas_item_uid) const;
	const std::shared_ptr<__Texture_Ref__> &get_texture_from_uid(const uid texture_uid) const;

public:
	struct TextureInfo {
		Vector2i size;
		uint32_t format;
		SDL_Texture *texture;
	};

public:
	RenderingServer(Viewport *viewport);
	~RenderingServer();

	void render();
	void remove_uid(const uid destroying_uid);

	constexpr Viewport *get_viewport() const {
		return viewport;
	}

	Optional<uid> load_texture_from_path(const String &path);
	uid create_canvas_item();

	constexpr void set_default_background_color(const ColorV &new_background_color) {
		background_color = new_background_color;
	}

	constexpr const ColorV &get_default_background_color() const {
		return background_color;
	}

	Vector2i get_screen_size() const;

	Optional<TextureInfo> get_texture_info_from_uid(const uid texture_uid) const;

	void canvas_item_add_texture(const uid texture_uid, const uid canvas_item_uid, const SDL_RendererFlip flip = SDL_FLIP_NONE, const ColorV &modulate = ColorV::WHITE(), const Transform2D &transform = Transform2D::IDENTITY);
	void canvas_item_add_texture_region(const uid texture_uid, const uid canvas_item_uid, const Rect2i &src_region, const SDL_RendererFlip flip = SDL_FLIP_NONE, const ColorV &modulate = ColorV::WHITE(), const Transform2D &transform = Transform2D::IDENTITY);

	void canvas_item_add_line(const uid canvas_item_uid, const Vector2f &start, const Vector2f &end, const ColorV &modulate = ColorV::WHITE());
	void canvas_item_add_lines(const uid canvas_item_uid, const std::vector<SDL_FPoint> &points, const ColorV &modulate = ColorV::WHITE());
	void canvas_item_add_rect(const uid canvas_item_uid, const Rect2f &rect, const ColorV &modulate = ColorV::WHITE());
	void canvas_item_add_rects(const uid canvas_item_uid, const std::vector<SDL_FRect> &rectangles, const ColorV &modulate = ColorV::WHITE());

	void canvas_item_set_transform(const uid canvas_item_uid, const Transform2D &new_transform);
	void canvas_item_set_parent(const uid canvas_item_uid, const uid parent_item_uid);
	void canvas_item_set_modulate(const uid canvas_item_uid, const ColorV &new_modulate);
	void canvas_item_set_blend_mode(const uid canvas_item_uid, const SDL_BlendMode blend_mode);
	void canvas_item_set_scale_mode(const uid canvas_item_uid, const SDL_ScaleMode scale_mode);
	void canvas_item_clear(const uid canvas_item_uid);
	void canvas_item_set_visible(const uid canvas_item_uid, const bool visible);
	void canvas_item_set_zindex(const uid canvas_item_uid, const int zindex);
	void canvas_item_set_zindex_relative(const uid canvas_item_uid, const bool zindex_relative);

	bool canvas_item_uid_exists(const uid canvas_item_uid) const;
	bool texture_uid_exists(const uid canvas_item_uid) const;

	Optional<const Transform2D> canvas_item_get_transform(const uid canvas_item_uid) const;
	Optional<const Transform2D> canvas_item_get_global_transform(const uid canvas_item_uid) const;

	Optional<const ColorV> canvas_item_get_modulate(const uid canvas_item_uid) const;
	Optional<const ColorV> canvas_item_get_global_modulate(const uid canvas_item_uid) const;

	Optional<bool> canvas_item_is_visible(const uid canvas_item_uid) const;
	Optional<bool> canvas_item_is_globally_visible(const uid canvas_item_uid) const;
	Optional<bool> canvas_item_is_visible_inside_viewport(const uid canvas_item_uid) const;

	Optional<SDL_BlendMode> canvas_item_get_blend_mode(const uid canvas_item_uid) const;
	Optional<SDL_ScaleMode> canvas_item_get_scale_mode(const uid canvas_item_uid) const;

	Optional<int> canvas_item_get_zindex(const uid canvas_item_uid) const;
	Optional<int> canvas_item_get_absolute_zindex(const uid canvas_item_uid) const;
	Optional<bool> canvas_item_is_zindex_relative(const uid canvas_item_uid) const;
};

}
