#pragma once

#include <SDL_events.h>

#include <string>

#include <boost/signals2.hpp>

namespace sdl {

struct Rect2i;
class Node;
class Window;
class RenderingServer;
class Viewport;
#ifdef B2_INCLUDED
class PhysicsServer2D;
#endif

class SceneTree {

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

	std::vector<Node*> deferred_item_removal;

	Window *window = nullptr;
	Viewport *viewport = nullptr;
	RenderingServer *rendering_server = nullptr;
	SDL_Event *event = nullptr;
	Node *root = nullptr;
	#ifdef B2_INCLUDED
	PhysicsServer2D *physics_server = nullptr;
	#endif

	virtual void _initialize();
	virtual void _ended();
	void events();
	void loop();
	void render();
	void physics();

public:
	SceneTree();
	virtual ~SceneTree();

	boost::signals2::signal<void()> loop_frame;
	boost::signals2::signal<void()> render_frame;
	boost::signals2::signal<void()> deferred_signals;

	#ifdef B2_INCLUDED
	boost::signals2::signal<void()> physics_frame;
	#endif

	Window *get_window() const;
	Viewport *get_viewport() const;
	RenderingServer *get_rendering_server() const;
	Node *get_root() const;
	SDL_Event *get_event() const;
	#ifdef B2_INCLUDED
	PhysicsServer2D *get_physics_server() const;
	#endif

	void start();
	void stop();

	void queue_free(Node *item);

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

	bool is_running() const;
};

}
