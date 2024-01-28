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


SceneTree::SceneTree(): running(false),
    fixed_frame_rate(60.0),
    frame_rate(60.0),
    render_delta_time(0.0),
    loop_delta_time(0.0)
{
	window = new Window;
	viewport = new Viewport;
	rendering_server = new RenderingServer(viewport);
	root = new Node;

	viewport->create(window);
	root->set_name("Root");
	root->set_tree(this);
	
	#ifdef B2_INCLUDED
	physics_frame_rate = 60.0;
	physics_delta_time = 0.0;
	physics_server = new PhysicsServer2D;
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

void SceneTree::events() {
	if (event->type == SDL_QUIT) {
		stop();
		return;
	}

	if (root)
		root->propagate_notification(Node::NOTIFICATION_EVENT);
}

void SceneTree::render() {
	if (!running)
		return;

	render_frame();
	if (root)
		root->propagate_notification(Node::NOTIFICATION_RENDER);
	rendering_server->render();
}

#ifdef B2_INCLUDED
void SceneTree::physics() {
	if (!running)
		return;

	physics_server->tick(physics_delta_time);
	//physics_frame();
	
	if (root)
		root->propagate_notification(Node::NOTIFICATION_PREDELETE);
}
#endif

void SceneTree::loop() {
	loop_frame();
	if (root)
		root->propagate_notification(Node::NOTIFICATION_LOOP);
}

void SceneTree::_initialize() {
}

void SceneTree::_ended() {
}

double SceneTree::wait_for(const double time_seconds) const {
	auto start = std::chrono::system_clock::now();
	auto wait_time = std::chrono::duration<double>(time_seconds);
	
	std::this_thread::sleep_for(wait_time);

	auto end = std::chrono::system_clock::now();

	return (end - start).count() / (double)std::nano::den;
}

void SceneTree::render_loop() {
	while (running) {
		const double delta = wait_for(1 / frame_rate);

		render_delta_time = delta;
		render();
	}
}

void SceneTree::main_loop() {
	while (running) {
		const double delta = wait_for(1 / fixed_frame_rate);

		loop_delta_time = delta;
		loop();
		deferred_signals();

		for (Node *item: deferred_item_removal)
			delete item;

		deferred_signals.disconnect_all_slots();
		deferred_item_removal.clear();
	}
}

void SceneTree::event_loop() {
	while (running) {
		SDL_WaitEvent(event);
		events();
	}
}

#ifdef B2_INCLUDED
void SceneTree::physics_loop() {
	while (running) {
		const double delta = wait_for(1 / physics_delta_time);

		physics();
		physics_delta_time = delta;
	}
}
#endif

void SceneTree::start() {
	if (!window->intialized_successfully() || running)
		return;

	running = true;
	event = new SDL_Event;
	_initialize();

	std::thread main_loop_thread = std::thread(&SceneTree::main_loop, this);
	std::thread event_loop_thread = std::thread(&SceneTree::event_loop, this);
	render_loop();

	main_loop_thread.join();
	event_loop_thread.join();
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

void SceneTree::set_frame_rate(const double new_frame_rate) {
	frame_rate = new_frame_rate;
}

double SceneTree::get_frame_rate() const {
	return frame_rate;
}

void SceneTree::set_fixed_frame_rate(const double new_fixed_frame_rate) {
	fixed_frame_rate = new_fixed_frame_rate;
}

double SceneTree::get_fixed_frame_rate() const {
	return fixed_frame_rate;
}

double SceneTree::get_render_delta_time() const {
	return render_delta_time;
}

double SceneTree::get_loop_delta_time() const {
	return loop_delta_time;
}

bool SceneTree::is_running() const {
	return running;
}

#ifdef B2_INCLUDED
void SceneTree::set_physics_frame_rate(const double new_physics_frame_rate) {
	physics_frame_rate = new_physics_frame_rate;
}

double SceneTree::get_physics_frame_rate() const {
	return physics_frame_rate;
}

double SceneTree::get_physics_delta_time() const {
	return physics_delta_time;
}
#endif
