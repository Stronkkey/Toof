#include <items/camera_item.hpp>
#include <rendering/viewport.hpp>

using namespace sdl;

CameraItem::CameraItem(): offset(),
    zoom(Vector2::ONE),
    position_smoothing_speed(360),
    rotation_smoothing_speed(360),
    ignore_rotation(true),
    position_smoothing_enabled(false),
    rotation_smoothing_enabled(false) {
}

Transform2D CameraItem::_get_camera_transform() const {
	Viewport *viewport = get_rendering_server()->get_viewport();

	Vector2 final_offset = offset;
	Vector2 camera_position;
	Vector2 global_scale;
	double camera_rotation = 0;

	final_offset.x += (real_t)-(viewport->get_viewport_size().x / 4.0);
	
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

void CameraItem::step_camera(const double) {
	Viewport *viewport = get_rendering_server() ? get_rendering_server()->get_viewport() : nullptr;

	if (!viewport)
		return;

	viewport->set_canvas_transform(_get_camera_transform());
}

void CameraItem::_notification(const int what) {
	RenderingItem::_notification(what);

	switch (what) {
		case NOTIFICATION_RENDER:
			step_camera(get_delta_time());
			break;
		default:
			break;
	}
}

std::optional<Transform2D> CameraItem::get_camera_transform() const {
	if (get_rendering_server() && get_rendering_server()->get_viewport())
		return _get_camera_transform();
	return std::nullopt;
}