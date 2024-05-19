#include <servers/rendering/viewport.hpp>
#include <servers/rendering/window.hpp>
#include <servers/rendering_server.hpp>

using namespace Toof;

Viewport::Viewport(): vsync(true), window(nullptr), canvas_transform(Transform2D::IDENTITY) {
}

void Viewport::create(Window *from_window) {
	window = from_window;
	renderer = SDL_CreateRenderer(window->get_window(), -1, SDL_RENDERER_ACCELERATED);
	set_vsync_enabled(vsync);
}

Vector2i Viewport::get_viewport_size() const {
	int x;
	int y;
	SDL_GetRendererOutputSize(renderer, &x, &y);
	return Vector2i((integer)x, (integer)y);
}

void Viewport::set_vsync_enabled(const bool vsync_enabled) {
	vsync = vsync_enabled;
	SDL_RenderSetVSync(renderer, vsync_enabled);
}

void Viewport::set_canvas_transform(const Transform2D &new_canvas_transform) {
	canvas_transform = new_canvas_transform;
}
