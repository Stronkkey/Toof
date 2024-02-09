#pragma once

#include <core/math/rect2.hpp>
#include <core/math/color.hpp>
#include <core/math/transform2d.hpp>

#include <SDL_render.h>

#include <memory>
#include <vector>

namespace sdl {

struct CanvasItem;
struct Texture;
class Viewport;

enum DrawingItemType {
	DRAWING_ITEM_TYPE_NONE
};

struct DrawingItem {
	void draw(const std::shared_ptr<CanvasItem> &canvas_item, const Viewport *viewport);
	Rect2 get_draw_rect(const std::shared_ptr<CanvasItem> &canvas_item) const;

	virtual void _draw(const std::shared_ptr<CanvasItem> &canvas_item, const Viewport *viewport);
	virtual Rect2 _get_draw_rect(const std::shared_ptr<CanvasItem> &canvas_item) const;
};

struct TextureDrawingItem: public DrawingItem {
	std::weak_ptr<Texture> texture;

	Color texture_modulate;
	bool use_region;
	SDL_RendererFlip flip;
	Rect2i src_region;
	Transform2D transform;

	void _draw(const std::shared_ptr<CanvasItem> &canvas_item, const Viewport *viewport) override;
	Rect2 _get_draw_rect(const std::shared_ptr<CanvasItem> &canvas_item) const override;
};

struct RectDrawingItem: public DrawingItem {
	SDL_FRect rectangle;
	Color modulate;

	void _draw(const std::shared_ptr<CanvasItem> &canvas_item,const Viewport *viewport) override;

	Rect2 _get_draw_rect(const std::shared_ptr<CanvasItem> &canvas_item) const override;
};

struct RectsDrawingItem: public DrawingItem {
	std::vector<SDL_FRect> rectangles;
	Color modulate;

	void _draw(const std::shared_ptr<CanvasItem> &canvas_item,const Viewport *viewport) override;
	
	Rect2 _get_draw_rect(const std::shared_ptr<CanvasItem> &canvas_item) const override;
};

struct LineDrawingItem: public DrawingItem {
	SDL_FPoint start_point;
	SDL_FPoint end_point;
	Color modulate;

	void _draw(const std::shared_ptr<CanvasItem> &canvas_item,const Viewport *viewport) override;

	Rect2 _get_draw_rect(const std::shared_ptr<CanvasItem> &canvas_item) const override;
};

struct LinesDrawingItem: public DrawingItem {
	std::vector<SDL_FPoint> points;
	Color modulate;

	void _draw(const std::shared_ptr<CanvasItem> &canvas_item,const Viewport *viewport) override;
	
	Rect2 _get_draw_rect(const std::shared_ptr<CanvasItem> &canvas_item) const override;
};

}
