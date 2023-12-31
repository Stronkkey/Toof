#pragma once

#include <types/rect2.hpp>
#include <types/color.hpp>
#include <types/transform2d.hpp>

#include <SDL_render.h>

#include <memory>
#include <vector>

namespace sdl {

struct CanvasItem;
struct Texture;
class Viewport;

struct DrawingItem {
	std::shared_ptr<CanvasItem> canvas_item = std::shared_ptr<CanvasItem>();

	void draw(const Viewport *viewport);
	Rect2 get_draw_rect() const;

	virtual void _draw(const Viewport*) {}
	virtual Rect2 _get_draw_rect() const { return Rect2::EMPTY; }
};

struct TextureRectDrawingItem: public DrawingItem {
	std::shared_ptr<Texture> texture = std::shared_ptr<Texture>();

	Color texture_modulate;
	Rect2i src_region;
	Transform2D transform;
	SDL_RendererFlip flip;

	void _draw(const Viewport *viewport) override;
	void draw_texture(const Viewport *viewport,
		const SDL_Rect &src_region,
		const SDL_FRect &destination,
		const double rotation,
		const SDL_FPoint &center = SDL_FPoint());

	Rect2 _get_draw_rect() const override;
};

struct TextureDrawingItem: public DrawingItem {
	std::shared_ptr<Texture> texture = std::shared_ptr<Texture>();

	Color texture_modulate;
	Transform2D transform;
	SDL_RendererFlip flip;

	void _draw(const Viewport *viewport) override;
	void draw_texture(const Viewport *viewport,
		const SDL_Rect &src_region,
		const SDL_FRect &destination,
		const double rotation,
		const SDL_FPoint &center = SDL_FPoint());

	Rect2 _get_draw_rect() const override;
};

struct RectDrawingItem: public DrawingItem {
	SDL_FRect rectangle;
	Color modulate;

	void _draw(const Viewport *viewport) override;

	Rect2 _get_draw_rect() const override;
};

struct RectsDrawingItem: public DrawingItem {
	std::vector<SDL_FRect> rectangles;
	Color modulate;

	void _draw(const Viewport *viewport) override;
	
	Rect2 _get_draw_rect() const override;
};

struct LineDrawingItem: public DrawingItem {
	SDL_FPoint start_point;
	SDL_FPoint end_point;
	Color modulate;

	void _draw(const Viewport *viewport) override;

	Rect2 _get_draw_rect() const override;
};

struct LinesDrawingItem: public DrawingItem {
	std::vector<SDL_FPoint> points;
	Color modulate;

	void _draw(const Viewport *viewport) override;
	
	Rect2 _get_draw_rect() const override;
};

}
