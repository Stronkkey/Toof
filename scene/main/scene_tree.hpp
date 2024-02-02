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
	double loop_frame_rate, loop_delta_time, loop_speed_scale, loop_time_scale;
	double render_frame_rate, render_delta_time, render_speed_scale, render_time_scale;

	#ifdef B2_INCLUDED
	double physics_frame_rate, physics_delta_time, physics_speed_scale, physics_time_scale;
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

	void set_render_frame_rate(const double new_render_frame_rate);
	double get_render_frame_rate() const;

	void set_loop_frame_rate(const double new_loop_frame_rate);
	double get_loop_frame_rate() const;

	void set_render_speed_scale(const double new_render_speed_scale);
	double get_render_speed_scale() const;

	void set_loop_speed_scale(const double new_loop_speed_scale);
	double get_loop_speed_scale() const;

	void set_render_time_scale(const double new_render_time_scale);
	double get_render_time_scale() const;

	void set_loop_time_scale(const double new_loop_time_scale);
	double get_loop_time_scale() const;

	double get_render_delta_time() const;
	double get_loop_delta_time() const;

	#ifdef B2_INCLUDED
	void set_physics_frame_rate(const double new_physics_frame_rate);
	double get_physics_frame_rate() const;

	void set_physics_speed_scale(const double new_physics_speed_scale);
	double get_physics_speed_scale() const;

	void set_physics_time_scale(const double new_physics_time_scale);
	double get_physics_time_scale() const;

	double get_physics_delta_time() const;
	#endif

	bool is_running() const;
};

}
