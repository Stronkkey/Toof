#ifndef WINDOW_H
#define WINDOW_H

#include <rendering/rendering_server.hpp>
#include <types/rect2.hpp>

#include <SDL_events.h>
#include <SDL_log.h>

namespace sdl {

class Window {
  
private:
  bool success, vsync;

  void fail(const std::string &error_message, const SDL_LogCategory category = SDL_LOG_CATEGORY_APPLICATION);

public:
  Window(const Rect2i &size = Rect2i(0, 0, 320, 240), const std::string &title = "Default", const bool use_vsync = true);
  ~Window();

  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Surface *surface;
  SDL_Event event;
  RenderingServer *rendering_server;

  void render();

  bool intialized_successfully() const;
  bool is_vsync_enabled() const;
  int get_refresh_rate() const;
  Vector2i get_size() const;
};
};

#endif // !WINDOW_H
