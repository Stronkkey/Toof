#include <scene/2d/node2d.hpp>
#include <scene/2d/sprite2d.hpp>
#include <scene/resources/texture2d.hpp>

using namespace sdl;

Sprite2D::Sprite2D(): texture(nullptr),
    texture_region(),
    texture_transform(Transform2D::IDENTITY),
    flip(SDL_FLIP_NONE),
    centered(true) {
}

Transform2D Sprite2D::_get_placement_texture_transform() const {
	Transform2D placement_texture_transform = texture_transform;
	if (centered) {
		const Vector2f texture_size = texture->get_size(get_rendering_server());
		placement_texture_transform.origin -= (texture_size / 2) * texture_transform.scale;
	}

	return placement_texture_transform;
}

void Sprite2D::_draw_full_texture() const {
	texture->draw(get_rendering_server(), texture->get_uid(), get_canvas_item(), flip, Color::WHITE, _get_placement_texture_transform());
}

void Sprite2D::_draw_rect_texture() const {
	texture->draw_region(get_rendering_server(), texture->get_uid(), get_canvas_item(), texture_region, flip, Color::WHITE, _get_placement_texture_transform());
}

void Sprite2D::_draw_texture() const {
	const std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();
	if (!rendering_server || !texture)
		return;

	rendering_server->canvas_item_clear(get_canvas_item());
	if (texture_region == Rect2i::EMPTY)
		_draw_full_texture();
	else
		_draw_rect_texture();
}

void Sprite2D::_notification(const int what) {
	Node2D::_notification(what);

	if (what == NOTIFICATION_DRAW)
		_draw_texture();
}

void Sprite2D::set_texture(const std::shared_ptr<Texture2D> &new_texture) {
	texture = new_texture;
	texture_changed();
	queue_redraw();
}

void Sprite2D::set_texture_region(const Rect2i &new_texture_region) {
	texture_region = new_texture_region;
	queue_redraw();
}

void Sprite2D::set_offset(const Vector2f &new_offset) {
	texture_transform.origin = new_offset;
	queue_redraw();
}

void Sprite2D::set_flip(const SDL_RendererFlip new_flip) {
	flip = new_flip;
	queue_redraw();
}

void Sprite2D::set_texture_rotation(const Angle new_rotation) {
	texture_transform.rotation = new_rotation;
	queue_redraw();
}

void Sprite2D::set_texture_scale(const Vector2f &new_texture_scale) {
	texture_transform.scale = new_texture_scale;
	queue_redraw();
}

void Sprite2D::set_texture_transform(const Transform2D &new_texture_transform) {
	texture_transform = new_texture_transform;
	queue_redraw();
}

void Sprite2D::set_centered(const bool new_centered) {
	centered = new_centered;
	queue_redraw();
}
