/*  This file is part of the Toof Engine. */
/** @file node2d.hpp */
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
	* @brief Sets the scale of this Node2D to @b new_scale.
	*/
	void set_scale(const Vector2f &new_scale);

	/**
	* @brief Returns the scale of this Node2D, relative to the parent.
	*/
	constexpr const Vector2f &get_scale() const {
		return transform.scale;
	}

	/**
	* @brief Sets the rotation of this Node2D to @b new_rotation.
	*/
	void set_rotation(const Angle new_rotation);

	/**
	* @brief Returns the rotation of this Node2D, relative to the parent.
	*/
	constexpr Angle get_rotation() const {
		return transform.rotation;
	}

	/**
	* @brief Sets the position of this Node2D to @b position.
	*/
	void set_position(const Vector2f &position);

	/**
	* @brief Returns the position of this Node2D, relative to the parent.
	*/
	constexpr const Vector2f &get_position() const {
		return transform.origin;
	}

	/**
	* @brief Sets the global position for this Node2D to @b new_global_position.
	*/
	void set_global_position(const Vector2f &new_global_position);

	/**
	* @brief Returns the global position of this Node2D.
	*/
	const Vector2f get_global_position() const;

	/**
	* @brief Sets the global scale of this Node2D to @b new_global_scale.
	*/
	void set_global_scale(const Vector2f &new_global_scale);

	/**
	* @brief Returns the global scale of this Node2D.
	*/
	const Vector2f get_global_scale() const;

	/**
	* @brief Sets the global rotation of this Node2D to @b new_global_rotation.
	*/
	void set_global_rotation(const Angle new_global_rotation);

	/**
	* @brief Returns the global rotation of this Node2D.
	*/
	Angle get_global_rotation() const;

	/**
	* @brief Sets the relative transform of this Node2D to @b new_transform.
	*/
	void set_transform(const Transform2D &new_transform);

	/**
	* @brief Returns the relative transform of this Node2D.
	*/
	Transform2D get_transform() const override;

	/**
	* @brief Sets the global transform of this Node2D to @b new_global_transform.
	*/
	void set_global_transform(const Transform2D &new_global_transform);
};

}
