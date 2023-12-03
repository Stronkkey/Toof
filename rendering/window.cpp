#include <rendering/window.hpp>

#include <iostream>

using namespace sdl;

Window::Window(const Rect2i &rect, const std::string &title) {
  success = true;
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    fail("Couldn't initialize SDL: %s", SDL_LOG_CATEGORY_APPLICATION);

  if (!(IMG_Init(IMG_INIT_PNG)))
    fail("Couldn't initialize SDL_Image: %s", SDL_LOG_CATEGORY_APPLICATION);

  if (rect.get_position() == Vector2i::ZERO)
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, rect.w, rect.h, SDL_WINDOW_RESIZABLE);
  else
    window = SDL_CreateWindow(title.c_str(), rect.x, rect.y, rect.w, rect.h, SDL_WINDOW_RESIZABLE);

  if (window == NULL)
    fail("Couldn't create window: %s", SDL_LOG_CATEGORY_APPLICATION);
 
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  rendering_server = new RenderingServer(renderer);
}

Window::~Window() {
  if (renderer)
    SDL_DestroyRenderer(renderer);
  if (window)
    SDL_DestroyWindow(window);

  delete rendering_server;
  SDL_Quit();
}

void Window::fail(const std::string &error_message, const SDL_LogCategory log_category) {
  std::cout << error_message << std::endl;
  SDL_LogError(log_category, error_message.c_str(), SDL_GetError());
  success = false;
}

bool Window::intialized_successfully() const {
  return success;
}

void Window::render() {
  SDL_RenderClear(renderer);
  rendering_server->render();
  SDL_RenderPresent(renderer);
}