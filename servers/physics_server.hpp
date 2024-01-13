#ifdef B2_INCLUDED
#pragma once

#include <core/math/vector2.hpp>

#include <memory>
#include <optional>
#include <unordered_map>

namespace sdl {

struct PhysicsWorld2D;
struct PhysicsBody;
struct PhysicsShape;

class PhysicsServer2D {

private:
	std::unordered_map<uid, std::unique_ptr<PhysicsWorld2D>> worlds;
	std::unordered_map<uid, std::unique_ptr<PhysicsBody>> bodies;
	std::unordered_map<uid, std::unique_ptr<PhysicsShape>> shapes;
	Vector2 gravity;

	uid uid_index;

	uid assign_uid();
	void destroy_uid(const uid destroy_uid);
	void tick_world(const std::unique_ptr<PhysicsWorld2D> &world, const double delta);

public:
	PhysicsServer2D();
	~PhysicsServer2D();
	
	void remove_uid(const uid destroy_uid);
	void tick(const double delta);

	void set_gravity(const Vector2 &new_gravity);
	Vector2 get_gravity() const;

	uid create_world();

	void world_set_gravity(const uid world_uid, const Vector2 &new_world_gravity);
	std::optional<Vector2> world_get_gravity(const uid world_uid) const;
	void world_set_velocity_iterations(const uid world_uid, const int32_t velocity_iterations);
	std::optional<int32_t> world_get_velocity_iterations(const uid world_uid) const;
	void world_set_position_iterations(const uid world_uid, const int32_t position_iterations);
	std::optional<int32_t> world_get_position_iterations(const uid world_uid);
};

}

#endif // !B2_INCLUDED