#pragma once

#include <core/math/math_defs.hpp>
#include <core/math/transform2d.hpp>
#include <core/math/color.hpp>

#include <SDL_render.h>

namespace sdl {

struct Rect2i;
class RenderingServer;

class Texture2D {

public:
	virtual Vector2i get_size(const RenderingServer* = nullptr) const;
	virtual int get_width(const RenderingServer* = nullptr) const;
	virtual int get_height(const RenderingServer* = nullptr) const;
	virtual uid get_uid() const;

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

class UidTexture : public Texture2D {

private:
	uid texture_uid;

public:
	UidTexture();
	UidTexture(const uid from_uid);

	Vector2i get_size(const RenderingServer* = nullptr) const override;
	uid get_uid() const override { return texture_uid; }

	void draw(RenderingServer *rendering_server,
	    const uid texture_uid,
	    const uid canvas_item_uid,
	    const SDL_RendererFlip flip = SDL_FLIP_NONE,
	    const Color &modulate = Color::WHITE,
	    const Transform2D &transform = Transform2D::IDENTITY) const override;

	void draw_region(RenderingServer *rendering_server,
	    const uid texture_uid,
	    const uid canvas_item_uid,
	    const Rect2i &src_region,
	    const SDL_RendererFlip flip = SDL_FLIP_NONE,
	    const Color &modulate = Color::WHITE,
	    const Transform2D &transform = Transform2D::IDENTITY) const override;

	void load_from_path(RenderingServer *rendering_server, const std::string &file_path);
};

}
