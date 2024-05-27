/*  This file is part of the Toof Engine. */
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
#include <scene/main/scene_tree.hpp>
#include <scene/main/node.hpp>
#include <servers/rendering/viewport.hpp>
#include <servers/rendering/window.hpp>
#include <servers/rendering_server.hpp>
#include <input/input.hpp>
#include <input/input_event.hpp>

#ifdef TOOF_PHYSICS_ENABLED
#include <servers/physics_server.hpp>
#endif

#include <SDL_timer.h>

#include <thread>
#include <chrono>

using namespace Toof;

SceneTree::SceneTree() {
	running = false;
	paused = false;

	const long time = std::chrono::high_resolution_clock::now().time_since_epoch().count();

	process_loop = Loop();
	physics_loop = Loop();
	render_loop = Loop();

	process_loop.prev_step_time = time;
	process_loop.loop_type = Loop::LOOP_TYPE_PROCESS;

	render_loop.prev_step_time = time;
	render_loop.loop_type = Loop::LOOP_TYPE_RENDER;

	window = std::make_unique<Window>();
	viewport = std::make_unique<Viewport>();
	rendering_server = std::make_unique<RenderingServer>(viewport.get());
	root = std::make_unique<Node>();
	input = std::make_unique<Input>(&process_loop.step_count, &render_loop.step_count);

	viewport->create(window.get());
	root->set_name("Root");
	root->set_tree(this);

	#ifdef TOOF_PHYSICS_ENABLED
	physics_loop.prev_step_time = time;
	physics_loop.loop_type = Loop::LOOP_TYPE_PHYSICS;

	physics_server = std::make_unique<PhysicsServer2D>();
	#endif
}

SceneTree::~SceneTree() {
	stop();
}

void SceneTree::_initialize() {
}

void SceneTree::_ended() {
}

void SceneTree::_add_child(Node *child) {
	if (root)
		root->add_child(child);
}

void SceneTree::step_render(const double delta) {
	render_loop.delta_time = delta * render_loop.time_scale;
	render_frame();

	if (root)
		root->propagate_notification(Node::NOTIFICATION_RENDER);
	rendering_server->render();
}

void SceneTree::step_process(const double delta) {
	process_loop.delta_time = delta * process_loop.time_scale;
	process_frame();

	if (root)
		root->propagate_notification(Node::NOTIFICATION_PROCESS);

	deferred_signals();

	for (Node *item: deferred_item_removal)
		delete item;

	deferred_signals.disconnect_all();
	deferred_item_removal.clear();
}

void SceneTree::step_event() {
	if (event->type == SDL_QUIT)
		stop();

	const std::shared_ptr<InputEvent> &input_event = input->process_event(event.get());
	if (root && input_event)
		root->propagate_input_event(input_event);
}

void SceneTree::step_physics(const double delta) {
	#ifndef TOOF_PHYSICS_ENABLED
	return;
	#endif

	physics_loop.delta_time = delta * physics_loop.time_scale;
	physics_frame();

	if (root)
		root->propagate_notification(Node::NOTIFICATION_PREDELETE);

	physics_server->tick(physics_loop.delta_time);
}

void SceneTree::_do_loop(Loop &loop) {
	const long time_now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	const long delta = (time_now - loop.prev_step_time);
	const double step_time = loop.speed_scale / loop.frame_rate;
	const double true_delta = static_cast<double>(delta) / std::nano::den;

	if (true_delta < step_time)
		return;

	switch (loop.loop_type) {
		case Loop::LOOP_TYPE_RENDER:
			step_render(true_delta);
			break;
		case Loop::LOOP_TYPE_PROCESS:
			step_process(true_delta);
			break;
		case Loop::LOOP_TYPE_PHYSICS:
			step_physics(true_delta);
			break;
		default:
			break;
	}

	loop.prev_step_time = time_now;
	loop.step_count++;
}

void SceneTree::queue_free(Node *node) {
	deferred_item_removal.push_back(node);
}

void SceneTree::_main_loop() {
	while (running) {
		if (paused)
			return;

		if (!event_paused)
			while (SDL_PollEvent(event.get()))
				step_event();

		if (!render_loop.paused)
			_do_loop(render_loop);

		if (!process_loop.paused)
			_do_loop(process_loop);

		#ifdef TOOF_PHYSICS_ENABLED
		if (!physics_loop.paused)
			_do_loop(physics_loop);
		#endif

		std::this_thread::yield();
	}
}

void SceneTree::start() {
	if (!window->intialized_successfully() || running)
		return;

	running = true;
	event = std::make_unique<SDL_Event>();

	_initialize();
	_main_loop();
}

void SceneTree::stop() {
	if (running) {
		running = false;
		_ended();
	}
}
