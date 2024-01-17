#pragma once

#include <SDL_events.h>

#include <string>

#include <boost/signals2.hpp>

namespace sdl {

struct Rect2i;
class Item;
class Window;
class RenderingServer;
class Viewport;
#ifdef B2_INCLUDED
class PhysicsServer2D;
#endif

class Tree {

private:
	bool running;
	double fixed_frame_rate;
	double frame_rate;
	double render_delta_time;
	double loop_delta_time;
	#ifdef B2_INCLUDED
	double physics_frame_rate;
	double physics_delta_time;
	#endif

	double wait_for(const double time_seconds) const;
	void render_loop();
	void main_loop();
	void event_loop();
	#ifdef B2_INCLUDED
	void physics_loop();
	#endif

	boost::signals2::signal<void()> deferred_signals;
	std::vector<Item*> deferred_item_removal;

	Window *window;
	Viewport *viewport;
	RenderingServer *rendering_server;
	SDL_Event *event;
	Item *root;
	#ifdef B2_INCLUDED
	PhysicsServer2D *physics_server;
	#endif

	virtual void initialize();
	virtual void events();
	virtual void loop();
	virtual void render();
	virtual void physics();
	virtual void ended();

public:
	Tree();
	virtual ~Tree();

	//boost::signals2::signal<void()> loop_frame;
//	boost::signals2::signal<void()> render_frame;
	#ifdef B2_INCLUDED
	//boost::signals2::signal<void()> physics_frame;
	#endif

	Window *get_window() const;
	Viewport *get_viewport() const;
	RenderingServer *get_rendering_server() const;
	Item *get_root() const;
	SDL_Event *get_event() const;
	#ifdef B2_INCLUDED
	PhysicsServer2D *get_physics_server() const;
	#endif

	void start();
	void stop();

	void defer_callable(void(*callable)());
	void queue_free(Item *item);

	void set_frame_rate(const double new_frame_rate);
	double get_frame_rate() const;

	void set_fixed_frame_rate(const double new_fixed_frame_rate);
	double get_fixed_frame_rate() const;

	double get_render_delta_time() const;
	double get_loop_delta_time() const;

	#ifdef B2_INCLUDED
	void set_physics_frame_rate(const double new_physics_frame_rate);
	double get_physics_frame_rate() const;
	double get_physics_delta_time() const;
	#endif

	bool is_running();
};

}
