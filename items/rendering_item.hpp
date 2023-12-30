#pragma once

#include <items/item.hpp>

#include <types/transform2d.hpp>
#include <types/color.hpp>
#include <rendering/rendering_server.hpp>

namespace sdl {

class Texture2D;
/** A 2D GameObject. Has a position, scale, and rotation.*/

class RenderingItem : public Item {

public:
	enum {
		NOTIFICATION_DRAW = 900 /** Notification received when redraw is called. This is called once during _ready.*/,
		NOTIFICATION_VISIBILITY_CHANGED /** Notification received when the visibility of the CanvasItem changes.*/,
	};

private:
	Transform2D transform;
	uid canvas_item;
	Color modulate;
	SDL_BlendMode blend_mode;
	bool visible;

	/**
	* Syncs the transform, modulate, blend_mode and visible property with the RenderingServer.
	*/
	void update();
	void on_parent_changed(Item *new_parent);
	void ready();

protected:
	/**
	* Returns the RenderingServer inside the tree or nullptr if the tree hasn't been set.
	*/
	RenderingServer *get_rendering_server() const;

	void _notification(const int what) override;
	/**
	* Called when the RenderingItem has been requested to redraw (after redraw is called or notification NOTIFICATION_DRAW is sent).
	*/
	virtual void _draw() const;

public:
	RenderingItem();
	~RenderingItem();

	/**
	* Returns the CanvasItem uid used by the RenderingServer for this item.
	*/
	uid get_canvas_item() const;

	/**
	* Tells the RenderingItem to redraw calling _draw and sending notification NOTIFICATION_DRAW.
	*/
	void redraw();

	/**
	* Sets the relative position for this CanvasItem to @param new_position.
	*/
	void set_position(const Vector2 &new_position);

	/**
	* Returns the position of this CanvasItem, relative to the parent.
	*/
	Vector2 get_position() const;

	/**
	* Sets the relative scale for this CanvasItem to @param new_scale.
	*/
	void set_scale(const Vector2 &new_scale);

	/**
	* Returns the scale of this CanvasItem, relative to the parent.
	*/
	Vector2 get_scale() const;

	/**
	* Sets the relative rotation (in degrees) for this CanvasItem to @param new_rotation.
	*/
	void set_rotation(const double new_rotation);

	/**
	* Returns the relative rotation of this CanvasItem in degrees, relative to the parent.
	*/
	double get_rotation() const;

	/**
	* Sets the global position for this CanvasItem to @param new_global_position.
	*/
	void set_global_position(const Vector2 &new_global_position);

	/**
	* Returns the global position of this CanvasItem.
	*/
	Vector2 get_global_position() const;

	/**
	* Sets the global scale for this CanvasItem to @param new_global_scale.
	*/
	void set_global_scale(const Vector2 &new_global_scale);

	/**
	* Returns the global scale of this CanvasItem.
	*/
	Vector2 get_global_scale() const;

	/**
	* Sets the global rotation (in degrees) for this CanvasItem to @param new_global_rotation.
	*/
	void set_global_rotation(const double new_global_rotation);

	/**
	* Returns the global rotation (in degrees) of this CanvasItem.
	*/
	double get_global_rotation() const;

	/**
	* Sets the relative transform (position, scale, and rotation) for this CanvasItem to @param new_transform.
	*/
	void set_transform(const Transform2D &new_transform);

	/**
	* Returns the relative transform (position, scale, and rotation) of this CanvasItem.
	*/
	Transform2D get_transform() const;

	/**
	* Sets the global transform (position, scale, and rotation) for this CanvasItem to @param new_global_transform.
	*/
	void set_global_transform(const Transform2D &new_global_transform);

	/**
	* Returns the global transform (position, scale, and rotation) of this CanvasItem.
	*/
	Transform2D get_global_transform() const;

	/**
	* Sets the modulate (tint) for this CanvasItem, relative to the parent.
	*/
	void set_modulate(const Color &new_modulate);

	/**
	* Returns the modulate (tint) of this CanvasItem, relative to the parent.
	*/
	Color get_modulate() const;

	/**
	* Returns the global modulation (tint) of this CanvasItem.
	*/
	Color get_absolute_modulate() const;

	/**
	* Sets the blending mode for this CanvasItem to @param new_blend_mode that is used for future draw operations. See SDL_BlendMode.
	*/
	void set_blend_mode(const SDL_BlendMode new_blend_mode);

	/**
	* Returns the blending mode of this CanvasItem that is used for future draw operations. See SDL_BlendMode.
	*/
	SDL_BlendMode get_blend_mode() const;

	/**
	* Hides the CanvasItem and its children.
	*/
	void hide();

	/**
	* Shows the CanvasItem and its children.
	*/
	void show();

	/**
	* Return true if the CanvasItem is visible, otherwise false. See also is_visible_in_tree.
	* Note: This only takes into account this CanvasItem's visiblity.
	*/
	bool is_visible() const;

	/**
	* Returns true if the CanvasItem and its parent are visible, otherwise false. See also is_visible.
	*/
	bool is_visible_in_tree() const;

	/**
	* Returns true if the CanvasItem is visible inside the viewport, otherwise false.
	*/
	bool is_visible_inside_viewport() const;

	void draw_texture(const std::shared_ptr<Texture2D> &texture, const Transform2D &texture_transform = Transform2D::IDENTITY, const Color &modulation = Color::WHITE) const;
	void draw_texture_rect(const std::shared_ptr<Texture2D> &texture, const Rect2i &region, const Transform2D &texture_transform = Transform2D::IDENTITY, const Color &modulation = Color::WHITE) const;
	void draw_line(const Vector2 &start, const Vector2 &end, const Color &modulation) const;
	void draw_rect(const Rect2 &rect, const Color &modulation) const;
};

}
