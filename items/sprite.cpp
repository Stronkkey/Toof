#include <items/rendering_item.hpp>
#include <items/sprite.hpp>
#include <resources/texture2d.hpp>

using namespace sdl;

SpriteItem::SpriteItem(): texture(nullptr),
    texture_region(),
    texture_transform(),
    flip(SDL_FLIP_NONE),
    centered(true) {
}

Transform2D SpriteItem::get_placement_texture_transform() const {
	Transform2D placement_texture_transform = texture_transform;
	if (centered) {
		const Vector2 texture_size = texture->get_size(get_rendering_server());
		placement_texture_transform.origin -= (texture_size / 2) * texture_transform.scale;
	}

	return placement_texture_transform;
}

void SpriteItem::draw_texture() const {
	texture->draw(get_rendering_server(), texture->get_uid(), get_canvas_item(), flip, Color::WHITE, get_placement_texture_transform());
}

void SpriteItem::draw_rect_texture() const {
	texture->draw_region(get_rendering_server(), texture->get_uid(), get_canvas_item(), texture_region, flip, Color::WHITE, get_placement_texture_transform());
}

void SpriteItem::draw() const {
	RenderingServer *rendering_server = get_rendering_server();
	if (!rendering_server || !texture)
		return;

	rendering_server->canvas_item_clear(get_canvas_item());
	if (texture_region == Rect2i::EMPTY)
		draw_texture();
	else
		draw_rect_texture();
}

void SpriteItem::_notification(const int what) {
	RenderingItem::_notification(what);

	if (what == NOTIFICATION_DRAW)
		draw();
}

void SpriteItem::set_texture(const std::shared_ptr<Texture2D> &new_texture) {
	texture = new_texture;
	texture_changed();
	redraw();
}

std::shared_ptr<Texture2D> SpriteItem::get_texture() const {
	return texture;
}

void SpriteItem::set_texture_region(const Rect2i &new_texture_region) {
	texture_region = new_texture_region;
	redraw();
}

Rect2i SpriteItem::get_texture_region() const {
	return texture_region;
}

void SpriteItem::set_offset(const Vector2 &new_offset) {
	texture_transform.origin = new_offset;
	redraw();
}

Vector2 SpriteItem::get_offset() const {
	return texture_transform.origin;
}

void SpriteItem::set_flip(const SDL_RendererFlip new_flip) {
	flip = new_flip;
	redraw();
}

SDL_RendererFlip SpriteItem::get_flip() const {
	return flip;
}

void SpriteItem::set_texture_rotation(const double new_rotation) {
	texture_transform.rotation = new_rotation;
	redraw();
}

double SpriteItem::get_texture_rotation() const {
	return texture_transform.rotation;
}

void SpriteItem::set_texture_scale(const Vector2 &new_texture_scale) {
	texture_transform.scale = new_texture_scale;
	redraw();
}

Vector2 SpriteItem::get_texture_scale() const {
	return texture_transform.scale;
}

void SpriteItem::set_texture_transform(const Transform2D &new_texture_transform) {
	texture_transform = new_texture_transform;
	redraw();
}

void SpriteItem::set_centered(const bool new_centered) {
	centered = new_centered;
	redraw();
}

bool SpriteItem::is_centered() const {
	return centered;
}
