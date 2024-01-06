#pragma once

#include <core/math/math_defs.hpp>
#include <core/math/transform2d.hpp>
#include <core/math/color.hpp>
#include <resources/resource.hpp>

#include <SDL_render.h>

namespace sdl {

struct Rect2i;
class RenderingServer;

class Texture2D : public Resource {

public:
	virtual Vector2i get_size(const RenderingServer* = nullptr) const;
	virtual int get_width(const RenderingServer* = nullptr) const;
	virtual int get_height(const RenderingServer* = nullptr) const;
	virtual uid get_uid() const;
	virtual SDL_Texture *get_texture(const RenderingServer* = nullptr) const;

	virtual void draw(RenderingServer *rendering_server,
	    const uid texture_uid,
	    const uid canvas_item_uid,
	    const SDL_RendererFlip flip = SDL_FLIP_NONE,
	    const Color &modulate = Color::WHITE,
	    const Transform2D &transform = Transform2D::IDENTITY) const;

	virtual void draw_region(RenderingServer *rendering_server,
	    const uid texture_uid,
	    const uid canvas_item_uid,
	    const Rect2i &src_region,
	    const SDL_RendererFlip flip = SDL_FLIP_NONE,
	    const Color &modulate = Color::WHITE,
	    const Transform2D &transform = Transform2D::IDENTITY) const;

};

}
