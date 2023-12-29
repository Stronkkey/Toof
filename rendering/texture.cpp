#include <rendering/texture.hpp>
#include <rendering/rendering_server.hpp>

using namespace sdl;

void Texture2D::draw(RenderingServer*, const uid, const uid, const SDL_RendererFlip, const Color&, const Transform2D&) const {
}

void Texture2D::draw_region(RenderingServer*, const uid, const uid, const Rect2i&, const SDL_RendererFlip, const Color&, const Transform2D&) const {
}


UidTexture::UidTexture() {
}

UidTexture::UidTexture(const uid from_uid) {
	texture_uid = from_uid;
}

Vector2i UidTexture::get_size() const {
	return Vector2i::ZERO;
}

Vector2i UidTexture::get_size(RenderingServer *rendering_server) const {
	return rendering_server->get_texture_info_from_uid(texture_uid).size;
}

void UidTexture::draw(RenderingServer *rendering_server,
        const uid texture_uid,
        const uid canvas_item_uid,
        const SDL_RendererFlip flip,
        const Color &modulate,
        const Transform2D &transform) const {
	rendering_server->canvas_item_add_texture(texture_uid, canvas_item_uid, flip, modulate, transform);
}

void UidTexture::draw_region(RenderingServer *rendering_server,
        const uid texture_uid,
        const uid canvas_item_uid,
        const Rect2i &src_region,
        const SDL_RendererFlip flip,
        const Color &modulate,
        const Transform2D &transform ) const {
	rendering_server->canvas_item_add_texture_region(texture_uid, canvas_item_uid, src_region, flip, modulate, transform);
}

void UidTexture::load_from_path(RenderingServer *rendering_server, const std::string &file_path) {
	texture_uid = rendering_server->load_texture_from_path(file_path);
}
