#include <items/rendering_item.hpp>
#include <rendering/window.hpp>
#include <items/tree.hpp>
#include <rendering/texture.hpp>

#include <typeinfo>

using namespace sdl;

RenderingItem::RenderingItem(): transform(Transform2D::IDENTITY),
    canvas_item(0),
    modulate(Color::WHITE),
    blend_mode(SDL_BLENDMODE_BLEND),
	scale_mode(SDL_ScaleModeLinear),
    visible(true) {
}

RenderingItem::~RenderingItem() {
	RenderingServer *rendering_server = get_rendering_server();

	if (rendering_server)
		rendering_server->remove_uid(canvas_item);
}

void RenderingItem::ready() {
	transform = transform.IDENTITY;
	canvas_item = get_rendering_server()->create_canvas_item();

	update();
	redraw();
}

RenderingServer *RenderingItem::get_rendering_server() const {
	return get_tree() ? get_tree()->get_rendering_server() : nullptr;
}

void RenderingItem::update() {
	RenderingServer *rendering_server = get_rendering_server();

	if (rendering_server) {
		rendering_server->canvas_item_set_transform(canvas_item, transform);
		rendering_server->canvas_item_set_modulate(canvas_item, modulate);
		rendering_server->canvas_item_set_blend_mode(canvas_item, blend_mode);
		rendering_server->canvas_item_set_scale_mode(canvas_item, scale_mode);
		rendering_server->canvas_item_set_visible(canvas_item, visible);
	}
}

void RenderingItem::on_parent_changed(Item *new_parent) {
	RenderingServer *rendering_server = get_rendering_server();
	if (!rendering_server || !new_parent)
		return;

	RenderingItem *rendering_item = dynamic_cast<RenderingItem*>(new_parent);
	if (rendering_item)
		rendering_server->canvas_item_set_parent(canvas_item, rendering_item->get_canvas_item());
}

void RenderingItem::_notification(const int what) {
	switch (what) {
		case NOTIFICATION_READY:
			ready();
			break;
		case NOTIFICATION_DRAW:
			_draw();
			break;
		case NOTIFICATION_PARENTED:
			on_parent_changed(get_parent());
			break;
		default:
			break;
	}
}

void RenderingItem::_draw() const {
}

uid RenderingItem::get_canvas_item() const {
	return canvas_item;
}

void RenderingItem::redraw() {
	if (is_inside_tree())
		notification(NOTIFICATION_DRAW);
}


void RenderingItem::set_position(const Vector2 &new_position) {
	transform.origin = new_position;
	update();
}

Vector2 RenderingItem::get_position() const {
	return transform.origin;
}

void RenderingItem::set_scale(const Vector2 &new_scale) {
	transform.scale = new_scale;
	update();
}

Vector2 RenderingItem::get_scale() const {
	return transform.scale;
}

void RenderingItem::set_rotation(const double new_rotation) {
	transform.rotation = new_rotation;
	update();
}

double RenderingItem::get_rotation() const {
	return transform.rotation;
}

void RenderingItem::set_global_position(const Vector2 &new_global_position) {
	Vector2 global_position = get_global_position();
	transform.origin = -Vector2(global_position - new_global_position);
}

Vector2 RenderingItem::get_global_position() const {
	RenderingServer *rendering_server = get_rendering_server();

	if (rendering_server)
		return rendering_server->canvas_item_get_global_transform(canvas_item).origin;
	return transform.origin;
}

void RenderingItem::set_global_scale(const Vector2 &new_global_scale) {
	Vector2 global_scale = get_global_scale();
	transform.scale = -Vector2(global_scale - new_global_scale);
}

Vector2 RenderingItem::get_global_scale() const {
	RenderingServer *rendering_server = get_rendering_server();

	if (rendering_server)
		return rendering_server->canvas_item_get_global_transform(canvas_item).scale;
	return transform.scale;
}

void RenderingItem::set_global_rotation(const double new_global_rotation) {
	double global_rotation = get_global_rotation();
	transform.rotation = -(global_rotation - new_global_rotation);
}

double RenderingItem::get_global_rotation() const {
	RenderingServer *rendering_server = get_rendering_server();

	if (rendering_server)
		return rendering_server->canvas_item_get_global_transform(canvas_item).rotation;
	return transform.rotation;
}

