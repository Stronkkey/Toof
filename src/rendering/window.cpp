#include "window.hpp"
#include <iostream>

using namespace sdl;

Window::Window(Vector2i size) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
    success = false;
  }

  if (SDL_CreateWindowAndRenderer(size.x, size.y, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
    success = false;
  }
}

Window::~Window() {
}

void Window::poll_event() {
  while (true) {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
      break;

    std::cout << event.type;
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }
  
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
