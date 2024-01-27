#pragma once

#include <core/math/transform2d.hpp>
#include <core/math/color.hpp>

#include <vector>
#include <memory>

#include <SDL_render.h>

namespace sdl {

struct DrawingItem;

struct CanvasItem {
	Transform2D transform = Transform2D::IDENTITY;
	Color modulate = Color::WHITE;
	bool visible = true;
	bool zindex_relative = true;
	int zindex = 0;

	SDL_BlendMode blend_mode = SDL_BLENDMODE_BLEND;
	SDL_ScaleMode scale_mode = SDL_ScaleModeLinear;

	std::weak_ptr<CanvasItem> parent;
	std::vector<std::shared_ptr<DrawingItem>> drawing_items;

	Transform2D get_global_transform() const;
	Color get_absolute_modulate() const;
	bool is_visible() const;
	int get_zindex() const;
};

}
