#ifdef B2_INCLUDED

#include <items/physics/physics_body2d.hpp>
#include <items/tree.hpp>
#include <servers/physics_server.hpp>

void sdl::PhysicsBody2D::ready() {
	physics_body_rid = get_physics_server()->body_create();
}

void sdl::PhysicsBody2D::_notification(const int what) {
	RenderingItem::_notification(what);

	if (what == NOTIFICATION_READY)
		ready();
}

sdl::PhysicsServer2D *sdl::PhysicsBody2D::get_physics_server() const {
	return get_tree() ? get_tree()->get_physics_server() : nullptr;
}

void sdl::PhysicsBody2D::add_collision_exception_with(const PhysicsBody2D*) {
}

void sdl::PhysicsBody2D::remove_collision_exception_with(const PhysicsBody2D*) {
}

#endif