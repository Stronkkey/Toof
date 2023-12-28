#include <rendering/viewport.hpp>
#include <rendering/rendering_server.hpp>
#include <rendering/window.hpp>

using namespace sdl;

Viewport::Viewport(): vsync(true), window(nullptr), canvas_transform(Transform2D::IDENTITY) {
}

Viewport::~Viewport() {
}

void Viewport::create(Window *from_window) {
  window = from_window;
  renderer = SDL_CreateRenderer(window->get_window(), -1, SDL_RENDERER_ACCELERATED);
  set_vsync_enabled(vsync);
}

Window *Viewport::get_window() const {
  return window;
}

SDL_Renderer *Viewport::get_renderer() const {
  return renderer;
}

Vector2i Viewport::get_viewport_size() const {
  int x;
  int y;
  SDL_GetRendererOutputSize(renderer, &x, &y);
  return Vector2i(x, y);
}

void Viewport::set_vsync_enabled(const bool vsync_enabled) {
  vsync = vsync_enabled;
  SDL_RenderSetVSync(renderer, vsync_enabled ? 1 : 0);
}

bool Viewport::is_vsync_enabled() const {
  return vsync;
}

void Viewport::set_canvas_transform(const Transform2D &new_canvas_transform) {
  canvas_transform = new_canvas_transform;
}

Transform2D Viewport::get_canvas_transform() const {
  return canvas_transform;
}