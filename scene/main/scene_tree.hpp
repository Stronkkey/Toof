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
class InputMap;

#ifdef B2_INCLUDED
class PhysicsServer2D;
#endif

class SceneTree {

private:
	struct Loop {
		enum LoopType {
			LOOP_TYPE_PROCESS,
			LOOP_TYPE_RENDER,
			LOOP_TYPE_PHYSICS,
			LOOP_TYPE_NONE
		};

		double frame_rate;
		double delta_time;
		double speed_scale;
		double time_scale;
		long prev_step_time;
		LoopType loop_type = LOOP_TYPE_NONE;
	};

private:
	bool running, paused, render_paused, process_paused, physics_paused, event_paused;

	std::unique_ptr<Loop> render_loop, process_loop, physics_loop;

	void _step_loop(const Loop::LoopType loop_type);
	void _do_loop(const std::unique_ptr<Loop> &loop);
	void _main_loop();

	std::vector<Node*> deferred_item_removal;

	std::unique_ptr<Window> window;
	std::unique_ptr<Viewport> viewport;
	std::unique_ptr<InputMap> input_map;
	std::unique_ptr<RenderingServer> rendering_server;
	std::unique_ptr<SDL_Event> event;
	std::unique_ptr<Node> root;

	#ifdef B2_INCLUDED
	std::unique_ptr<PhysicsServer2D> physics_server;
	#endif

	virtual void _initialize();
	virtual void _ended();

public:
	SceneTree();
	virtual ~SceneTree();

	boost::signals2::signal<void()> process_frame;
	boost::signals2::signal<void()> render_frame;
	boost::signals2::signal<void()> deferred_signals;
	boost::signals2::signal<void()> physics_frame;

	const std::unique_ptr<Window> &get_window() const;
	const std::unique_ptr<Viewport> &get_viewport() const;
	const std::unique_ptr<RenderingServer> &get_rendering_server() const;
	const std::unique_ptr<Node> &get_root() const;
	const std::unique_ptr<SDL_Event> &get_event() const;
	const std::unique_ptr<InputMap> &get_input_map() const;

	#ifdef B2_INCLUDED
	const std::unique_ptr<PhysicsServer2D> &get_physics_server() const;
	#endif

	void start();
	void stop();
	
	void step_render(const double delta);
	void step_process(const double delta);
	void step_event();
	void step_physics(const double delta);

	void queue_free(Node *node);

	void set_paused(const bool paused);
	bool is_paused() const;

	void set_render_paused(const bool paused);
	bool is_render_paused() const;

	void set_process_paused(const bool paused);
	bool is_process_paused() const;

	void set_event_paused(const bool paused);
	bool is_event_paused() const;

	#ifdef B2_INCLUDED
	void set_physics_paused(const bool paused);
	bool is_physics_paused() const;
	#endif

	void set_render_frame_rate(const double new_render_frame_rate);
	double get_render_frame_rate() const;

	void set_process_frame_rate(const double new_process_frame_rate);
	double get_process_frame_rate() const;

	void set_render_speed_scale(const double new_render_speed_scale);
	double get_render_speed_scale() const;

	void set_process_speed_scale(const double new_process_speed_scale);
	double get_process_speed_scale() const;

	void set_render_time_scale(const double new_render_time_scale);
	double get_render_time_scale() const;

	void set_process_time_scale(const double new_process_time_scale);
	double get_process_time_scale() const;

	double get_render_delta_time() const;
	double get_process_delta_time() const;

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
