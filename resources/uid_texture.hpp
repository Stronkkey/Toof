#pragma once

#include <resources/texture2d.hpp>

namespace sdl {

class UidTexture : public Texture2D {

private:
	uid texture_uid;

public:
	UidTexture();
	UidTexture(const uid from_uid);

	Vector2i get_size(const RenderingServer* = nullptr) const override;
	uid get_uid() const override { return texture_uid; }
	SDL_Texture *get_texture(const RenderingServer *rendering_server = nullptr) const override;

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
