#pragma once

#include <scene/2d/node2d.hpp>

namespace sdl {

class Camera2D : public Node2D {
public:
	enum Camera2DProcessCallback {
		CAMERA2D_PROCESS_LOOP,
		CAMERA2D_PROCESS_RENDER,
	};

	enum Camera2DAnchorMode {
		CAMERA2D_ANCHOR_FIXED_TOP_LEFT,
		CAMERA2D_ANCHOR_DRAG_CENTER
	};
private:
	Vector2f _get_target_scale() const;
	Vector2f _get_target_position() const;
	Angle _get_target_rotation() const;
	Transform2D _get_target_transform() const;
	Vector2i _get_viewport_size() const;
	Transform2D _get_canvas_transform() const;
	Vector2f _get_camera_position() const;
	void _step_camera() const;
	void _limit_vector(Vector2f &vector) const;
	void _notification(const int what) override;
	Optional<Viewport*> _get_viewport() const;

	Vector2f offset;
	Vector2f zoom;
	real position_smoothing_speed;
	real rotation_smoothing_speed;
	real drag_bottom_margin;
	real drag_left_margin;
	real drag_right_margin;
	real drag_top_margin;
	real drag_vertical_offset;
	real drag_horizontal_offset;
	real limit_bottom;
	real limit_left;
	real limit_right;
	real limit_top;
	bool enabled;
	bool limit_smoothed;
	bool drag_horizontal_enabled;
	bool drag_vertical_enabled;
	bool ignore_rotation;
	bool position_smoothing_enabled;
	bool rotation_smoothing_enabled;
	bool fix_x;
	bool fix_y;
	
	Camera2DProcessCallback process_callback;
	Camera2DAnchorMode anchor_mode;
public:
	Camera2D();
	~Camera2D() = default;

	constexpr void set_offset(const Vector2f &offset) {
		this->offset = offset;
	}

	constexpr const Vector2f &get_offset() const {
		return offset;
	}

	constexpr void set_zoom(const Vector2f &zoom) {
		this->zoom = zoom;
	}

	constexpr const Vector2f &get_zoom() const {
		return zoom;
	}

	constexpr void set_position_smoothing_speed(const real position_smoothing_speed) {
		this->position_smoothing_speed = position_smoothing_speed;
	}

	constexpr real get_position_smoothing_speed() const {
		return position_smoothing_speed;
	}

	constexpr void set_rotation_smoothing_speed(const real rotation_smoothing_speed) {
		this->rotation_smoothing_speed = rotation_smoothing_speed;
	}

	constexpr real get_rotation_smoothing_speed() const {
		return rotation_smoothing_speed;
	}

	constexpr void set_drag_bottom_margin(const real drag_bottom_margin) {
		this->drag_bottom_margin = drag_bottom_margin;
	}

	constexpr real get_drag_bottom_margin() const {
		return drag_bottom_margin;
	}

	constexpr void set_drag_left_margin(const real drag_left_margin) {
		this->drag_left_margin = drag_left_margin;
	}

	constexpr real get_drag_left_margin() const {
		return drag_left_margin;
	}

	constexpr void set_drag_right_margin(const real drag_right_margin) {
		this->drag_right_margin = drag_right_margin;
	}

	constexpr real get_drag_right_margin() const {
		return drag_right_margin;
	}

	constexpr void set_drag_top_margin(const real drag_top_margin) {
		this->drag_top_margin = drag_top_margin;
	}

	constexpr real get_drag_top_margin() const {
		return drag_top_margin;
	}

	constexpr void set_drag_vertical_offset(const real drag_vertical_offset) {
		this->drag_vertical_offset = drag_vertical_offset;
	}

	constexpr real get_drag_vertical_offset() const {
		return drag_vertical_offset;
	}

	constexpr void set_drag_horizontal_offset(const real drag_horizontal_offset) {
		this->drag_horizontal_offset = drag_horizontal_offset;
	}

	constexpr real get_drag_horizontal_offset() const {
		return drag_horizontal_offset;
	}

	constexpr void set_limit_bottom(const real limit_bottom) {
		this->limit_bottom = limit_bottom;
	}

	constexpr real get_limit_bottom() const {
		return limit_bottom;
	}

	constexpr void set_limit_left(const real limit_left) {
		this->limit_left = limit_left;
	}

	constexpr real get_limit_left() const {
		return limit_left;
	}

	constexpr void set_limit_right(const real limit_right) {
		this->limit_right = limit_right;
	}

	constexpr real get_limit_right() const {
		return limit_right;
	}

	constexpr void set_limit_top(const real limit_top) {
		this->limit_top = limit_top;
	}

	constexpr real get_limit_top() const {
		return limit_top;
	}

	constexpr void set_enabled(const bool enabled) {
		this->enabled = enabled;
	}

	constexpr bool is_enabled() const {
		return enabled;
	}

	constexpr void set_limit_smoothed(const bool limit_smoothed) {
		this->limit_smoothed = limit_smoothed;
	}

	constexpr bool get_limit_smoothed() const {
		return limit_smoothed;
	}

	constexpr void set_drag_horizontal_enabled(const bool drag_horizontal_enabled) {
		this->drag_horizontal_enabled = drag_horizontal_enabled;
	}

	constexpr bool get_drag_horizontal_enabled() const {
		return drag_horizontal_enabled;
	}

	constexpr void set_drag_vertical_enabled(const bool drag_vertical_enabled) {
		this->drag_vertical_enabled = drag_vertical_enabled;
	}

	constexpr bool get_drag_vertical_enabled() const {
		return drag_vertical_enabled;
	}

	constexpr void set_ignore_rotation(const bool ignore_rotation) {
		this->ignore_rotation = ignore_rotation;
	}

	constexpr bool get_ignore_rotation() const {
		return ignore_rotation;
	}

	constexpr void set_position_smoothing_enabled(const bool position_smoothing_enabled) {
		this->position_smoothing_enabled = position_smoothing_enabled;
	}

	constexpr bool get_position_smoothing_enabled() const {
		return position_smoothing_enabled;
	}

	constexpr void set_rotation_smoothing_enabled(const bool rotation_smoothing_enabled) {
		this->rotation_smoothing_enabled = rotation_smoothing_enabled;
	}

	constexpr bool get_rotation_smoothing_enabled() const {
		return rotation_smoothing_enabled;
	}

	constexpr void set_fix_x(const bool fix_x) {
		this->fix_x = fix_x;
	}

	constexpr bool is_x_fixed() const {
		return fix_x;
	}

	constexpr void set_fix_y(const bool fix_y) {
		this->fix_y = fix_y;
	}

	constexpr bool is_y_fixed() const {
		return fix_y;
	}

	constexpr void set_process_callback(const Camera2DProcessCallback process_callback) {
		this->process_callback = process_callback;
	}

	constexpr Camera2DProcessCallback get_process_callback() const {
		return process_callback;
	}

	constexpr void set_anchor_mode(const Camera2DAnchorMode anchor_mode) {
		this->anchor_mode = anchor_mode;
	}

	constexpr Camera2DAnchorMode get_anchor_mode() const {
		return anchor_mode;
	}

	Transform2D get_target_transform() const;
	void align() const;
	Vector2f get_screen_center_position() const;
};

}