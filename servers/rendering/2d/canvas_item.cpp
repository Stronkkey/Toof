#include <servers/rendering/2d/canvas_item.hpp>
#include <servers/rendering/2d/drawing_item.hpp>

using namespace sdl;

#define __EXPIRED_CHECK__ if (parent.expired()) {parent.reset(); return; }

void __CanvasItem__::set_global_transform() {
	__EXPIRED_CHECK__

	global_transform = transform;
	std::shared_ptr<__CanvasItem__> parent_canvas_item = parent.lock();

	while (parent_canvas_item) {
		global_transform *= parent_canvas_item->transform;
		parent_canvas_item = parent_canvas_item->parent.lock();
	}
}

void __CanvasItem__::set_global_modulate() {
	__EXPIRED_CHECK__

	global_modulate = modulate;
	std::shared_ptr<__CanvasItem__> parent_canvas_item = parent.lock();

	while (parent_canvas_item) {
		global_modulate *= parent_canvas_item->modulate;
		parent_canvas_item = parent_canvas_item->parent.lock();
	}
}

void __CanvasItem__::set_global_visible() {
	__EXPIRED_CHECK__

	if (!visible) {
		global_visible = false;
		return;
	}

	global_visible = true;
	std::shared_ptr<__CanvasItem__> parent_canvas_item = parent.lock();

	while (parent_canvas_item && global_visible) {
		global_visible = parent_canvas_item->visible;
		parent_canvas_item = parent_canvas_item->parent.lock();
	}
}

void __CanvasItem__::set_global_zindex() {
	__EXPIRED_CHECK__

	if (!zindex_relative) {
		global_zindex = zindex;
		return;
	}

	std::shared_ptr<__CanvasItem__> parent_canvas_item = parent.lock();
	global_zindex = zindex;

	while (parent_canvas_item) {
		global_zindex += parent_canvas_item->zindex;
		parent_canvas_item = parent_canvas_item->parent.lock();
	}
}

const Transform2D &__CanvasItem__::get_global_transform() {
	set_global_transform();
	return global_transform;
}

const ColorV &__CanvasItem__::get_global_modulate() {
	set_global_modulate();
	return global_modulate;
}

bool __CanvasItem__::is_globally_visible() {
	set_global_visible();
	return global_visible;
}

int __CanvasItem__::get_global_zindex() {
	set_global_zindex();
	return global_zindex;
}