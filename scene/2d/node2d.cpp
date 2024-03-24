#include <scene/2d/node2d.hpp>
#include <servers/rendering/window.hpp>
#include <scene/main/scene_tree.hpp>
#include <scene/resources/texture2d.hpp>

#include <typeinfo>

using namespace sdl;

Node2D::Node2D():
    transform(Transform2D::IDENTITY),
    canvas_item(0),
    modulate(ColorV(255, 255, 255, 255)),
    blend_mode(SDL_BLENDMODE_BLEND),
    scale_mode(SDL_ScaleModeLinear),
    visible(true),
    zindex_relative(true),
    update_queued(false),
    zindex(0) {
}

Node2D::~Node2D() {
	const std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();

	if (rendering_server)
		rendering_server->remove_uid(canvas_item);
}

void Node2D::ready() {
	transform = transform.IDENTITY;
	canvas_item = get_rendering_server()->create_canvas_item();

	queue_redraw();
}

const std::unique_ptr<RenderingServer> &Node2D::get_rendering_server() const {
	if (is_inside_tree())
		return get_tree()->get_rendering_server();
	
	const std::unique_ptr<RenderingServer> _r, *r = &_r;
	return *r;
}

void Node2D::_update() {
	const std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();
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

void Node2D::_on_parent_changed(Node *new_parent) {
	const std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();
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
			_on_parent_changed(get_parent());
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

	SceneTree *tree = get_tree();
	tree->deferred_signals.connect(std::bind(&Node2D::_update, this));
	tree->deferred_signals.connect(std::bind(&Node::notification, this, NOTIFICATION_DRAW));
}

void Node2D::set_position(const Vector2f &new_position) {
	transform.origin = new_position;
	queue_redraw();
}

void Node2D::set_scale(const Vector2f &new_scale) {
	transform.scale = new_scale;
	queue_redraw();
}

void Node2D::set_rotation(const Angle new_rotation) {
	transform.rotation = new_rotation;
	queue_redraw();
}

void Node2D::set_global_position(const Vector2f &new_global_position) {
	Vector2 global_position = get_global_position();
	transform.origin = -Vector2(global_position - new_global_position);
	queue_redraw();
}

const Vector2f Node2D::get_global_position() const {
	return get_global_transform().origin;
}

void Node2D::set_global_scale(const Vector2f &new_global_scale) {
	Vector2 global_scale = get_global_scale();
	transform.scale = -Vector2(global_scale - new_global_scale);
	queue_redraw();
}

const Vector2f Node2D::get_global_scale() const {
	return get_global_transform().scale;
}

void Node2D::set_global_rotation(const Angle new_global_rotation) {
	Angle global_rotation = get_global_rotation();
	transform.rotation = -(global_rotation - new_global_rotation);
}

Angle Node2D::get_global_rotation() const {
	return get_global_transform().rotation;
}

void Node2D::set_transform(const Transform2D &new_transform) {
	transform = new_transform;
	queue_redraw();
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
	const std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();

	if (rendering_server)
		return rendering_server->canvas_item_get_global_transform(canvas_item).value_or(transform);
	return transform;
}

void Node2D::set_modulate(const ColorV &new_modulate) {
	modulate = new_modulate;
	queue_redraw();
}

const ColorV &Node2D::get_modulate() const {
	return modulate;
}

const ColorV Node2D::get_absolute_modulate() const {
	const std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();

	if (rendering_server)
		return rendering_server->canvas_item_get_global_modulate(canvas_item).value_or(modulate);
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

bool Node2D::is_visible_in_tree() const {
	const std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();

	if (rendering_server)
		return rendering_server->canvas_item_is_globally_visible(canvas_item).value_or(visible);
	return visible;
}

bool Node2D::is_visible_inside_viewport() const {
	const std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();

	if (rendering_server)
		return rendering_server->canvas_item_is_visible_inside_viewport(canvas_item).value_or(visible);
	return visible;
}

void Node2D::set_zindex(const int zindex) {
	this->zindex = zindex;
	queue_redraw();
}

int Node2D::get_absolute_zindex() const {
	const std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();

	if (rendering_server)
		return rendering_server->canvas_item_get_absolute_zindex(canvas_item).value_or(zindex);
	return zindex;
}

void Node2D::set_zindex_relative(const bool zindex_relative) {
	this->zindex_relative = zindex_relative;
	queue_redraw();
}

void Node2D::draw_texture(const uid texture_uid, const Transform2D &texture_transform, const ColorV &modulation) const {
	const std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();

	if (rendering_server)
		rendering_server->canvas_item_add_texture(texture_uid, canvas_item, SDL_FLIP_NONE, modulation, texture_transform);
}

void Node2D::draw_texture_rect(const uid texture_uid, const Rect2i &region, const Transform2D &texture_transform, const ColorV &modulation) const {
	const std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();

	if (rendering_server)
		rendering_server->canvas_item_add_texture_region(texture_uid, canvas_item, region, SDL_FLIP_NONE, modulation, texture_transform);
}

void Node2D::draw_line(const Vector2f &start, const Vector2f &end, const ColorV &modulation) const {
	const std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();
	if (rendering_server)
		rendering_server->canvas_item_add_line(canvas_item, start, end,  modulation);
}

void Node2D::draw_lines(const std::vector<SDL_FPoint> &points, const ColorV &modulation) const {
	const std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();
	if (rendering_server)
		rendering_server->canvas_item_add_lines(canvas_item, points, modulation);
}

void Node2D::draw_rect(const Rect2f &rect, const ColorV &modulation) const {
	const std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();
	if (rendering_server)
		rendering_server->canvas_item_add_rect(canvas_item, rect, modulation);
}

void Node2D::draw_rects(const std::vector<SDL_FRect> &rects, const ColorV &modulation) const {
	const std::unique_ptr<RenderingServer> &rendering_server = get_rendering_server();
	if (rendering_server)
		rendering_server->canvas_item_add_rects(canvas_item, rects, modulation);
}