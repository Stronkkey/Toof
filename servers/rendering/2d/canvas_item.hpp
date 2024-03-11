#pragma once

#include <core/math/transform2d.hpp>
#include <core/math/color.hpp>

#include <vector>
#include <memory>

#include <SDL_render.h>

namespace sdl {

struct DrawingItem;

struct CanvasItem {
	Transform2D transform, global_transform = Transform2D::IDENTITY;
	ColorV modulate, global_modulate = ColorV::WHITE();
	bool visible, zindex_relative, global_visible = true;
	int zindex, global_zindex = 0;

	SDL_BlendMode blend_mode = SDL_BLENDMODE_BLEND;
	SDL_ScaleMode scale_mode = SDL_ScaleModeLinear;

	std::weak_ptr<CanvasItem> parent;
	std::vector<std::unique_ptr<DrawingItem>> drawing_items;

	void set_global_transform();
	void set_global_modulate();
	void set_global_visible();
	void set_global_zindex();

	const Transform2D &get_global_transform();
	const ColorV &get_global_modulate();
	bool is_globally_visible();
	int get_global_zindex();
};

}
