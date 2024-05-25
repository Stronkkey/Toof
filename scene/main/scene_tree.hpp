/*  This file is part of the Toof Engine. */
/** @file scene_tree.hpp */
/*
  BSD 3-Clause License

  Copyright (c) 2024-present, Stronkkey and Contributors

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
      list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#pragma once

#include <core/memory/signal.hpp>

#include <SDL_events.h>

#include <memory>

namespace Toof {

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
public:
	class Loop {
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
		uint64_t step_count;
		LoopType loop_type = LOOP_TYPE_NONE;
		bool paused;

		friend SceneTree;

		constexpr Loop(): frame_rate(60.0), delta_time(0.0), speed_scale(1.0), time_scale(1.0), prev_step_time(0), step_count(0), loop_type(LOOP_TYPE_NONE), paused(false) {
		}
	public:
		~Loop() = default;

		constexpr void set_frame_rate(double frame_rate) {
			this->frame_rate = frame_rate;
		}

		constexpr double get_frame_rate() const {
			return frame_rate;
		}

		constexpr double get_delta_time() const {
			return delta_time;
		}

		constexpr void set_speed_scale(double speed_scale) {
			this->speed_scale = speed_scale;
		}

		constexpr double get_speed_scale() const {
			return speed_scale;
		}

		constexpr void set_time_scale(double time_scale) {
			this->time_scale = time_scale;
		}

		constexpr double get_time_scale() const {
			return time_scale;
		}

		constexpr uint64_t get_step_count() const {
			return step_count;
		}

		constexpr void set_paused(bool is_paused) {
			paused = is_paused;
		}

		constexpr void pause() {
			paused = true;
		}

		constexpr void unpause() {
			paused = false;
		}

		constexpr bool is_paused() const {
			return paused;
		}
	};
private:
	bool running, paused, event_paused;

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
protected:
	void _add_child(Node *child);
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

 	constexpr Loop &get_render_loop() & {
		return render_loop;
	}

 	constexpr const Loop &get_render_loop() const & {
		return render_loop;
	}

 	constexpr Loop &get_process_loop() & {
		return process_loop;
	}

 	constexpr const Loop &get_process_loop() const & {
		return process_loop;
	}

	constexpr void pause() {
		paused = true;
	}

	constexpr void unpause() {
		paused = false;
	}

	constexpr bool is_paused() const {
		return paused;
	}

	constexpr void set_event_paused(const bool paused) {
		event_paused = paused;
	}

	constexpr bool is_event_paused() const {
		return event_paused;
	}

	#ifdef B2_INCLUDED

	constexpr Loop &get_physics_loop() & {
		return physics_loop;
	}

	constexpr const Loop &get_physics_loop() const & {
		return physics_loop;
	}

	#endif

	constexpr bool is_running() const {
		return running;
	}
};

}
