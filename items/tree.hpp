#pragma once

#include <SDL_events.h>

#include <functional>
#include <string>

namespace sdl {

struct Rect2i;
class Item;
class Window;
class RenderingServer;
class Viewport;

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
  Window *window;
  Viewport *viewport;
  RenderingServer *rendering_server;
  SDL_Event *event;
  Item *root;

  virtual void initialize();
  virtual void events();
  virtual void loop();
  virtual void render();
  virtual void ended();

public:
  Tree();
  virtual ~Tree();

  Window *get_window() const;
  Viewport *get_viewport() const;
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
