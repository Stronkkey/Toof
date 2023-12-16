#include <items/tree.hpp>
#include <items/item.hpp>

#include <SDL_timer.h>

#include <thread>
#include <chrono>

using namespace sdl;

Tree::Tree(): fixed_frame_rate(60.0),
  frame_rate(60.0) {
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

void Tree::loop(double delta) {
  root->propagate_loop(delta);
}

void Tree::initialize() {
}

void Tree::ended() {
}

void Tree::main_loop() {
  uint64_t now = SDL_GetPerformanceCounter();
  uint64_t last = 0;

  while (running) {
    last = now;
    now = SDL_GetPerformanceCounter();
    double delta = (double(now - last)) / SDL_GetPerformanceFrequency();

    auto wait_time = std::chrono::duration<double>(1 / fixed_frame_rate);
    std::this_thread::sleep_for(wait_time);

    if (event_process_type == EVENT_PROCESS_TYPE_FIXED || event_process_type == EVENT_PROCESS_TYPE_FIXED_RENDER)
      events();

    loop(delta);
  }
}

void Tree::render_loop() {
  uint64_t now = SDL_GetPerformanceCounter();
  uint64_t last = 0;

  while (running) {
    last = now;
    now = SDL_GetPerformanceCounter();
    double delta = (double(now - last)) / SDL_GetPerformanceFrequency();

    auto wait_time = std::chrono::duration<double>(1 / frame_rate);
    std::this_thread::sleep_for(wait_time);
    
    if (event_process_type == EVENT_PROCESS_TYPE_RENDER || event_process_type == EVENT_PROCESS_TYPE_FIXED_RENDER)
      events();

    render(delta);
  }
}

void Tree::start() {
  if (!window->intialized_successfully() || running)
    return;

  running = true;
  event = new SDL_Event;
  initialize();

  std::thread main_loop_thread = std::thread(&Tree::main_loop, this);
  render_loop();

  main_loop_thread.join();
}

void Tree::stop() {
  if (running) {
    running = false;
    ended();
  }
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

void Tree::set_frame_rate(const double new_frame_rate) {
  frame_rate = new_frame_rate;
}

double Tree::get_frame_rate() const {
  return frame_rate;
}

void Tree::set_fixed_frame_rate(const double new_fixed_frame_rate) {
  fixed_frame_rate = new_fixed_frame_rate;
}

double Tree::get_fixed_frame_rate() const {
  return fixed_frame_rate;
}
