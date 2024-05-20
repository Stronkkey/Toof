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
