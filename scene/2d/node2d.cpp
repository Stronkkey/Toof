#include <scene/2d/node2d.hpp>
#include <servers/rendering/window.hpp>
#include <scene/main/scene_tree.hpp>
#include <scene/resources/texture2d.hpp>

using namespace Toof;

void Node2D::set_scale(const Vector2f &new_scale) {
	transform.scale = new_scale;
	queue_redraw();
}

void Node2D::set_rotation(const Angle new_rotation) {
	transform.rotation = new_rotation;
	queue_redraw();
}

void Node2D::set_position(const Vector2f &position) {
	transform.origin = position;
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

Transform2D Node2D::get_transform() const {
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
