#pragma once

#include <scene/resources/texture2d.hpp>

#include <cereal/cereal.hpp>

namespace sdl {

class FileTexture : public Texture2D {
private:
	uid texture_uid;
	String texture_path;

	Vector2i _get_size() const override;

	inline uid _get_uid() const override {
		return texture_uid;
	}

	SDL_Texture *_get_texture() const override;
	void _draw(const uid, const uid, const SDL_RendererFlip, const ColorV&, const Transform2D&) override;
	void _draw_region(const uid, const uid, const Rect2i&, const SDL_RendererFlip, const ColorV&, const Transform2D&) override;
public:
	FileTexture();
	FileTexture(RenderingServer *rendering_server);
	FileTexture(RenderingServer *rendering_server, const String &texture_path);
	FileTexture(RenderingServer *rendering_server, String &&texture_path);

	constexpr const String &get_texture_path() const & {
		return texture_path;
	}

	inline String get_texture_path() const && {
		return std::move(texture_path);
	}

	void load_from_path(const String &file_path);

	template<class Archive>
	void serialize(Archive &archive) {
		archive(cereal::make_nvp("FilePath", texture_path));
	}
};

}
