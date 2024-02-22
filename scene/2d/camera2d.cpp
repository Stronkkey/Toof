#include <scene/2d/camera2d.hpp>
#include <servers/rendering/viewport.hpp>

using namespace sdl;

Transform2D Camera2D::_get_camera_transform() const {
	Viewport *viewport = get_rendering_server()->get_viewport();

	Vector2 final_offset = offset;
	Vector2 camera_position;
	//Vector2 global_scale;
	Angle camera_rotation = 0;

	if (anchor_mode == CAMERA_ITEM_ANCHOR_DRAG_CENTER)
		final_offset -= (viewport->get_viewport_size() / 2);

	if (!position_smoothing_enabled)
		camera_position = get_global_position() + final_offset;
	else { // What the hell
		real_t c = position_smoothing_speed * get_delta_time();
		camera_position = viewport->get_canvas_transform().origin + final_offset;
		camera_position = camera_position.move_toward(get_global_position(), c);
	}

	if (!ignore_rotation)
		camera_rotation = get_global_rotation();

	return Transform2D(camera_rotation, -camera_position, zoom);
}

bool Camera2D::_can_process(const int what) const {
	if (what == NOTIFICATION_RENDER)
		if (process_callback == CAMERA_ITEM_PROCESS_LOOP_RENDER || process_callback == CAMERA_ITEM_PROCESS_RENDER)
			return true;

	if (what == NOTIFICATION_PROCESS)
		if (process_callback == CAMERA_ITEM_PROCESS_LOOP_RENDER || process_callback == CAMERA_ITEM_PROCESS_LOOP)
			return true;

	return false;
}

void Camera2D::_step_camera(const double) {
	Viewport *viewport = get_rendering_server() ? get_rendering_server()->get_viewport() : nullptr;

	if (viewport) {
		const Transform2D &canvas_transform = viewport->get_canvas_transform();
		Transform2D camera_transform = _get_camera_transform();

		if (fix_x)
			camera_transform.origin.x = canvas_transform.origin.x;
		if (fix_y)
			camera_transform.origin.y = canvas_transform.origin.y;

		viewport->set_canvas_transform(camera_transform);
	}
}

void Camera2D::_notification(const int what) {
	Node2D::_notification(what);

	if (process_callback == CAMERA_ITEM_PROCESS_NONE)
		return;

	if (_can_process(what))
		_step_camera(what == NOTIFICATION_RENDER ? get_delta_time() : get_process_delta_time());
}

std::optional<Transform2D> Camera2D::get_camera_transform() const {
	if (get_rendering_server() && get_rendering_server()->get_viewport())
		return _get_camera_transform();
	return std::nullopt;
}