#include <scene/main/scene_tree.hpp>
#include <scene/main/node.hpp>
#include <servers/rendering/viewport.hpp>
#include <servers/rendering/window.hpp>
#include <servers/rendering_server.hpp>

#ifdef B2_INCLUDED
#include <servers/physics_server.hpp>
#endif

#include <SDL_timer.h>

#include <thread>
#include <chrono>

using namespace sdl;

SceneTree::SceneTree() {
	running = false;

	const long time = std::chrono::high_resolution_clock::now().time_since_epoch().count();

	process_loop = std::make_unique<Loop>();
	physics_loop = std::make_unique<Loop>();
	render_loop = std::make_unique<Loop>();

	process_loop->frame_rate = 60.0;
	process_loop->delta_time = 0.0;
	process_loop->speed_scale = 1.0;
	process_loop->time_scale = 1.0;
	process_loop->prev_step_time = time;
	process_loop->loop_type = Loop::LOOP_TYPE_PROCESS;

	render_loop->frame_rate = 60.0;
	render_loop->delta_time = 0.0;
	render_loop->speed_scale = 1.0;
	render_loop->time_scale = 1.0;
	render_loop->prev_step_time = time;
	render_loop->loop_type = Loop::LOOP_TYPE_RENDER;

	window = new Window;
	viewport = new Viewport;
	rendering_server = new RenderingServer(viewport);
	root = new Node;

	viewport->create(window);
	root->set_name("Root");
	root->set_tree(this);

	#ifdef B2_INCLUDED
	physics_loop->frame_rate = 60.0;
	physics_loop->delta_time = 0.0;
	physics_loop->speed_scale = 1.0;
	physics_loop->time_scale = 1.0;
	physics_loop->prev_step_time = time;
	physics_loop->loop_type = Loop::LOOP_TYPE_PHYSICS;

	physics_server = new PhysicsServer2D;
	#else
	physics_loop->prev_step_time = 1 << 30;
	#endif
}

SceneTree::~SceneTree() {
	stop();
	
	if (window)
		delete window;
	if (viewport)
		delete viewport;
	if (rendering_server)
		delete rendering_server;
	if (event)
		delete event;
	if (root)
		delete root;

	#ifdef B2_INCLUDED
	if (physics_server)
		delete physics_server;
	#endif
}

void SceneTree::_initialize() {
}

void SceneTree::_ended() {
}

void SceneTree::step_render(const double delta) {
	render_loop->delta_time = delta * render_loop->time_scale;
	render_frame();

	if (root)
		root->propagate_notification(Node::NOTIFICATION_RENDER);
	rendering_server->render();
}

void SceneTree::step_process(const double delta) {
	process_loop->delta_time = delta * process_loop->time_scale;
	loop_frame();

	if (root)
		root->propagate_notification(Node::NOTIFICATION_LOOP);

	deferred_signals();

	for (Node *item: deferred_item_removal)
		delete item;

	deferred_signals.disconnect_all_slots();
	deferred_item_removal.clear();
}

void SceneTree::step_event() {
	if (event->type == SDL_QUIT)
		stop();

	if (root)
		root->propagate_notification(Node::NOTIFICATION_EVENT);
}

void SceneTree::step_physics(const double delta) {
	#ifndef B2_INCLUDED
	return;
	#endif

	physics_loop->delta_time = delta * physics_loop->time_scale;
	physics_frame();

	if (root)
		root->propagate_notification(Node::NOTIFICATION_PREDELETE);

	physics_server->tick(physics_loop->delta_time);
}

void SceneTree::_do_loop(const std::unique_ptr<Loop> &loop) {
	const long time_now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	const long delta  = (time_now - loop->prev_step_time);
	const double step_time = loop->speed_scale / loop->frame_rate;

	if (delta < step_time)
		return;
	const double true_delta = (double)delta / std::nano::den;

	switch (loop->loop_type) {
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
	loop->prev_step_time = time_now;
}

void SceneTree::_main_loop() {
	while (running) {
		while (SDL_PollEvent(event))
			step_event();

		_do_loop(render_loop);
		_do_loop(process_loop);

		#ifdef B2_INCLUDED
		_do_loop(physics_loop);
		#endif

		std::this_thread::yield();
	}
}

void SceneTree::start() {
	if (!window->intialized_successfully() || running)
		return;

	running = true;
	event = new SDL_Event;

	_initialize();
	_main_loop();
}

void SceneTree::stop() {
	if (running) {
		running = false;
		_ended();
	}
}

void SceneTree::queue_free(Node *item) {
	deferred_item_removal.push_back(item);
}


Window *SceneTree::get_window() const {
	return window;
}

Viewport *SceneTree::get_viewport() const {
	return viewport;
}

RenderingServer *SceneTree::get_rendering_server() const {
	return rendering_server;
}

Node *SceneTree::get_root() const {
	return root;
}

SDL_Event *SceneTree::get_event() const {
	return event;
}

#ifdef B2_INCLUDED
PhysicsServer2D *SceneTree::get_physics_server() const {
	return physics_server;
}
#endif

void SceneTree::set_render_frame_rate(const double new_render_frame_rate) {
	render_loop->frame_rate = new_render_frame_rate;
}

double SceneTree::get_render_frame_rate() const {
	return render_loop->frame_rate;
}

void SceneTree::set_loop_frame_rate(const double new_loop_frame_rate) {
	process_loop->frame_rate = new_loop_frame_rate;
}

double SceneTree::get_loop_frame_rate() const {
	return process_loop->frame_rate;
}

void SceneTree::set_render_speed_scale(const double new_render_speed_scale) {
	render_loop->speed_scale = new_render_speed_scale;
}

double SceneTree::get_render_speed_scale() const {
	return render_loop->speed_scale;
}

void SceneTree::set_loop_speed_scale(const double new_loop_speed_scale) {
	process_loop->speed_scale = new_loop_speed_scale;
}

double SceneTree::get_loop_speed_scale() const {
	return process_loop->speed_scale;
}

void SceneTree::set_render_time_scale(const double new_render_time_scale) {
	render_loop->time_scale = new_render_time_scale;
}

double SceneTree::get_render_time_scale() const {
	return render_loop->time_scale;
}

void SceneTree::set_loop_time_scale(const double new_loop_time_scale) {
	process_loop->time_scale = new_loop_time_scale;
}

double SceneTree::get_loop_time_scale() const {
	return process_loop->time_scale;
}

double SceneTree::get_render_delta_time() const {
	return render_loop->delta_time;
}

double SceneTree::get_loop_delta_time() const {
	return process_loop->delta_time;
}

bool SceneTree::is_running() const {
	return running;
}

#ifdef B2_INCLUDED
void SceneTree::set_physics_frame_rate(const double new_physics_frame_rate) {
	physics_loop->frame_rate = new_physics_frame_rate;
}

double SceneTree::get_physics_frame_rate() const {
	return physics_loop->frame_rate;
}

void SceneTree::set_physics_speed_scale(const double new_physics_speed_scale) {
	physics_loop->speed_scale = new_physics_speed_scale;
}

double SceneTree::get_physics_speed_scale() const {
	return physics_loop->speed_scale;
}

void SceneTree::set_physics_time_scale(const double new_physics_time_scale) {
	physics_loop->time_scale = new_physics_time_scale;
}

double SceneTree::get_physics_time_scale() const {
	return physics_loop->time_scale;
}

double SceneTree::get_physics_delta_time() const {
	return physics_loop->delta_time;
}
#endif
