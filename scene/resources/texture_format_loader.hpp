#pragma once

#include <scene/resources/resource_format_loader.hpp>

#include <scene/resources/file_texture.hpp>

namespace sdl {

SDL_LIBS_RESOURCE_ID(Texture2D, 1000)
SDL_LIBS_RESOURCE_ID(FileTexture, 1001)

template<class ArchiveType>
struct TextureFormatLoader : public ResourceFormatLoader<ArchiveType> {
	std::unique_ptr<Texture2D> load_texture(int32_t id, ArchiveType &archive) const;
	std::unique_ptr<Resource> load(int32_t id, ArchiveType &archive) const override {
		return load_texture(id, archive);
	}
};

template<class ArchiveType>
std::unique_ptr<Texture2D> TextureFormatLoader<ArchiveType>::load_texture(int32_t id, ArchiveType &archive) const {
	SDL_LIBS_LOAD_TYPE_DEFAULT_ARGS(FileTexture)

	return {};
}

}
