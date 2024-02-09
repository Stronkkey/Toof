#ifdef B2_INCLUDED

#include <scene/2d/physics/physics_body2d.hpp>
#include <scene/main/scene_tree.hpp>
#include <servers/physics_server.hpp>

void sdl::PhysicsBody2D::ready() {
	physics_body_rid = get_physics_server()->body_create();
}

void sdl::PhysicsBody2D::_notification(const int what) {
	Node2D::_notification(what);

	if (what == NOTIFICATION_READY)
		ready();
}

const std::unique_ptr<sdl::PhysicsServer2D> &sdl::PhysicsBody2D::get_physics_server() const {
	if (is_inside_tree())
		return get_tree()->get_physics_server();

	std::unique_ptr<PhysicsServer2D> _p;
	std::unique_ptr<PhysicsServer2D> *p = &_p;
	return *p;
}

void sdl::PhysicsBody2D::add_collision_exception_with(const PhysicsBody2D*) {
}

void sdl::PhysicsBody2D::remove_collision_exception_with(const PhysicsBody2D*) {
}

#endif