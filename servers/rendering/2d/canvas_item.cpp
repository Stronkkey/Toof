#include <servers/rendering/2d/canvas_item.hpp>
#include <servers/rendering/2d/drawing_item.hpp>

using namespace sdl;

Transform2D CanvasItem::get_global_transform() const {
	if (parent.expired())
		return transform;
	Transform2D absolute_transform = transform;
	std::shared_ptr<CanvasItem> parent_canvas_item = parent.lock();

	while (parent_canvas_item) {
		absolute_transform *= parent_canvas_item->transform;
		parent_canvas_item = parent_canvas_item->parent.lock();
	}

	return absolute_transform;
}

Color CanvasItem::get_absolute_modulate() const {
	if (parent.expired())
		return modulate;
	Color absolute_modulate = modulate;
	std::shared_ptr<CanvasItem> parent_canvas_item = parent.lock();

	while (parent_canvas_item) {
		absolute_modulate *= parent_canvas_item->modulate;
		parent_canvas_item = parent_canvas_item->parent.lock();
	}

	return absolute_modulate;
}

bool CanvasItem::is_visible() const {
	if (parent.expired())
		return visible;
	std::shared_ptr<CanvasItem> parent_canvas_item = parent.lock();

	while (parent_canvas_item) {
		if (!parent_canvas_item->visible)
			return false;

		parent_canvas_item = parent_canvas_item->parent.lock();
	}

	return true;
}