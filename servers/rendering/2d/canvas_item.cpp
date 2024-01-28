#include <servers/rendering/2d/canvas_item.hpp>
#include <servers/rendering/2d/drawing_item.hpp>

using namespace sdl;

void CanvasItem::set_global_transform() {
	if (parent.expired())
		return;

	global_transform = transform;
	std::shared_ptr<CanvasItem> parent_canvas_item = parent.lock();

	while (parent_canvas_item) {
		global_transform *= parent_canvas_item->transform;
		parent_canvas_item = parent_canvas_item->parent.lock();
	}
}

void CanvasItem::set_global_modulate() {
	if (parent.expired())
		return;

	global_modulate = modulate;
	std::shared_ptr<CanvasItem> parent_canvas_item = parent.lock();

	while (parent_canvas_item) {
		global_modulate *= parent_canvas_item->modulate;
		parent_canvas_item = parent_canvas_item->parent.lock();
	}
}

void CanvasItem::set_global_visible() {
	if (parent.expired())
		return;

	global_visible = visible;
	std::shared_ptr<CanvasItem> parent_canvas_item = parent.lock();

	while (parent_canvas_item && global_visible) {
		global_visible = parent_canvas_item->visible;
		parent_canvas_item = parent_canvas_item->parent.lock();
	}
}

void CanvasItem::set_global_zindex() {
	if (parent.expired())
		return;

	if (!zindex_relative) {
		global_zindex = zindex;
		return;
	}

	std::shared_ptr<CanvasItem> parent_canvas_item = parent.lock();
	global_zindex = zindex;

	while (parent_canvas_item) {
		global_zindex += parent_canvas_item->zindex;
		parent_canvas_item = parent_canvas_item->parent.lock();
	}
}

const Transform2D &CanvasItem::get_global_transform() {
	set_global_transform();
	return global_transform;
}

const Color &CanvasItem::get_global_modulate() {
	set_global_modulate();
	return global_modulate;
}

bool CanvasItem::is_globally_visible() {
	set_global_visible();
	return global_visible;
}

int CanvasItem::get_global_zindex() {
	set_global_zindex();
	return global_zindex;
}