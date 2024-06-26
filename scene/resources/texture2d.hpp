/*  This file is part of the Toof Engine. */
/** @file texture2d.hpp */
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

#include <core/math/math_defs.hpp>
#include <core/math/transform2d.hpp>
#include <core/math/color.hpp>
#include <scene/resources/resource.hpp>

#include <SDL_render.h>

namespace Toof {

template<class>
struct Rect2;
typedef Rect2<integer> Rect2i;
class RenderingServer;

class Texture2D : public Resource {
private:
	RenderingServer *rendering_server;

	virtual Vector2i _get_size() const {
		return Vector2i();
	}

	virtual integer _get_width() const {
		return 0;
	}

	virtual integer _get_height() const {
		return 0;
	}

	virtual uid _get_uid() const {
		return 0;
	}

	virtual SDL_Texture *_get_texture() const {
		return nullptr;
	}

	virtual void _draw(const uid, const uid, const SDL_RendererFlip, const ColorV&, const Transform2D&) {
	}

	virtual void _draw_region(const uid, const uid, const Rect2i&, const SDL_RendererFlip, const ColorV&, const Transform2D&) {
	}

	virtual void _on_rendering_server_set() {
	}
protected:
	Texture2D();
public:
	~Texture2D() = default;

	inline void set_rendering_server(RenderingServer *rendering_server) {
		this->rendering_server = rendering_server;
		_on_rendering_server_set();
	}

	constexpr RenderingServer *get_rendering_server() {
		return rendering_server;
	}

	constexpr const RenderingServer *get_rendering_server() const {
		return rendering_server;
	}

	inline Vector2i get_size() const {
		return _get_size();
	}

	inline int get_width() const {
		return _get_width();
	}

	inline int get_height() const {
		return _get_height();
	}

	inline uid get_uid() const {
		return _get_uid();
	}

	inline SDL_Texture *get_texture() const {
		return _get_texture();
	}

	inline void draw(const uid texture_uid,
	    const uid canvas_item_uid,
	    const SDL_RendererFlip flip = SDL_FLIP_NONE,
	    const ColorV &modulate = ColorV::WHITE(),
	    const Transform2D &transform = Transform2D::IDENTITY)
		{
			_draw(texture_uid, canvas_item_uid, flip, modulate, transform);
		}

	inline void draw_region(const uid texture_uid,
	    const uid canvas_item_uid,
	    const Rect2i &src_region,
	    const SDL_RendererFlip flip = SDL_FLIP_NONE,
	    const ColorV &modulate = ColorV::WHITE(),
	    const Transform2D &transform = Transform2D::IDENTITY)
	{
		_draw_region(texture_uid, canvas_item_uid, src_region, flip, modulate, transform);
	}
};

}
