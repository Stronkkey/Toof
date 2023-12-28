#include <rendering/viewport.hpp>
#include <rendering/rendering_server.hpp>
#include <rendering/window.hpp>

using namespace sdl;

Viewport::Viewport(): vsync(true), window(nullptr) {
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