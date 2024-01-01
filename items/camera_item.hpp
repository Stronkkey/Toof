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
	CameraItem();

	Vector2 offset, zoom;
	real_t position_smoothing_speed, rotation_smoothing_speed;
	bool ignore_rotation, position_smoothing_enabled, rotation_smoothing_enabled;

	std::optional<Transform2D> get_camera_transform() const;

};

}