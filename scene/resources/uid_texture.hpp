#pragma once

#include <scene/resources/texture2d.hpp>

#include <memory>

namespace sdl {

class UidTexture : public Texture2D {

private:
	uid texture_uid;

public:
	UidTexture();
	UidTexture(const uid from_uid);

	Vector2i get_size(const std::unique_ptr<RenderingServer>& = nullptr) const override;
	inline uid get_uid() const override;
	SDL_Texture *get_texture(const std::unique_ptr<RenderingServer> &rendering_server = nullptr) const override;

	void draw(const std::unique_ptr<RenderingServer> &rendering_server,
	    const uid texture_uid,
	    const uid canvas_item_uid,
	    const SDL_RendererFlip flip = SDL_FLIP_NONE,
	    const Color &modulate = Color::WHITE,
	    const Transform2D &transform = Transform2D::IDENTITY) const override;

	void draw_region(const std::unique_ptr<RenderingServer> &rendering_server,
	    const uid texture_uid,
	    const uid canvas_item_uid,
	    const Rect2i &src_region,
	    const SDL_RendererFlip flip = SDL_FLIP_NONE,
	    const Color &modulate = Color::WHITE,
	    const Transform2D &transform = Transform2D::IDENTITY) const override;

	void load_from_path(const std::unique_ptr<RenderingServer> &rendering_server, const std::string &file_path);
};

uid UidTexture::get_uid() const {
	return texture_uid;
}

}
