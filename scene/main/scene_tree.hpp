#pragma once

#include <core/memory/signal.hpp>

#include <SDL_events.h>

#include <memory>

namespace sdl {

template<class>
struct Rect2;
class Node;
class Window;
class RenderingServer;
class Viewport;
class Input;

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
		uint64_t step_count = 0;
		LoopType loop_type = LOOP_TYPE_NONE;
	};

private:
	bool running, paused, render_paused, process_paused, physics_paused, event_paused;

	Loop render_loop;
	Loop process_loop;
	Loop physics_loop;

	void _step_loop(const Loop::LoopType loop_type);
	void _do_loop(Loop &loop);
	void _main_loop();

	std::vector<Node*> deferred_item_removal;

	std::unique_ptr<Window> window;
	std::unique_ptr<Viewport> viewport;
	std::unique_ptr<Input> input;
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

	Signal<> process_frame;
	Signal<> render_frame;
	Signal<> deferred_signals;
	Signal<> physics_frame;

	constexpr const std::unique_ptr<Window> &get_window() const {
		return window;
	}

	constexpr const std::unique_ptr<Viewport> &get_viewport() const {
		return viewport;
	}

	constexpr const std::unique_ptr<RenderingServer> &get_rendering_server() const {
		return rendering_server;
	}

	constexpr const std::unique_ptr<Node> &get_root() const {
		return root;
	}

	constexpr const std::unique_ptr<SDL_Event> &get_event() const {
		return event;
	}

	constexpr const std::unique_ptr<Input> &get_input() const {
		return input;
	}

	#ifdef B2_INCLUDED
	constexpr const std::unique_ptr<PhysicsServer2D> &get_physics_server() const {
		return physics_server;
	}
	#endif

	void start();
	void stop();
	
	void step_render(const double delta);
	void step_process(const double delta);
	void step_event();
	void step_physics(const double delta);

	void queue_free(Node *node);

	constexpr void set_paused(const bool paused) {
		this->paused = paused;
	}

	constexpr bool is_paused() const {
		return paused;
	}

	constexpr void set_render_paused(const bool paused) {
		render_paused = paused;
	}

	constexpr bool is_render_paused() const {
		return render_paused;
	}

	constexpr void set_process_paused(const bool paused) {
		process_paused = paused;
	}

	constexpr bool is_process_paused() const {
		return process_paused;
	}

	constexpr void set_event_paused(const bool paused) {
		event_paused = paused;
	}

	constexpr bool is_event_paused() const {
		return event_paused;
	}

	#ifdef B2_INCLUDED
	constexpr void set_physics_paused(const bool paused) {
		physics_paused = paused;
	}

	constexpr bool is_physics_paused() const {
		return physics_paused;
	}
	#endif

	constexpr void set_render_frame_rate(const double new_render_frame_rate) {
		render_loop.frame_rate = new_render_frame_rate;
	}

	constexpr double get_render_frame_rate() const {
		return render_loop.frame_rate;
	}

	constexpr void set_process_frame_rate(const double new_process_frame_rate) {
		process_loop.frame_rate = new_process_frame_rate;
	}

	constexpr double get_process_frame_rate() const {
		return process_loop.frame_rate;
	}

	constexpr void set_render_speed_scale(const double new_render_speed_scale) {
		render_loop.speed_scale = new_render_speed_scale;
	}

	constexpr double get_render_speed_scale() const {
		return render_loop.speed_scale;
	}

	constexpr void set_process_speed_scale(const double new_process_speed_scale) {
		process_loop.speed_scale = new_process_speed_scale;
	}

	constexpr double get_process_speed_scale() const {
		return process_loop.speed_scale;
	}

	constexpr void set_render_time_scale(const double new_render_time_scale) {
		render_loop.time_scale = new_render_time_scale;
	}

	constexpr double get_render_time_scale() const {
		return render_loop.time_scale;
	}

	constexpr void set_process_time_scale(const double new_process_time_scale) {
		process_loop.time_scale = new_process_time_scale;
	}

	constexpr double get_process_time_scale() const {
		return process_loop.time_scale;
	}

	constexpr double get_render_delta_time() const {
		return render_loop.delta_time;
	}

	constexpr double get_process_delta_time() const {
		return process_loop.delta_time;
	}

	constexpr uint64_t get_render_step_count() const {
		return render_loop.step_count;
	}

	constexpr uint64_t get_process_step_count() const {
		return process_loop.step_count;
	}

	#ifdef B2_INCLUDED
	constexpr void set_physics_frame_rate(const double new_physics_frame_rate) {
		physics_loop.frame_rate = new_physics_frame_rate;
	}

	constexpr double get_physics_frame_rate() const {
		return physics_loop.frame_rate;
	}

	constexpr void set_physics_speed_scale(const double new_physics_speed_scale) {
		physics_loop.speed_scale = new_physics_speed_scale;
	}

	constexpr double get_physics_speed_scale() const {
		return physics_loop.speed_scale;
	}

	constexpr void set_physics_time_scale(const double new_physics_time_scale) {
		physics_loop.time_scale = new_physics_time_scale;
	}

	constexpr double get_physics_time_scale() const {
		return physics_loop.time_scale;
	}

	constexpr double get_physics_delta_time() const {
		return physics_loop.delta_time;
	}

	constexpr uint64_t get_physics_step_count() const {
		return physics_loop.step_count;
	}
	#endif

	constexpr bool is_running() const {
		return running;
	}
};

}
