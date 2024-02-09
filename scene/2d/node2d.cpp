#include <scene/2d/node2d.hpp>
#include <servers/rendering/window.hpp>
#include <scene/main/scene_tree.hpp>
#include <scene/resources/texture2d.hpp>

#include <typeinfo>

using namespace sdl;

Node2D::Node2D(): transform(Transform2D::IDENTITY),
    canvas_item(0),
    modulate(Color::WHITE),
    blend_mode(SDL_BLENDMODE_BLEND),
	scale_mode(SDL_ScaleModeLinear),
    visible(true),
	zindex_relative(true),
	update_queued(false),
	zindex(0) {
}

Node2D::~Node2D() {
	std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();

	if (rendering_server)
		rendering_server->remove_uid(canvas_item);
}

void Node2D::ready() {
	transform = transform.IDENTITY;
	canvas_item = get_rendering_server()->create_canvas_item();

	queue_redraw();
}

std::unique_ptr<RenderingServer> &Node2D::get_rendering_server() const {
	if (is_inside_tree())
		return get_tree()->get_rendering_server();
	
	std::unique_ptr<RenderingServer> _r;
	std::unique_ptr<RenderingServer> *r = &_r;
	return *r;
}

void Node2D::update() {
	std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();
	update_queued = false;

	if (rendering_server) {
		rendering_server->canvas_item_set_transform(canvas_item, transform);
		rendering_server->canvas_item_set_modulate(canvas_item, modulate);
		rendering_server->canvas_item_set_blend_mode(canvas_item, blend_mode);
		rendering_server->canvas_item_set_scale_mode(canvas_item, scale_mode);
		rendering_server->canvas_item_set_visible(canvas_item, visible);
		rendering_server->canvas_item_set_zindex(canvas_item, zindex);
		rendering_server->canvas_item_set_zindex_relative(canvas_item, zindex_relative);
	}
}

void Node2D::on_parent_changed(Node *new_parent) {
	std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();
	if (!rendering_server || !new_parent)
		return;

	Node2D *rendering_item = dynamic_cast<Node2D*>(new_parent);
	if (rendering_item)
		rendering_server->canvas_item_set_parent(canvas_item, rendering_item->get_canvas_item());
}

void Node2D::_notification(const int what) {
	switch (what) {
		case NOTIFICATION_READY:
			ready();
			break;
		case NOTIFICATION_DRAW:
			draw();
			_draw();
			break;
		case NOTIFICATION_PARENTED:
			on_parent_changed(get_parent());
			break;
		default:
			break;
	}
}

void Node2D::_draw() const {
}

void Node2D::queue_redraw() {
	if (!is_inside_tree() || update_queued)
		return;

	get_tree()->deferred_signals.connect(std::bind(&Node2D::update, this));
	notification(NOTIFICATION_DRAW);
}

uid Node2D::get_canvas_item() const {
	return canvas_item;
}

void Node2D::set_position(const Vector2 &new_position) {
	transform.origin = new_position;
	queue_redraw();
}

const Vector2 &Node2D::get_position() const {
	return transform.origin;
}

void Node2D::set_scale(const Vector2 &new_scale) {
	transform.scale = new_scale;
	queue_redraw();
}

const Vector2 &Node2D::get_scale() const {
	return transform.scale;
}

void Node2D::set_rotation(const double new_rotation) {
	transform.rotation = new_rotation;
	queue_redraw();
}

double Node2D::get_rotation() const {
	return transform.rotation;
}

void Node2D::set_global_position(const Vector2 &new_global_position) {
	Vector2 global_position = get_global_position();
	transform.origin = -Vector2(global_position - new_global_position);
	queue_redraw();
}

const Vector2 Node2D::get_global_position() const {
	return get_global_transform().origin;
}

void Node2D::set_global_scale(const Vector2 &new_global_scale) {
	Vector2 global_scale = get_global_scale();
	transform.scale = -Vector2(global_scale - new_global_scale);
}

const Vector2 Node2D::get_global_scale() const {
	return get_global_transform().scale;
}

void Node2D::set_global_rotation(const double new_global_rotation) {
	double global_rotation = get_global_rotation();
	transform.rotation = -(global_rotation - new_global_rotation);
}

double Node2D::get_global_rotation() const {
	return get_global_transform().rotation;
}

void Node2D::set_transform(const Transform2D &new_transform) {
	transform = new_transform;
	update();
}

const Transform2D &Node2D::get_transform() const {
	return transform;
}

