/*  This file is part of the Toof Engine. */
/** @file canvas_node.hpp */
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
#pragma once

#include <scene/main/node.hpp>

#include <core/math/transform2d.hpp>
#include <core/math/color.hpp>
#include <core/memory/optional.hpp>

#include <SDL_render.h>

namespace Toof {

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
		* @brief Notification received when redraw is called. This is called once during _ready
		*/
		NOTIFICATION_DRAW = 900,

		/**
		* @brief Notification received when the visibility of this CanvasNode changes.
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
	* @brief Queues this CanvasNode to update on the next render frame.
	* @details This can be safely called multiple times in one frame.
	*/
	void queue_redraw();

	/**
	* @brief Emitted when the renderingitem must redraw, after the related NOTIFICATION_DRAW notification, and before _draw is called.
	*/
	Signal<> draw;

	/**
	* @brief Emitted when becoming hidden.
	*/
	Signal<> hidden;

	/**
	* @brief Emitted when the visibility (hidden/visible) changes.
	*/
	Signal<> visibility_changed;

	/**
	* @brief Returns the uid used by the RenderingServer for this CanvasNode.
	*/
	constexpr uid get_canvas_item() const {
		return canvas_item;
	}

	/**
	* @brief Returns the transform of this CanvasNode, relative to its parent.
	*/
	virtual Transform2D get_transform() const;

	/**
	* @brief Returns the transform of this Node, relative to global space.
	*/
	virtual Transform2D get_global_transform() const;

	/**
	* @brief Hides this Node and its children.
	*/
	void hide();

	/**
	* @brief Shows this Node and its children.
	*/
	void show();

	/**
	* @brief Returns @b true if this CanvasNode is visible.
	* @see @b is_visible_in_tree.
	*/
	constexpr bool is_visible() const {
		return visible;
	}

	/**
	* @brief Sets the modulation (tint) for this CanvasNode.
	*/
	void set_modulation(const ColorV &modulation);

	/**
	* @brief Returns the modulate (tint) of this CanvasNode.
	*/
	const ColorV &get_modulation() const;

	/**
	* @brief Returns the global modulation of this CanvasNode.
	*/
	ColorV get_absolute_modulation() const;

	/**
	* @deprecated Use set_modulation instead.
	*/
	inline void set_modulate(const ColorV &new_modulate) {
		set_modulation(new_modulate);
	}

	/**
	* @deprecated Use get_modulation instead.
	*/
	inline const ColorV &get_modulate() const {
		return get_modulation();
	}

	/**
	* @deprecated Use get_absolute_modulation.
	*/
	inline const ColorV get_absolute_modulate() const {
		return get_absolute_modulation();
	}

	/**
	* @brief Sets the blending mode for this CanvasNode.
	* @see @b SDL_BlendMode.
	*/
	void set_blend_mode(SDL_BlendMode new_blend_mode);

	/**
	* @brief Returns the blending mode of this CanvasNode.
	* @see @b SDL_BlendMode.
	*/
	constexpr SDL_BlendMode get_blend_mode() const {
		return blend_mode;
	}

	/**
	* @brief Sets the scaling mode for this CanvasNode.
	* @see @b SDL_ScaleMode.
	*/
	void set_scale_mode(SDL_ScaleMode scaling_mode);

	/**
	* @brief Returns the scaling mode of this CanvasNode.
	* @see @b SDL_ScaleMode.
	*/
	constexpr SDL_ScaleMode get_scale_mode() const {
		return scale_mode;
	}

	/**
	* @brief Returns the Z index of this CanvasNode.
	* @see @b RenderingServer::canvas_item_get_zindex.
	*/
	constexpr int get_zindex() const {
		return zindex;
	}

	/**
	* @brief Sets the Z index of this CanvasNode.
	* @see @b RenderingServer::canvas_item_set_zindex.
	*/
	void set_zindex(int zindex);

	/**
	* @brief Returns the absolute Z index of this CanvasNode.
	* @see @b RenderingServer::canvas_item_get_absolute_zindex.
	*/
	int get_absolute_zindex() const;

	/**
	* @brief Sets the zindex relative.
	* @see @b RenderingServer::canvas_item_set_zindex.
	*/
	void set_zindex_relative(const bool zindex_relative);

	/**
	* @brief Returns @b true if zindex is relative.
	* @see @b RenderingServer::canvas_item_is_zindex_relative.
	*/
	constexpr bool get_zindex_relative() const {
		return zindex_relative;
	}

	/**
	* @brief Returns @b true if the CanvasNode and its parent are visible.
	* @see @b is_visible.
	*/
	bool is_visible_in_tree() const;

	/**
	* @brief Returns @b true if the CanvasNode is visible inside the viewport and is inside the SceneTree.
	*/
	bool is_visible_inside_viewport() const;

	/**
	* @brief Draws the texture using the RenderingServer.
	* @see @b RenderingServer::canvas_item_add_texture.
	*/
	void draw_texture(uid texture_uid, const Transform2D &texture_transform = Transform2D::IDENTITY, const ColorV &modulation = ColorV::WHITE()) const;

	/**
	* @brief Draws the texture in the specified @b region using RenderingServer.
	* @see @b RenderingServer::canvas_item_add_texture_region.
	*/
	void draw_texture_rect(uid texture_uid, const Rect2i &region, const Transform2D &texture_transform = Transform2D::IDENTITY, const ColorV &modulation = ColorV::WHITE()) const;
	
	/**
	* @brief Draws a colored line beginning from @b start to @b end with the color of @b modulation using the RenderingServer.
	* @see @b RenderingServer::canvas_item_add_line.
	*/
	void draw_line(const Vector2f &start, const Vector2f &end, const ColorV &modulation = ColorV::WHITE()) const;

	/**
	* @brief Draws multiple lines with the modulation of @b modulation using the RenderingServer.
	* @see @b RenderingServer::canvas_item_add_lines.
	*/
	void draw_lines(const std::vector<SDL_FPoint> &points, const ColorV &modulation = ColorV::WHITE()) const;

	/**
	* @brief Draws the Rect2 with the color @b modulation using the RenderingServer.
	* @see @b RenderingServer::canvas_item_add_rect.
	*/
	void draw_rect(const Rect2f &rect, const ColorV &modulation = ColorV::WHITE()) const;

	/**
	* @brief Draws multiple rectangle with the color @b modulation using the RenderingServer.
	* @see @b RenderingServer::canvas_item_add_rects.
	*/
	void draw_rects(const std::vector<SDL_FRect> &rects, const ColorV &modulation = ColorV::WHITE()) const;
};

}

