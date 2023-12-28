#pragma once

#include <types/vector2.hpp>

#include <SDL_video.h>
#include <SDL_render.h>
#include <SDL_events.h>

namespace sdl {

class RenderingServer;
class Window;

class Viewport {

private:
  bool vsync;

  Window *window;
  SDL_Renderer *renderer;

public:
  Viewport();
  ~Viewport();

  void create(Window *from_window);

  Vector2i get_viewport_size() const;

  Window *get_window() const;
  SDL_Renderer *get_renderer() const;

  void set_vsync_enabled(const bool vsync_enabled);
  bool is_vsync_enabled() const;
};

}