void Node2D::set_global_transform(const Transform2D &new_global_transform) {
	const Transform2D global_transform = get_global_transform();
	Transform2D new_transform = new_global_transform;

	transform.origin = -(global_transform.origin - new_global_transform.origin);
	transform.rotation = -(global_transform.rotation - new_transform.rotation);
	transform.scale = -(global_transform.scale - new_transform.scale);
	queue_redraw();
}

const Transform2D Node2D::get_global_transform() const {
	std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();

	if (rendering_server) {
		const std::optional<const Transform2D> global_transform = rendering_server->canvas_item_get_global_transform(canvas_item);
		return global_transform.has_value() ? global_transform.value() : transform;
	}
	
	return transform;
}

void Node2D::set_modulate(const Color &new_modulate) {
	modulate = new_modulate;
	queue_redraw();
}

const Color &Node2D::get_modulate() const {
	return modulate;
}

const Color Node2D::get_absolute_modulate() const {
	std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();

	if (rendering_server) {
		const std::optional<const Color> absolute_modulate = rendering_server->canvas_item_get_global_modulate(canvas_item);
		return absolute_modulate.has_value() ? absolute_modulate.value() : modulate;
	}

	return modulate;
}

void Node2D::set_blend_mode(const SDL_BlendMode new_blend_mode) {
	blend_mode = new_blend_mode;
	queue_redraw();
}

SDL_BlendMode Node2D::get_blend_mode() const {
	return blend_mode;
}

void Node2D::set_scale_mode(const SDL_ScaleMode scaling_mode) {
	scale_mode = scaling_mode;
	queue_redraw();
}

SDL_ScaleMode Node2D::get_scale_mode() const {
	return scale_mode;
}

void Node2D::hide() {
	if (!visible)
		return;

	visible = false;
	hidden();
	visibility_changed();
	queue_redraw();
}

void Node2D::show() {
	if (visible)
		return;

	visible = true;
	visibility_changed();
	queue_redraw();
}

bool Node2D::is_visible() const {
	return visible;
}

bool Node2D::is_visible_in_tree() const {
	std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();

	if (rendering_server) {
		const std::optional<bool> is_visible = rendering_server->canvas_item_is_globally_visible(canvas_item);
		return is_visible.has_value() ? is_visible.value() : visible;
	}

	return visible;
}

bool Node2D::is_visible_inside_viewport() const {
	std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();

	if (rendering_server) {
		const std::optional<bool> is_visible = rendering_server->canvas_item_is_visible_inside_viewport(canvas_item);
		return is_visible.has_value() ? is_visible.value() : visible;
	}

	return visible;
}

void Node2D::set_zindex(const int zindex) {
	this->zindex = zindex;
}

int Node2D::get_zindex() const {
	return zindex;
}

int Node2D::get_absolute_zindex() const {
	std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();
	if (rendering_server) {
		const std::optional<int> global_zindex = rendering_server->canvas_item_get_absolute_zindex(canvas_item);
		return global_zindex.has_value() ? global_zindex.value() : 0;
	}

	return 0;
}

void Node2D::set_zindex_relative(const bool zindex_relative) {
	this->zindex_relative = zindex_relative;
	update();
}

void Node2D::draw_texture(const std::shared_ptr<Texture2D> &texture, const Transform2D &texture_transform, const Color &modulation) const {
	std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();
	if (rendering_server)
		rendering_server->canvas_item_add_texture(texture->get_uid(), canvas_item, SDL_FLIP_NONE, modulation, texture_transform);
}

void Node2D::draw_texture_rect(const std::shared_ptr<Texture2D> &texture, const Rect2i &region, const Transform2D &texture_transform, const Color &modulation) const {
	std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();
	if (rendering_server)
		rendering_server->canvas_item_add_texture_region(texture->get_uid(), canvas_item, region, SDL_FLIP_NONE, modulation, texture_transform);
}

void Node2D::draw_line(const Vector2 &start, const Vector2 &end, const Color &modulation) const {
	std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();
	if (rendering_server)
		rendering_server->canvas_item_add_line(canvas_item, start, end,  modulation);
}

void Node2D::draw_lines(const std::vector<SDL_FPoint> &points, const Color &modulation) const {
	std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();
	if (rendering_server)
		rendering_server->canvas_item_add_lines(canvas_item, points, modulation);
}

void Node2D::draw_rect(const Rect2 &rect, const Color &modulation) const {
	std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();
	if (rendering_server)
		rendering_server->canvas_item_add_rect(canvas_item, rect, modulation);
}

void Node2D::draw_rects(const std::vector<SDL_FRect> &rects, const Color &modulation) const {
	std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();
	if (rendering_server)
		rendering_server->canvas_item_add_rects(canvas_item, rects, modulation);
}