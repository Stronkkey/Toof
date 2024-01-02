#pragma once

#include <items/rendering_item.hpp>

#include <optional>

namespace sdl {

class CameraItem : public RenderingItem {

private:
	Transform2D _get_camera_transform() const;
	void step_camera(const double what);

protected:
	void _notification(const int what) override;

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

public:
	CameraItem();

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

	std::optional<Transform2D> get_camera_transform() const;
};

}