#include <scene/resources/texture2d.hpp>
#include <servers/rendering_server.hpp>

sdl::Vector2i sdl::Texture2D::get_size(const std::unique_ptr<RenderingServer>&) const {
    return Vector2i::ZERO;
}

int sdl::Texture2D::get_width(const std::unique_ptr<RenderingServer> &rendering_server) const {
	return get_size(rendering_server).x;
}

int sdl::Texture2D::get_height(const std::unique_ptr<RenderingServer> &rendering_server) const {
	return get_size(rendering_server).y;
}

sdl::uid sdl::Texture2D::get_uid() const {
	return 0;
}

SDL_Texture *sdl::Texture2D::get_texture(const std::unique_ptr<RenderingServer>&) const {
	return nullptr;
}

void sdl::Texture2D::draw(const std::unique_ptr<RenderingServer>&, const uid, const uid, const SDL_RendererFlip, const Color&, const Transform2D&) const {
}

void sdl::Texture2D::draw_region(const std::unique_ptr<RenderingServer>&, const uid, const uid, const Rect2i&, const SDL_RendererFlip, const Color&, const Transform2D&) const {
}
