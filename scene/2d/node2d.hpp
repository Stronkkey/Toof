#pragma once

#include <scene/main/canvas_node.hpp>

#include <core/math/transform2d.hpp>
#include <core/math/color.hpp>
#include <servers/rendering_server.hpp>

namespace Toof {

class Texture2D;
/** A 2D GameObject. Has a position, scale, and rotation.*/

class Node2D : public CanvasNode {
public:
	enum {
		NOTIFICATION_DRAW = 900 /** Notification received when redraw is called. This is called once during _ready.*/,
		NOTIFICATION_VISIBILITY_CHANGED /** Notification received when the visibility of the node2d changes.*/,
	};
private:
	Transform2D transform = Transform2D::IDENTITY;
public:
	Node2D() = default;
	~Node2D() = default;

	/**
	* Sets the relative scale for this node2d to @param new_scale.
	*/
	void set_scale(const Vector2f &new_scale);

	/**
	* @returns the scale of this node2d, relative to the parent.
	*/
	constexpr const Vector2f &get_scale() const {
		return transform.scale;
	}

	/**
	* Sets the relative rotation for this node2d to @param new_rotation.
	*/
	void set_rotation(const Angle new_rotation);

	/**
	* @returns the relative rotation of this node2d, relative to the parent.
	*/
	constexpr Angle get_rotation() const {
		return transform.rotation;
	}

	/**
	* @brief sets the position and redraws.
	*/
	void set_position(const Vector2f &position);

	/**
	* @returns the position of this Node2D, in relativity to the parent.
	*/
	constexpr const Vector2f &get_position() const {
		return transform.origin;
	}

	/**
	* Sets the global position for this node2d to @param new_global_position.
	*/
	void set_global_position(const Vector2f &new_global_position);

	/**
	* @returns the global position of this node2d.
	*/
	const Vector2f get_global_position() const;

	/**
	* Sets the global scale for this node2d to @param new_global_scale.
	*/
	void set_global_scale(const Vector2f &new_global_scale);

	/**
	* @returns the global scale of this node2d.
	*/
	const Vector2f get_global_scale() const;

	/**
	* Sets the global rotation for this node2d to @param new_global_rotation.
	*/
	void set_global_rotation(const Angle new_global_rotation);

	/**
	* @returns the global rotation of this node2d.
	*/
	Angle get_global_rotation() const;

	/**
	* Sets the relative transform (position, scale, and rotation) for this node2d to @param new_transform.
	*/
	void set_transform(const Transform2D &new_transform);

	/**
	* @returns the relative transform (position, scale, and rotation) of this node2d.
	*/
	Transform2D get_transform() const override;

	/**
	* Sets the global transform (position, scale, and rotation) for this node2d to @param new_global_transform.
	*/
	void set_global_transform(const Transform2D &new_global_transform);
};

}
