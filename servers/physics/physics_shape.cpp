#include <servers/physics/physics_shape.hpp>

bool sdl::PhysicsShape::collides_against(const PhysicsShape *shape) const {
	switch(type) {
		case PHYSICS_SHAPE_TYPE_BOX:
			return reinterpret_cast<const PhysicsShapeBox*>(this)->_collides_against(shape);
		case PHYSICS_SHAPE_TYPE_CIRCLE:
			return reinterpret_cast<const PhysicsShapeCircle*>(this)->_collides_against(shape);
		default:
			return false;
	}
}

bool sdl::PhysicsShapeBox::_collides_against(const PhysicsShape *shape) const {
	
}