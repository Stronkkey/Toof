#include <items/tree.hpp>
#include <items/item.hpp>

#include <SDL_timer.h>

using namespace sdl;

Tree::Tree() {
  frame_rate = 60.0;
  root = new Item;
  window = new sdl::Window(get_window_rect(), get_window_title());
  rendering_server = window->rendering_server;
  root->set_tree(this);
  running = false;
}

Tree::~Tree() {
  root->free();
  delete window;
}

void Tree::events() {
  SDL_PollEvent(event);
  if (event->type == SDL_QUIT)
    stop();

  root->propagate_event(event);
}

void Tree::render(double delta) {
  root->propagate_render(delta);
  rendering_server->render();
}

void Tree::loop() {
  root->propagate_loop();
}

void Tree::initialize() {
}

void Tree::ended() {
}

void Tree::start() {
  if (!window->intialized_successfully() || running)
    return;

  running = true;
  event = new SDL_Event;
  initialize();

  uint64_t now = SDL_GetPerformanceCounter();
  uint64_t last = 0;

  while (running) {
    last = now;
    now = SDL_GetPerformanceCounter();
    double delta = (double(now - last) * 1000) / SDL_GetPerformanceFrequency();
    SDL_Delay(1000/frame_rate);

    events();
    loop();
    render(delta);
  }

  ended();
}

void Tree::stop() {
  running = false;
}

Window *Tree::get_window() const {
  return window;
}

Item *Tree::get_root() const {
  return root;
}

void Tree::set_root(Item *new_root) {
  root = new_root;
}

SDL_Event *Tree::get_event() const {
  return event;
}
