#pragma once

#include <core/math/transform2d.hpp>
#include <core/math/color.hpp>

#include <vector>
#include <memory>

#include <SDL_render.h>

namespace Toof {

struct __DrawingItem__;

struct __CanvasItem__ {
	Transform2D transform = Transform2D::IDENTITY;
	Transform2D global_transform = Transform2D::IDENTITY;
	ColorV modulate = ColorV::WHITE();
	ColorV global_modulate = ColorV::WHITE();
	bool visible = true;
	bool zindex_relative = true;
	bool global_visible = true;
	int zindex = true;
	int global_zindex = 0;

	SDL_BlendMode blend_mode = SDL_BLENDMODE_BLEND;
	SDL_ScaleMode scale_mode = SDL_ScaleModeLinear;

	std::weak_ptr<__CanvasItem__> parent;
	std::vector<std::unique_ptr<__DrawingItem__>> drawing_items;

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
