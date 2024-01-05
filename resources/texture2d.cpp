#include <resources/texture2d.hpp>
#include <servers/rendering_server.hpp>

using namespace sdl;

Vector2i Texture2D::get_size(const RenderingServer*) const {
    return Vector2i::ZERO;
}

int Texture2D::get_width(const RenderingServer *rendering_server) const {
	return get_size(rendering_server).x;
}

int Texture2D::get_height(const RenderingServer *rendering_server) const {
	return get_size(rendering_server).y;
}

uid Texture2D::get_uid() const {
	return 0;
}

void Texture2D::draw(RenderingServer*, const uid, const uid, const SDL_RendererFlip, const Color&, const Transform2D&) const {
}

void Texture2D::draw_region(RenderingServer*, const uid, const uid, const Rect2i&, const SDL_RendererFlip, const Color&, const Transform2D&) const {
}
