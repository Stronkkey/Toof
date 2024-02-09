#include <scene/2d/node2d.hpp>
#include <scene/2d/sprite2d.hpp>
#include <scene/resources/texture2d.hpp>

using namespace sdl;

Sprite2D::Sprite2D(): texture(nullptr),
    texture_region(),
    texture_transform(),
    flip(SDL_FLIP_NONE),
    centered(true) {
}

Transform2D Sprite2D::get_placement_texture_transform() const {
	Transform2D placement_texture_transform = texture_transform;
	if (centered) {
		const Vector2 texture_size = texture->get_size(get_rendering_server());
		placement_texture_transform.origin -= (texture_size / 2) * texture_transform.scale;
	}

	return placement_texture_transform;
}

void Sprite2D::draw_texture() const {
	texture->draw(get_rendering_server(), texture->get_uid(), get_canvas_item(), flip, Color::WHITE, get_placement_texture_transform());
}

void Sprite2D::draw_rect_texture() const {
	texture->draw_region(get_rendering_server(), texture->get_uid(), get_canvas_item(), texture_region, flip, Color::WHITE, get_placement_texture_transform());
}

void Sprite2D::draw() const {
	const std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();
	if (!rendering_server || !texture)
		return;

	rendering_server->canvas_item_clear(get_canvas_item());
	if (texture_region == Rect2i::EMPTY)
		draw_texture();
	else
		draw_rect_texture();
}

void Sprite2D::_notification(const int what) {
	Node2D::_notification(what);

	if (what == NOTIFICATION_DRAW)
		draw();
}

void Sprite2D::set_texture(const std::shared_ptr<Texture2D> &new_texture) {
	texture = new_texture;
	texture_changed();
	queue_redraw();
}

const std::shared_ptr<Texture2D> &Sprite2D::get_texture() const {
	return texture;
}

void Sprite2D::set_texture_region(const Rect2i &new_texture_region) {
	texture_region = new_texture_region;
	queue_redraw();
}

const Rect2i &Sprite2D::get_texture_region() const {
	return texture_region;
}

void Sprite2D::set_offset(const Vector2 &new_offset) {
	texture_transform.origin = new_offset;
	queue_redraw();
}

const Vector2 &Sprite2D::get_offset() const {
	return texture_transform.origin;
}

void Sprite2D::set_flip(const SDL_RendererFlip new_flip) {
	flip = new_flip;
	queue_redraw();
}

SDL_RendererFlip Sprite2D::get_flip() const {
	return flip;
}

void Sprite2D::set_texture_rotation(const double new_rotation) {
	texture_transform.rotation = new_rotation;
	queue_redraw();
}

double Sprite2D::get_texture_rotation() const {
	return texture_transform.rotation;
}

void Sprite2D::set_texture_scale(const Vector2 &new_texture_scale) {
	texture_transform.scale = new_texture_scale;
	queue_redraw();
}

const Vector2 &Sprite2D::get_texture_scale() const {
	return texture_transform.scale;
}

void Sprite2D::set_texture_transform(const Transform2D &new_texture_transform) {
	texture_transform = new_texture_transform;
	queue_redraw();
}

void Sprite2D::set_centered(const bool new_centered) {
	centered = new_centered;
	queue_redraw();
}

bool Sprite2D::is_centered() const {
	return centered;
}
