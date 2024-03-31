#include <scene/resources/file_texture.hpp>
#include <servers/rendering_server.hpp>

using namespace sdl;

FileTexture::FileTexture() {
}

FileTexture::FileTexture(RenderingServer *rendering_server) {
	set_rendering_server(rendering_server);
}

FileTexture::FileTexture(RenderingServer *rendering_server, const String &texture_path): texture_uid(0), texture_path(texture_path) {
	set_rendering_server(rendering_server);
	load_from_path(texture_path);
}

FileTexture::FileTexture(RenderingServer *rendering_server, String &&texture_path): texture_uid(), texture_path(std::move(texture_path)) {
	set_rendering_server(rendering_server);
	load_from_path(texture_path);
}

Vector2i FileTexture::_get_size() const {
	Optional<RenderingServer::TextureInfo> texture_info;

	if (get_rendering_server())
		texture_info = get_rendering_server()->get_texture_info_from_uid(texture_uid);
	
	return texture_info ? texture_info->size : Vector2i();
}

SDL_Texture *FileTexture::_get_texture() const {
	if (get_rendering_server()) {
		Optional<RenderingServer::TextureInfo> texture_info = get_rendering_server()->get_texture_info_from_uid(texture_uid);
		return texture_info ? texture_info->texture : nullptr;
	}

	return nullptr;
}

void FileTexture::_draw(const uid texture_uid,
	const uid canvas_item_uid,
	const SDL_RendererFlip flip,
	const ColorV &modulate,
	const Transform2D &transform)
{
	if (get_rendering_server())
		get_rendering_server()->canvas_item_add_texture(texture_uid, canvas_item_uid, flip, modulate, transform);
}

void FileTexture::_draw_region(const uid texture_uid,
	const uid canvas_item_uid,
	const Rect2i &src_region,
	const SDL_RendererFlip flip,
	const ColorV &modulate,
	const Transform2D &transform )
{
	if (get_rendering_server())
		get_rendering_server()->canvas_item_add_texture_region(texture_uid, canvas_item_uid, src_region, flip, modulate, transform);
}

void FileTexture::load_from_path(const String &file_path) {
	texture_path = file_path;
	if (!get_rendering_server())
		return;

	Optional<uid> text_uid = get_rendering_server()->load_texture_from_path(file_path);
	texture_uid = text_uid.value_or(0);
}
