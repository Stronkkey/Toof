#pragma once

#include <scene/main/node.hpp>

#include <core/math/transform2d.hpp>
#include <core/math/color.hpp>
#include <core/memory/optional.hpp>

#include <SDL_render.h>

namespace sdl {

class RenderingServer;

template<class>
class Rect2;

using Rect2i = Rect2<integer>;
using Rect2f = Rect2<real>;

/**
* @brief Abstract class for Nodes in 2D space.
*/
class CanvasNode : public Node {
public:
	enum {
		/**
		* Notification received when redraw is called. This is called once during _ready
		*/
		NOTIFICATION_DRAW = 900,

		/**
		* Notification received when the visibility of this CanvasNode changes.
		*/
		NOTIFICATION_VISIBILITY_CHANGED,
	};
private:
	uid canvas_item;
	ColorV modulation;
	SDL_BlendMode blend_mode;
	SDL_ScaleMode scale_mode;

	/**
	* @brief the visiblity of this and its child CanvasNodes.
	*/
	bool visible;

	/**
	* @brief If true, this CanvasNode's Z index is relative to its parent's Z index.
	*/
	bool zindex_relative;
	bool update_queued;

	/**
	* @brief the Rendering order of this CanvasNode.
	* A CanvasItem with a Z index will be rendered over a CanvasItem with a lower Z index.
	*/
	int zindex;

	/**
	* Syncs the transform, modulate, blend_mode, scale_mode, zindex, and visible property with the RenderingServer.
	*/
	void _update();
	
	void _on_parent_changed(Node *parent);
	void _on_tree_enter();
	void _on_tree_exit();
protected:
	/**
	* @returns the RenderingServer from the tree or nullptr if the Node is not inside a.
	* @note dereferencing the pointer is only allowed if is_inside_tree returns true.
	*/
	Optional<RenderingServer*> get_rendering_server() const;

	void _notification(int what) override;

	/**
	* Called when the CanvasNode has been requested to redraw (after queue_redraw is called or notification NOTIFICATION_DRAW is sent).
	*/
	virtual void _draw() const;
public:
	CanvasNode();
	~CanvasNode() = default;

	/**
	* Queues this CanvasNode to update on the next render frame.
	* This can be safely called multiple times in one frame.
	*/
	void queue_redraw();

	/**
	* Emitted when the renderingitem must redraw, after the related NOTIFICATION_DRAW notification, and before _draw is called.
	*/
	Signal<> draw;

	/**
	* Emitted when becoming hidden.
	*/
	Signal<> hidden;

	/**
	* Emitted when the visibility (hidden/visible) changes.
	*/
	Signal<> visibility_changed;

	/**
	* @returns the uid used by the RenderingServer for this CanvasNode.
	*/
	constexpr uid get_canvas_item() const {
		return canvas_item;
	}

	/**
	* @returns the transform of this Node, relative to its parent.
	*/
	virtual Transform2D get_transform() const;

	/**
	* @returns the transform of this Node, relative to global space.
	*/
	virtual Transform2D get_global_transform() const;

	/**
	* Hides this Node and its children.
	*/
	void hide();

	/**
	* Shows this Node and its children.
	*/
	void show();

	/**
	* @returns the visiblity of this Node.
	* @see also is_visible_in_tree.
	*/
	constexpr bool is_visible() const {
		return visible;
	}

	/**
	* Sets the modulation (tint) for this node2d, in relativity to the parent.
	*/
	void set_modulation(const ColorV &modulation);

	/**
	* @returns the modulate (tint) of this node2d, in relativity to the parent.
	*/
	const ColorV &get_modulation() const;

	/**
	* @returns the modulation of this node2d, in relativity to global .
	*/
	ColorV get_absolute_modulation() const;

	/**
	* @deprecated use set_modulation instead.
	*/
	inline void set_modulate(const ColorV &new_modulate) {
		set_modulation(new_modulate);
	}

	/**
	* @deprecated use get_modulation instead.
	*/
	inline const ColorV &get_modulate() const {
		return get_modulation();
	}

	/**
	* @deprecated use get_absolute_modulation.
	*/
	inline const ColorV get_absolute_modulate() const {
		return get_absolute_modulation();
	}

	/**
	* Sets the blending mode for this node2d to @param new_blend_mode that is used for future draw operations.
	* @see also SDL_BlendMode.
	*/
	void set_blend_mode(SDL_BlendMode new_blend_mode);

	/**
	* @returns the blending mode of this node2d.
	* @see also SDL_BlendMode.
	*/
	constexpr SDL_BlendMode get_blend_mode() const {
		return blend_mode;
	}

	/**
	* Sets the scaling mode for this node2d to @param scaling_mode, used for future draw operations.
	* @see also SDL_ScaleMode.
	*/
	void set_scale_mode(SDL_ScaleMode scaling_mode);

	/**
	* @returns the scaling mode of this node2d.
	* @see also SDL_ScaleMode.
	*/
	constexpr SDL_ScaleMode get_scale_mode() const {
		return scale_mode;
	}

	/**
	* @returns the zindex of this Node.
	* @see also RenderingServer::canvas_item_get_zindex.
	*/
	constexpr int get_zindex() const {
		return zindex;
	}

	/**
	* Sets the zindex of this node2d to @param zindex.
	* @see also RenderingServer::canvas_item_set_zindex.
	*/
	void set_zindex(int zindex);

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
	constexpr bool get_zindex_relative() const {
		return zindex_relative;
	}

	/**
	* @returns true if the node2d and its parent are visible, otherwise false.
	* @see also is_visible.
	*/
	bool is_visible_in_tree() const;

	/**
	* @returns true if the CanvasNode is visible inside the viewport and the Node is inside the SceneTree.
	*/
	bool is_visible_inside_viewport() const;

	/**
	* Draws the @param texture on this node2d using the RenderingServer.
	* @see also RenderingServer::canvas_item_add_texture.
	*/
	void draw_texture(uid texture_uid, const Transform2D &texture_transform = Transform2D::IDENTITY, const ColorV &modulation = ColorV::WHITE()) const;

	/**
	* Draws the @param texture in the specified @param region using RenderingServer.
	* @see also RenderingServer::canvas_item_add_texture_region.
	*/
	void draw_texture_rect(uid texture_uid, const Rect2i &region, const Transform2D &texture_transform = Transform2D::IDENTITY, const ColorV &modulation = ColorV::WHITE()) const;
	
	/**
	* Draws a colored line beginning from @param start to @param end with the color @param modulation using the RenderingServer.
	* @see also RenderingServer::canvas_item_add_line.
	*/
	void draw_line(const Vector2f &start, const Vector2f &end, const ColorV &modulation = ColorV::WHITE()) const;

	/**
	* Draws multiple lines with the color @param modulation using the RenderingServer.
	* @see also RenderingServer::canvas_item_add_lines.
	*/
	void draw_lines(const std::vector<SDL_FPoint> &points, const ColorV &modulation = ColorV::WHITE()) const;

	/**
	* Draws a colored rectangle that is inside @param rect with color @param modulation.
	* @see also RenderingServer::canvas_item_add_rect.
	*/
	void draw_rect(const Rect2f &rect, const ColorV &modulation = ColorV::WHITE()) const;

	/**
	* Draws multipled rectangle with the color @param modulation using the RenderingServer.
	* @see also RenderingServer::canvas_item_add_rects.
	*/
	void draw_rects(const std::vector<SDL_FRect> &rects, const ColorV &modulation = ColorV::WHITE()) const;
};

}

