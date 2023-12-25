#pragma once

#include <types/rect2.hpp>

#include <SDL_events.h>

#include <functional>

namespace sdl {

class Item;
class Window;
class RenderingServer;

class Tree {

typedef std::function<void(void)> callback;

private:
  bool running;
  double fixed_frame_rate;
  double frame_rate;
  double render_delta_time;
  double loop_delta_time;

  void render_loop();
  void main_loop();
  void event_loop();

  std::vector<callback> deferred_callbacks;
  std::vector<Item*> deferred_item_removal;

protected:
  sdl::Window *window;
  sdl::RenderingServer *rendering_server;
  SDL_Event *event;
  Item *root;

  virtual void initialize();
  virtual void events();
  virtual void loop();
  virtual void render();
  virtual void ended();

  virtual Rect2i get_window_rect() const { return Rect2i(0, 0, 340, 240); }

  virtual std::string get_window_title() const { return "SDL example"; }

  virtual bool should_use_vsync() const { return true; }

public:
  Tree();
  virtual ~Tree();

  Window *get_window() const;
  RenderingServer *get_rendering_server() const;

  Item *get_root() const;

  SDL_Event *get_event() const;

  void start();
  void stop();

  void defer_callable(const callback &callable);
  void queue_free(Item *item);

  void set_frame_rate(const double new_frame_rate);
  double get_frame_rate() const;

  void set_fixed_frame_rate(const double new_fixed_frame_rate);
  double get_fixed_frame_rate() const;

  double get_render_delta_time() const;
  double get_loop_delta_time() const;

  bool is_running();
};

}
