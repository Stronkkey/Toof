#ifdef B2_INCLUDED

#pragma once

#include <scene/resources/world2d.hpp>
#include <scene/2d/node2d.hpp>

namespace Toof {

class PhysicsServer2D;

class PhysicsBody2D : public Node2D {
private:
	uid physics_body_rid;
	World2D world_2d;

	void ready();
	void _notification(const int what) override;

protected:
	const std::unique_ptr<PhysicsServer2D> &get_physics_server() const;

public:
	void add_collision_exception_with(const PhysicsBody2D *physics_body2d);
	void remove_collision_exception_with(const PhysicsBody2D *physics_body2d);
};

}

#endif