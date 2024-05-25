/*  This file is part of the Toof Engine. */
/** @file drawing_item.hpp */
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

#include <core/math/rect2.hpp>
#include <core/math/color.hpp>
#include <core/math/transform2d.hpp>

#include <SDL_render.h>

#include <memory>
#include <vector>

namespace Toof {

struct __CanvasItem__;
class Viewport;

enum DrawingItemType {
	DRAWING_ITEM_TYPE_NONE
};

struct __Texture_Ref__;

struct __DrawingItem__ {
	void draw(const std::shared_ptr<__CanvasItem__> &canvas_item, const Viewport *viewport);
	Rect2f get_draw_rect(const std::shared_ptr<__CanvasItem__> &canvas_item) const;

	virtual void _draw(const std::shared_ptr<__CanvasItem__> &canvas_item, const Viewport *viewport);
	virtual Rect2f _get_draw_rect(const std::shared_ptr<__CanvasItem__> &canvas_item) const;
};

struct __TextureDrawingItem__: public __DrawingItem__ {
	std::weak_ptr<__Texture_Ref__> texture;

	ColorV texture_modulate;
	bool use_region;
	SDL_RendererFlip flip;
	Rect2i src_region;
	Transform2D transform;

	void _draw(const std::shared_ptr<__CanvasItem__> &canvas_item, const Viewport *viewport) override;
	Rect2f _get_draw_rect(const std::shared_ptr<__CanvasItem__> &canvas_item) const override;
};

struct __RectDrawingItem__: public __DrawingItem__ {
	SDL_FRect rectangle;
	ColorV modulate;

	void _draw(const std::shared_ptr<__CanvasItem__> &canvas_item,const Viewport *viewport) override;

	Rect2f _get_draw_rect(const std::shared_ptr<__CanvasItem__> &canvas_item) const override;
};

struct __RectsDrawingItem__: public __DrawingItem__ {
	std::vector<SDL_FRect> rectangles;
	ColorV modulate;

	void _draw(const std::shared_ptr<__CanvasItem__> &canvas_item,const Viewport *viewport) override;
	
	Rect2f _get_draw_rect(const std::shared_ptr<__CanvasItem__> &canvas_item) const override;
};

struct __LineDrawingItem__: public __DrawingItem__ {
	SDL_FPoint start_point;
	SDL_FPoint end_point;
	ColorV modulate;

	void _draw(const std::shared_ptr<__CanvasItem__> &canvas_item,const Viewport *viewport) override;

	Rect2f _get_draw_rect(const std::shared_ptr<__CanvasItem__> &canvas_item) const override;
};

struct __LinesDrawingItem__: public __DrawingItem__ {
	std::vector<SDL_FPoint> points;
	ColorV modulate;

	void _draw(const std::shared_ptr<__CanvasItem__> &canvas_item,const Viewport *viewport) override;
	
	Rect2f _get_draw_rect(const std::shared_ptr<__CanvasItem__> &canvas_item) const override;
};

}
