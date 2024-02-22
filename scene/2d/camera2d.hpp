#pragma once

#include <scene/2d/node2d.hpp>

#include <optional>

namespace sdl {

class Camera2D : public Node2D {
public:
	enum CameraItemProcessCallback {
		CAMERA_ITEM_PROCESS_LOOP,
		CAMERA_ITEM_PROCESS_RENDER,
		CAMERA_ITEM_PROCESS_LOOP_RENDER,
		CAMERA_ITEM_PROCESS_NONE
	};

	enum CameraItemAnchorMode {
		CAMERA_ITEM_ANCHOR_FIXED_TOP_LEFT,
		CAMERA_ITEM_ANCHOR_DRAG_CENTER
	};
private:
	Transform2D _get_camera_transform() const;
	bool _can_process(const int what) const;
	void _step_camera(const double what);
	void _notification(const int what) override;

	Vector2 offset;
	Vector2 zoom;
	real_t position_smoothing_speed;
	real_t rotation_smoothing_speed;
	bool ignore_rotation;
	bool position_smoothing_enabled;
	bool rotation_smoothing_enabled;
	bool fix_x;
	bool fix_y;
	
	CameraItemProcessCallback process_callback;
	CameraItemAnchorMode anchor_mode;
public:
	Camera2D() = default;
	~Camera2D() = default;

	constexpr void set_offset(const Vector2 &offset) {
		this->offset = offset;
	}

	constexpr const Vector2 &get_offset() const {
		return offset;
	}

	constexpr void set_zoom(const Vector2 &zoom) {
		this->zoom = zoom;
	}

	constexpr const Vector2 &get_zoom() const {
		return zoom;
	}

	constexpr void set_position_smoothing_speed(const real_t position_smoothing_speed) {
		this->position_smoothing_speed = position_smoothing_speed;
	}

	constexpr real_t get_position_smoothing_speed() const {
		return position_smoothing_speed;
	}

	constexpr void set_rotation_smoothing_speed(const real_t rotation_smoothing_speed) {
		this->rotation_smoothing_speed = rotation_smoothing_speed;
	}

	constexpr real_t get_rotation_smoothing_speed() const {
		return rotation_smoothing_speed;
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

	constexpr void set_process_callback(const CameraItemProcessCallback process_callback) {
		this->process_callback = process_callback;
	}

	constexpr CameraItemProcessCallback get_process_callback() const {
		return process_callback;
	}

	constexpr void set_anchor_mode(const CameraItemAnchorMode anchor_mode) {
		this->anchor_mode = anchor_mode;
	}

	constexpr CameraItemAnchorMode get_anchor_mode() const {
		return anchor_mode;
	}

	std::optional<Transform2D> get_camera_transform() const;
};

}