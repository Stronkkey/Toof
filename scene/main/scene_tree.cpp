#include <scene/main/scene_tree.hpp>
#include <scene/main/node.hpp>
#include <servers/rendering/viewport.hpp>
#include <servers/rendering/window.hpp>
#include <servers/rendering_server.hpp>
#include <input/input.hpp>
#include <input/input_event.hpp>

#ifdef B2_INCLUDED
#include <servers/physics_server.hpp>
#endif

#include <SDL_timer.h>

#include <thread>
#include <chrono>

using namespace sdl;

SceneTree::SceneTree() {
	running = false;

	paused = false;
	render_paused = false;
	process_paused = false;
	physics_paused = false;
	event_paused = false;

	const long time = std::chrono::high_resolution_clock::now().time_since_epoch().count();

	process_loop = Loop();
	physics_loop = Loop();
	render_loop = Loop();

	process_loop.frame_rate = 60.0;
	process_loop.delta_time = 0.0;
	process_loop.speed_scale = 1.0;
	process_loop.time_scale = 1.0;
	process_loop.prev_step_time = time;
	process_loop.loop_type = Loop::LOOP_TYPE_PROCESS;

	render_loop.frame_rate = 60.0;
	render_loop.delta_time = 0.0;
	render_loop.speed_scale = 1.0;
	render_loop.time_scale = 1.0;
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

	#ifdef B2_INCLUDED
	physics_loop.frame_rate = 60.0;
	physics_loop.delta_time = 0.0;
	physics_loop.speed_scale = 1.0;
	physics_loop.time_scale = 1.0;
	physics_loop.prev_step_time = time;
	physics_loop.loop_type = Loop::LOOP_TYPE_PHYSICS;

	physics_server = std::make_unique<PhysicsServer2D>();
	#else
	physics_loop.prev_step_time = 1 << 30;
	#endif
}

SceneTree::~SceneTree() {
	stop();
}

void SceneTree::_initialize() {
}

void SceneTree::_ended() {
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

	deferred_signals.disconnect_all_slots();
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
	#ifndef B2_INCLUDED
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
	const long delta  = (time_now - loop.prev_step_time);
	const double step_time = loop.speed_scale / loop.frame_rate;

	if (delta < step_time)
		return;
	const double true_delta = (double)delta / std::nano::den;

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

void SceneTree::_main_loop() {
	while (running) {
		if (paused)
			return;

		if (!event_paused)
			while (SDL_PollEvent(event.get()))
				step_event();

		if (!render_paused)
			_do_loop(render_loop);

		if (!process_paused)
			_do_loop(process_loop);

		#ifdef B2_INCLUDED
		if (!physics_paused)
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

void SceneTree::queue_free(Node *item) {
	deferred_item_removal.push_back(item);
}

void SceneTree::set_paused(const bool paused) {
	this->paused = paused;
}

bool SceneTree::is_paused() const {
	return paused;
}

void SceneTree::set_render_paused(const bool paused) {
	render_paused = paused;
}

bool SceneTree::is_render_paused() const {
	return render_paused;
}

void SceneTree::set_process_paused(const bool paused) {
	process_paused = paused;
}

bool SceneTree::is_process_paused() const {
	return process_paused;
}

void SceneTree::set_event_paused(const bool paused) {
	event_paused = paused;
}

bool SceneTree::is_event_paused() const {
	return event_paused;
}

#ifdef B2_INCLUDED
void SceneTree::set_physics_paused(const bool paused) {
	physics_paused = paused;
}

bool SceneTree::is_physics_paused() const {
	return physics_paused;
}
#endif

const std::unique_ptr<Window> &SceneTree::get_window() const {
	return window;
}

const std::unique_ptr<Viewport> &SceneTree::get_viewport() const {
	return viewport;
}

const std::unique_ptr<RenderingServer> &SceneTree::get_rendering_server() const {
	return rendering_server;
}

const std::unique_ptr<Node> &SceneTree::get_root() const {
	return root;
}

const std::unique_ptr<SDL_Event> &SceneTree::get_event() const {
	return event;
}

const std::unique_ptr<Input> &SceneTree::get_input() const {
	return input;
}

#ifdef B2_INCLUDED
const std::unique_ptr<PhysicsServer2D> &SceneTree::get_physics_server() const {
	return physics_server;
}
#endif

void SceneTree::set_render_frame_rate(const double new_render_frame_rate) {
	render_loop.frame_rate = new_render_frame_rate;
}

double SceneTree::get_render_frame_rate() const {
	return render_loop.frame_rate;
}

void SceneTree::set_process_frame_rate(const double new_process_frame_rate) {
	process_loop.frame_rate = new_process_frame_rate;
}

double SceneTree::get_process_frame_rate() const {
	return process_loop.frame_rate;
}

void SceneTree::set_render_speed_scale(const double new_render_speed_scale) {
	render_loop.speed_scale = new_render_speed_scale;
}

double SceneTree::get_render_speed_scale() const {
	return render_loop.speed_scale;
}

void SceneTree::set_process_speed_scale(const double new_process_speed_scale) {
	process_loop.speed_scale = new_process_speed_scale;
}

double SceneTree::get_process_speed_scale() const {
	return process_loop.speed_scale;
}

void SceneTree::set_render_time_scale(const double new_render_time_scale) {
	render_loop.time_scale = new_render_time_scale;
}

double SceneTree::get_render_time_scale() const {
	return render_loop.time_scale;
}

void SceneTree::set_process_time_scale(const double new_process_time_scale) {
	process_loop.time_scale = new_process_time_scale;
}

double SceneTree::get_process_time_scale() const {
	return process_loop.time_scale;
}

double SceneTree::get_render_delta_time() const {
	return render_loop.delta_time;
}

double SceneTree::get_process_delta_time() const {
	return process_loop.delta_time;
}

uint64_t SceneTree::get_render_step_count() const {
	return render_loop.step_count;
}

uint64_t SceneTree::get_process_step_count() const {
	return process_loop.step_count;
}

bool SceneTree::is_running() const {
	return running;
}

#ifdef B2_INCLUDED
void SceneTree::set_physics_frame_rate(const double new_physics_frame_rate) {
	physics_loop.frame_rate = new_physics_frame_rate;
}

double SceneTree::get_physics_frame_rate() const {
	return physics_loop.frame_rate;
}

void SceneTree::set_physics_speed_scale(const double new_physics_speed_scale) {
	physics_loop.speed_scale = new_physics_speed_scale;
}

double SceneTree::get_physics_speed_scale() const {
	return physics_loop.speed_scale;
}

void SceneTree::set_physics_time_scale(const double new_physics_time_scale) {
	physics_loop.time_scale = new_physics_time_scale;
}

double SceneTree::get_physics_time_scale() const {
	return physics_loop.time_scale;
}

double SceneTree::get_physics_delta_time() const {
	return physics_loop.delta_time;
}
#endif
