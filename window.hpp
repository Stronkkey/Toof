#include <SDL.h>
#include <string>

#include "rect2.hpp"

namespace sdl {

class Window {
  
private:
  bool success;

  void fail(const std::string &error_message, const SDL_LogCategory category = SDL_LOG_CATEGORY_APPLICATION);

public:
  Window(const Rect2i &size, const std::string &title = "Default");
  ~Window();

  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Surface *surface;
  SDL_Event event;

  void poll_event();
  
};
};
