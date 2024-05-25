/*  This file is part of the Toof Engine. */
/** @file canvas_item.hpp */
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

#include <core/math/transform2d.hpp>
#include <core/math/color.hpp>

#include <vector>
#include <memory>

#include <SDL_render.h>

namespace Toof {

struct __DrawingItem__;

struct __CanvasItem__ {
	Transform2D transform = Transform2D::IDENTITY;
	Transform2D global_transform = Transform2D::IDENTITY;
	ColorV modulate = ColorV::WHITE();
	ColorV global_modulate = ColorV::WHITE();
	bool visible = true;
	bool zindex_relative = true;
	bool global_visible = true;
	int zindex = true;
	int global_zindex = 0;

	SDL_BlendMode blend_mode = SDL_BLENDMODE_BLEND;
	SDL_ScaleMode scale_mode = SDL_ScaleModeLinear;

	std::weak_ptr<__CanvasItem__> parent;
	std::vector<std::unique_ptr<__DrawingItem__>> drawing_items;

	void set_global_transform();
	void set_global_modulate();
	void set_global_visible();
	void set_global_zindex();

	const Transform2D &get_global_transform();
	const ColorV &get_global_modulate();
	bool is_globally_visible();
	int get_global_zindex();
};

}
