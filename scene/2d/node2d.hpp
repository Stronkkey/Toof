#pragma once

#include <scene/main/node.hpp>

#include <core/math/transform2d.hpp>
#include <core/math/color.hpp>
#include <servers/rendering_server.hpp>

namespace sdl {

class Texture2D;
/** A 2D GameObject. Has a position, scale, and rotation.*/

class Node2D : public Node {

public:
	enum {
		NOTIFICATION_DRAW = 900 /** Notification received when redraw is called. This is called once during _ready.*/,
		NOTIFICATION_VISIBILITY_CHANGED /** Notification received when the visibility of the node2d changes.*/,
	};

private:
	Transform2D transform;
	uid canvas_item;
	Color modulate;
	SDL_BlendMode blend_mode;
	SDL_ScaleMode scale_mode;
	bool visible;
	bool zindex_relative;
	bool update_queued;
	int zindex;

	/**
	* Syncs the transform, modulate, blend_mode, scale_mode, zindex, and visible property with the RenderingServer.
	*/
	void update();

	void on_parent_changed(Node *new_parent);
	void ready();

protected:
	/**
	* @returns the RenderingServer from the tree.
	* @note attempting to dereference the pointer is undefined if the node is not inside a SceneTree.
	*/
	const std::unique_ptr<RenderingServer> &get_rendering_server() const;

	void _notification(const int what) override;
	/**
	* Called when the Node2D has been requested to redraw (after redraw is called or notification NOTIFICATION_DRAW is sent).
	*/
	virtual void _draw() const;

public:
	Node2D();
	~Node2D();

	/**
	* Queues this Node2D to update on the next render frame.
	* This can be safely called multiple times in one frame.
	*/
	void queue_redraw();

	/**
	* Emitted when the renderingitem must redraw, after the related NOTIFICATION_DRAW notification, and before _draw is called.
	*/
	boost::signals2::signal<void()> draw;

	/**
	* Emitted when becoming hidden.
	*/
	boost::signals2::signal<void()> hidden;

	/**
	* Emitted when the visibility (hidden/visible) changes.
	*/
	boost::signals2::signal<void()> visibility_changed;

	/**
	* @returns the CanvasItem uid used by the RenderingServer for this item.
	*/
	uid get_canvas_item() const;

	/**
	* Sets the relative position for this node2d to @param new_position.
	*/
	void set_position(const Vector2 &new_position);

	/**
	* @returns the position of this node2d, relative to the parent.
	*/
	const Vector2 &get_position() const;

	/**
	* Sets the relative scale for this node2d to @param new_scale.
	*/
	void set_scale(const Vector2 &new_scale);

	/**
	* @returns the scale of this node2d, relative to the parent.
	*/
	const Vector2 &get_scale() const;

	/**
	* Sets the relative rotation (in degrees) for this node2d to @param new_rotation.
	*/
	void set_rotation(const double new_rotation);

	/**
	* @returns the relative rotation of this node2d in degrees, relative to the parent.
	*/
	double get_rotation() const;

	/**
	* Sets the global position for this node2d to @param new_global_position.
	*/
	void set_global_position(const Vector2 &new_global_position);

	/**
	* @returns the global position of this node2d.
	*/
	const Vector2 get_global_position() const;

	/**
	* Sets the global scale for this node2d to @param new_global_scale.
	*/
	void set_global_scale(const Vector2 &new_global_scale);

	/**
	* @returns the global scale of this node2d.
	*/
	const Vector2 get_global_scale() const;

	/**
	* Sets the global rotation (in degrees) for this node2d to @param new_global_rotation.
	*/
	void set_global_rotation(const double new_global_rotation);

	/**
	* @returns the global rotation (in degrees) of this node2d.
	*/
	double get_global_rotation() const;

	/**
	* Sets the relative transform (position, scale, and rotation) for this node2d to @param new_transform.
	*/
	void set_transform(const Transform2D &new_transform);

	/**
	* @returns the relative transform (position, scale, and rotation) of this node2d.
	*/
	const Transform2D &get_transform() const;

	/**
	* Sets the global transform (position, scale, and rotation) for this node2d to @param new_global_transform.
	*/
	void set_global_transform(const Transform2D &new_global_transform);

	/**
	* @returns the global transform (position, scale, and rotation) of this node2d.
	*/
	const Transform2D get_global_transform() const;

