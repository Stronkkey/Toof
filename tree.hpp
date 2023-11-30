#ifndef TREE
#define TREE

#include "items/item.hpp"
#include "window.hpp"

#include <SDL_events.h>

namespace sdl {

class Tree {

protected:
  bool running;
  sdl::Window *window;
  sdl::RenderingServer *rendering_server;

  SDL_Event *event;
  Item *root;

  virtual void initialize();
  virtual void events();
  virtual void loop();
  virtual void render();
  virtual void ended();

  virtual void intialized() {}
  virtual void handle_events() { if (event->type == SDL_QUIT) stop(); }
  virtual void handle_loop() {}
  virtual void handle_render() {}
  virtual void on_ended() {}

  virtual Rect2i get_window_rect() const { return Rect2i(0, 0, 340, 240); }
  virtual std::string get_window_title() const { return "SDL example"; }

public:
  Tree();
  ~Tree();

  Window *get_window() const;

  Item *get_root() const;
  void set_root(Item *new_root);

  void start();
  void stop();

  bool is_running();
};

}

#endif // !TREE
