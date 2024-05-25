/*  This file is part of the Toof Engine. */
/** @file sprite2d.hpp */
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

#include <scene/2d/node2d.hpp>

namespace Toof {

class Texture2D;

class Sprite2D : public Node2D {
private:
	std::shared_ptr<Texture2D> texture;

	Rect2i texture_region;
	Transform2D texture_transform;
	SDL_RendererFlip flip;
	bool centered;

	Transform2D _get_placement_texture_transform() const;
	void _draw_full_texture() const;
	void _draw_rect_texture() const;
	void _draw_texture() const;
	void _notification(const int what) override;
public:
	Sprite2D();
	~Sprite2D() = default;

	Signal<> texture_changed;

	void set_texture(const std::shared_ptr<Texture2D> &new_texture);
	constexpr const std::shared_ptr<Texture2D> &get_texture() const {
		return texture;
	}

	void set_texture_region(const Rect2i &new_texture_region);
	constexpr const Rect2i &get_texture_region() const {
		return texture_region;
	}

	void set_offset(const Vector2f &new_offset);
	constexpr const Vector2f &get_offset() const {
		return texture_transform.origin;
	}

	void set_texture_rotation(const Angle new_rotation);
	constexpr Angle get_texture_rotation() const {
		return texture_transform.rotation;
	}

	void set_texture_scale(const Vector2f &new_texture_scale);
	constexpr const Vector2f &get_texture_scale() const {
		return texture_transform.scale;
	}

	void set_texture_transform(const Transform2D &new_texture_transform);
	constexpr const Transform2D &get_texture_transform() const {
		return texture_transform;
	}

	void set_flip(const SDL_RendererFlip new_flip);
	constexpr SDL_RendererFlip get_flip() const {
		return flip;
	}

	void set_centered(const bool new_centered);
	constexpr bool is_centered() const {
		return centered;
	}
};

}