	/**
	* Sets the modulate (tint) for this node2d, relative to the parent.
	*/
	void set_modulate(const Color &new_modulate);

	/**
	* @returns the modulate (tint) of this node2d, relative to the parent.
	*/
	const Color &get_modulate() const;

	/**
	* @returns the global modulation (tint) of this node2d.
	*/
	const Color get_absolute_modulate() const;

	/**
	* Sets the blending mode for this node2d to @param new_blend_mode that is used for future draw operations.
	* @see also SDL_BlendMode.
	*/
	void set_blend_mode(const SDL_BlendMode new_blend_mode);

	/**
	* @returns the blending mode of this node2d.
	* @see also SDL_BlendMode.
	*/
	SDL_BlendMode get_blend_mode() const;

	/**
	* Sets the scaling mode for this node2d to @param scaling_mode, used for future draw operations.
	* @see also SDL_ScaleMode.
	*/
	void set_scale_mode(const SDL_ScaleMode scaling_mode);

	/**
	* @returns the scaling mode of this node2d.
	* @see also SDL_ScaleMode.
	*/
	SDL_ScaleMode get_scale_mode() const;

	/**
	* Hides the node2d and its children.
	*/
	void hide();

	/**
	* Shows the node2d and its children.
	*/
	void show();

	/**
	* Return true if the node2d is visible, otherwise false.
	* @see also is_visible_in_tree.
	* @note this only takes into account this node2d's visiblity.
	*/
	bool is_visible() const;

	/**
	* @returns true if the node2d and its parent are visible, otherwise false.
	* @see also is_visible.
	*/
	bool is_visible_in_tree() const;

	/**
	* @returns true if the node2d is visible inside the viewport, otherwise false.
	*/
	bool is_visible_inside_viewport() const;

	/**
	* Sets the zindex of this node2d to @param zindex.
	* @see also RenderingServer::canvas_item_set_zindex.
	*/
	void set_zindex(const int zindex);

	/**
	* @returns the zindex of this node2d.
	* @see also RenderingServer::canvas_item_get_zindex.
	*/
	int get_zindex() const;

	/**
	* @returns the zindex of this item including its parents if zindex relative is on.
	* @see also RenderingServer::canvas_item_get_absolute_zindex.
	*/
	int get_absolute_zindex() const;

	/**
	* Sets the zindex relative to @param zindex_relative.
	* @see also RenderingServer::canvas_item_set_zindex.
	*/
	void set_zindex_relative(const bool zindex_relative);

	/**
	* @returns true if zindex is relative.
	* @see also RenderingServer::canvas_item_is_zindex_relative.
	*/
	bool get_zindex_relative() const;

	/**
	* Draws the @param texture on this node2d using the RenderingServer.
	* @see also RenderingServer::canvas_item_add_texture.
	*/
	void draw_texture(const std::shared_ptr<Texture2D> &texture, const Transform2D &texture_transform = Transform2D::IDENTITY, const Color &modulation = Color::WHITE) const;

	/**
	* Draws the @param texture in the specified @param region using RenderingServer.
	* @see also RenderingServer::canvas_item_add_texture_region.
	*/
	void draw_texture_rect(const std::shared_ptr<Texture2D> &texture, const Rect2i &region, const Transform2D &texture_transform = Transform2D::IDENTITY, const Color &modulation = Color::WHITE) const;
	
	/**
	* Draws a colored line beginning from @param start to @param end with the color @param modulation using the RenderingServer.
	* @see also RenderingServer::canvas_item_add_line.
	*/
	void draw_line(const Vector2 &start, const Vector2 &end, const Color &modulation = Color::WHITE) const;

	/**
	* Draws multiple lines with the color @param modulation using the RenderingServer.
	* @see also RenderingServer::canvas_item_add_lines.
	*/
	void draw_lines(const std::vector<SDL_FPoint> &points, const Color &modulation = Color::WHITE) const;

	/**
	* Draws a colored rectangle that is inside @param rect with color @param modulation.
	* @see also RenderingServer::canvas_item_add_rect.
	*/
	void draw_rect(const Rect2 &rect, const Color &modulation = Color::WHITE) const;

	/**
	* Draws multipled rectangle with the color @param modulation using the RenderingServer.
	* @see also RenderingServer::canvas_item_add_rects.
	*/
	void draw_rects(const std::vector<SDL_FRect> &rects, const Color &modulation = Color::WHITE) const;
};

}
