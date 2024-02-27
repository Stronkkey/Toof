#include <scene/2d/camera2d.hpp>
#include <servers/rendering/viewport.hpp>

#include <core/utility_functions.hpp>

using namespace sdl;

Camera2D::Camera2D(): offset(),
    zoom(Vector2(1, 1)),
    position_smoothing_speed(10.0),
    rotation_smoothing_speed(10.0),
    drag_bottom_margin(0.2),
    drag_left_margin(0.2),
    drag_right_margin(0.2),
    drag_top_margin(0.2),
    drag_vertical_offset(0.0),
    drag_horizontal_offset(0.0),
    limit_bottom(-10000000.0),
    limit_left(-10000000.0),
    limit_right(10000000.0),
    limit_top(10000000.0),
    enabled(true),
    limit_smoothed(true),
    drag_horizontal_enabled(false),
    drag_vertical_enabled(false),
    ignore_rotation(true),
    position_smoothing_enabled(false),
    rotation_smoothing_enabled(false),
    fix_x(false),
    fix_y(false),
    process_callback(CAMERA2D_PROCESS_RENDER),
    anchor_mode(CAMERA2D_ANCHOR_DRAG_CENTER) {
}

Vector2 Camera2D::_get_target_scale() const {
	return zoom;
}

Vector2 Camera2D::_get_target_position() const {
	Vector2 target_position;

	if (position_smoothing_enabled) {
		real_t c = position_smoothing_speed * (process_callback == CAMERA2D_PROCESS_LOOP ? get_process_delta_time() : get_delta_time());
		target_position = std::min(_get_camera_position().lerp(get_global_position(), c), get_global_position());
	} else
		target_position = get_global_position();

	if (anchor_mode == CAMERA2D_ANCHOR_DRAG_CENTER)
		target_position -= (_get_viewport_size() / 2.0);

	if (!position_smoothing_enabled)
		_limit_vector(target_position);

	return -target_position;
}

Angle Camera2D::_get_target_rotation() const {
	Angle target_rotation;

	if (ignore_rotation)
		target_rotation = 0.0;
	else
	 	target_rotation = get_global_rotation();

	return target_rotation;
}

Transform2D Camera2D::_get_target_transform() const {
	return Transform2D(_get_target_rotation(), _get_target_position(), _get_target_scale());
}

Vector2i Camera2D::_get_viewport_size() const {
	const Viewport *viewport = get_rendering_server() ? get_rendering_server()->get_viewport() : nullptr;

	return viewport ? viewport->get_viewport_size() : Vector2i();
}

Transform2D Camera2D::_get_canvas_transform() const {
	const Viewport *viewport = get_rendering_server() ? get_rendering_server()->get_viewport() : nullptr;

	return viewport ? viewport->get_canvas_transform() : Transform2D();
}

Vector2 Camera2D::_get_camera_position() const {
	const Viewport *viewport = get_rendering_server() ? get_rendering_server()->get_viewport() : nullptr;

	Vector2 camera_position = viewport ? viewport->get_canvas_transform().origin : Vector2();
	if (viewport && anchor_mode == CAMERA2D_ANCHOR_DRAG_CENTER)
		camera_position -= (viewport->get_viewport_size() / 2.0);

	return -camera_position;
}

void Camera2D::_step_camera() const {
	Viewport *viewport = get_rendering_server() ? get_rendering_server()->get_viewport() : nullptr;

	if (viewport) {
		const Transform2D &canvas_transform = viewport->get_canvas_transform();
		Transform2D target_transform = _get_target_transform();

		if (fix_x)
			target_transform.origin.x = canvas_transform.origin.x;
		if (fix_y)
			target_transform.origin.y = canvas_transform.origin.y;

		viewport->set_canvas_transform(target_transform);
	}
}

void Camera2D::_limit_vector(Vector2 &vector) const {
	vector.x = std::min(std::max(limit_left, vector.x), limit_right);
	vector.y = std::min(std::max(limit_bottom, vector.y), limit_top);
}

void Camera2D::_notification(const int what) {
	Node2D::_notification(what);

	bool can_proccess = (what == NOTIFICATION_PROCESS && process_callback == CAMERA2D_PROCESS_LOOP)
	                    || (what == NOTIFICATION_RENDER && process_callback == CAMERA2D_PROCESS_RENDER);
	if (enabled && can_proccess)
		_step_camera();
}

Transform2D Camera2D::get_target_transform() const {
	if (get_rendering_server() && get_rendering_server()->get_viewport())
		return _get_target_transform();
	return get_transform();
}

void Camera2D::align() const {
	Viewport *viewport = get_rendering_server() ? get_rendering_server()->get_viewport() : nullptr;
	Transform2D transform = _get_target_transform();
	transform.origin = get_global_position();

	if (viewport)
		viewport->set_canvas_transform(transform);
}

Vector2 Camera2D::get_screen_center_position() const {
	return _get_target_position();
}