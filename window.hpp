#include <SDL.h>
#include "vector2.hpp"

namespace sdl {

class Window {
  
private:
  bool success;

public:
  Window(Vector2i size);
  ~Window();

  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Surface *surface;
  SDL_Event event;

  void poll_event();
  
};
};
