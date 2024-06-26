/*  This file is part of the Toof Engine. */
/*
  BSD 3-Clause License

  Copyright (c) 2024-present, Stronkkey and Contributors

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
      list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <scene/2d/camera2d.hpp>
#include <servers/rendering/viewport.hpp>

using namespace Toof;

Camera2D::Camera2D(): offset(),
    zoom(Vector2f::ONE()),
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

Vector2f Camera2D::_get_target_scale() const {
	return zoom;
}

Vector2f Camera2D::_get_target_position() const {
	Vector2f target_position;

	if (position_smoothing_enabled) {
		real c = position_smoothing_speed * (process_callback == CAMERA2D_PROCESS_LOOP ? get_process_delta_time() : get_delta_time());
		target_position = std::min(_get_camera_position().lerp(get_global_position(), c), get_global_position());
	} else
		target_position = get_global_position();

	if (anchor_mode == CAMERA2D_ANCHOR_DRAG_CENTER)
		target_position -= (_get_viewport_size() / 2);

	if (!position_smoothing_enabled)
		_limit_vector(target_position);

	return -target_position;
}

Angle Camera2D::_get_target_rotation() const {
	Angle target_rotation;

	if (ignore_rotation)
		target_rotation = Angle::ZERO_ROTATION();
	else
	 	target_rotation = get_global_rotation();

	return target_rotation;
}

Transform2D Camera2D::_get_target_transform() const {
	return Transform2D(_get_target_rotation(), _get_target_position(), _get_target_scale());
}

Vector2i Camera2D::_get_viewport_size() const {
	Optional<Viewport*> viewport = _get_viewport();

	return viewport ? viewport.get_value()->get_viewport_size() : Vector2i();
}

Transform2D Camera2D::_get_canvas_transform() const {
	Optional<Viewport*> viewport = _get_viewport();

	return viewport ? viewport.get_value()->get_canvas_transform() : Transform2D();
}

Vector2f Camera2D::_get_camera_position() const {
	Optional<Viewport*> viewport = _get_viewport();

	Vector2f camera_position = viewport ? viewport.get_value()->get_canvas_transform().origin : Vector2f::ZERO();
	if (viewport && anchor_mode == CAMERA2D_ANCHOR_DRAG_CENTER)
		camera_position -= (viewport.get_value()->get_viewport_size() / (unsigned long)2.0);

	return -camera_position;
}

void Camera2D::_set_camera_transform(const Transform2D &transform) const {
	Optional<Viewport*> viewport = _get_viewport();

	if (viewport)
		viewport.get_value()->set_canvas_transform(transform);
}

void Camera2D::_step_camera() const {
	Optional<Viewport*> viewport = _get_viewport();

	if (viewport) {
		const Transform2D &canvas_transform = viewport.get_value()->get_canvas_transform();
		Transform2D target_transform = _get_target_transform();

		if (fix_x)
			target_transform.origin.x = canvas_transform.origin.x;
		if (fix_y)
			target_transform.origin.y = canvas_transform.origin.y;

		viewport.get_value()->set_canvas_transform(target_transform);
	}
}

void Camera2D::_limit_vector(Vector2f &vector) const {
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

Optional<Viewport*> Camera2D::_get_viewport() const {
	if (get_rendering_server())
		return get_rendering_server().get_value()->get_viewport();
	return NullOption;
}

Transform2D Camera2D::get_target_transform() const {
	if (_get_viewport())
		return _get_target_transform();
	return get_transform();
}

Optional<const Transform2D&> Camera2D::get_camera_transform() const {
	Optional<Viewport*> viewport = _get_viewport();

	if (viewport)
		return viewport.get_value()->get_canvas_transform();

	return NullOption;
}

void Camera2D::set_camera_transform(const Transform2D &transform) const {
	_set_camera_transform(transform);
}

void Camera2D::align() const {
	Optional<Viewport*> viewport = _get_viewport();
	Transform2D transform = _get_target_transform();
	transform.origin = get_global_position();

	if (viewport)
		viewport.get_value()->set_canvas_transform(transform);
}

Vector2f Camera2D::get_screen_center_position() const {
	return _get_target_position();
}