void RenderingItem::set_transform(const Transform2D &new_transform) {
	transform = new_transform;
	update();
}

Transform2D RenderingItem::get_transform() const {
	return transform;
}

void RenderingItem::set_global_transform(const Transform2D &new_global_transform) {
	const Transform2D global_transform = get_global_transform();
	Transform2D new_transform = new_global_transform;

	transform.origin = -(global_transform.origin - new_global_transform.origin);
	transform.rotation = -(global_transform.rotation - new_transform.rotation);
	transform.scale = -(global_transform.scale - new_transform.scale);
	update();
}

Transform2D RenderingItem::get_global_transform() const {
	RenderingServer *rendering_server = get_rendering_server();

	if (rendering_server)
		return rendering_server->canvas_item_get_global_transform(canvas_item);
	return transform;
}

void RenderingItem::set_modulate(const Color &new_modulate) {
	modulate = new_modulate;
	update();
}

Color RenderingItem::get_modulate() const {
	return modulate;
}

Color RenderingItem::get_absolute_modulate() const {
	RenderingServer *rendering_server = get_rendering_server();
	return rendering_server ? rendering_server->canvas_item_get_global_modulate(canvas_item) : modulate;
}

void RenderingItem::set_blend_mode(const SDL_BlendMode new_blend_mode) {
	blend_mode = new_blend_mode;
	update();
}

SDL_BlendMode RenderingItem::get_blend_mode() const {
	return blend_mode;
}

void RenderingItem::set_scale_mode(const SDL_ScaleMode scaling_mode) {
	scale_mode = scaling_mode;
	update();
}

SDL_ScaleMode RenderingItem::get_scale_mode() const {
	return scale_mode;
}

void RenderingItem::hide() {
	if (!visible)
		return;

	visible = false;
	update();
}

void RenderingItem::show() {
	if (visible)
		return;

	visible = true;
	update();
}

bool RenderingItem::is_visible() const {
	return visible;
}

bool RenderingItem::is_visible_in_tree() const {
	RenderingServer *rendering_server = get_rendering_server();
	return rendering_server ? rendering_server->canvas_item_is_globally_visible(canvas_item) : true;
}

bool RenderingItem::is_visible_inside_viewport() const {
	RenderingServer *rendering_server = get_rendering_server();
	return rendering_server ? rendering_server->canvas_item_is_visible_inside_viewport(canvas_item) : true;
}

void RenderingItem::draw_texture(const std::shared_ptr<Texture2D> &texture, const Transform2D &texture_transform, const Color &modulation) const {
	RenderingServer *rendering_server = get_rendering_server();
	if (rendering_server)
		rendering_server->canvas_item_add_texture(texture->get_uid(), canvas_item, SDL_FLIP_NONE, modulation, texture_transform);
}

void RenderingItem::draw_texture_rect(const std::shared_ptr<Texture2D> &texture, const Rect2i &region, const Transform2D &texture_transform, const Color &modulation) const {
	RenderingServer *rendering_server = get_rendering_server();
	if (rendering_server)
		rendering_server->canvas_item_add_texture_region(texture->get_uid(), canvas_item, region, SDL_FLIP_NONE, modulation, texture_transform);
}

void RenderingItem::draw_line(const Vector2 &start, const Vector2 &end, const Color &modulation) const {
	RenderingServer *rendering_server = get_rendering_server();
	if (rendering_server)
		rendering_server->canvas_item_add_line(canvas_item, start, end,  modulation);
}

void RenderingItem::draw_lines(const std::vector<SDL_FPoint> &points, const Color &modulation) const {
	RenderingServer *rendering_server = get_rendering_server();
	if (rendering_server)
		rendering_server->canvas_item_add_lines(canvas_item, points, modulation);
}

void RenderingItem::draw_rect(const Rect2 &rect, const Color &modulation) const {
	RenderingServer *rendering_server = get_rendering_server();
	if (rendering_server)
		rendering_server->canvas_item_add_rect(canvas_item, rect, modulation);
}

void RenderingItem::draw_rects(const std::vector<SDL_FRect> &rects, const Color &modulation) const {
	RenderingServer *rendering_server = get_rendering_server();
	if (rendering_server)
		rendering_server->canvas_item_add_rects(canvas_item, rects, modulation);
}