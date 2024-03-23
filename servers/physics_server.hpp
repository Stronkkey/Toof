#ifdef B2_INCLUDED
#pragma once

#include <core/math/transform2d.hpp>
#include <core/memory/optional.hpp>

#include <memory>
#include <unordered_map>
#include <variant>

#include <box2d/b2_body.h>

namespace sdl {

struct PhysicsWorld2D;
struct PhysicsBody;
struct PhysicsShape;

class PhysicsServer2D {

private:
	std::unordered_map<uid, std::unique_ptr<PhysicsWorld2D>> worlds;
	std::unordered_map<uid, std::unique_ptr<PhysicsBody>> bodies;
	std::unordered_map<uid, std::unique_ptr<PhysicsShape>> shapes;
	Vector2f gravity;

	uid uid_index;
	b2BodyDef default_body_definition;
	
	uid assign_uid();
	void destroy_uid(const uid destroy_uid);
	void tick_world(const std::unique_ptr<PhysicsWorld2D> &world, const double delta);
	void create_physics_body_from_def(const std::unique_ptr<PhysicsBody> &physics_body, const uid world_uid, const b2BodyDef *body_def = nullptr);
	void transfer_body_to_world(const std::unique_ptr<PhysicsBody> &physics_body, const uid world_uid);
	std::unique_ptr<b2BodyDef> get_body_def_from_body(const b2Body *body) const;

public:
	enum BodyState {
		BODY_STATE_TRANSFORM,
		BODY_STATE_NONE
	};
	typedef std::variant<Transform2D> body_state_variant;

public:
	PhysicsServer2D();
	~PhysicsServer2D();
	
	void remove_uid(const uid destroy_uid);
	void tick(const double delta);

	void set_gravity(const Vector2f &new_gravity);
	const Vector2f &get_gravity() const;

	uid create_world();
	uid body_create();

	void world_set_gravity(const uid world_uid, const Vector2f &new_world_gravity);
	Optional<Vector2f> world_get_gravity(const uid world_uid) const;
	void world_set_velocity_iterations(const uid world_uid, const int32_t velocity_iterations);
	Optional<int32_t> world_get_velocity_iterations(const uid world_uid) const;
	void world_set_position_iterations(const uid world_uid, const int32_t position_iterations);
	Optional<int32_t> world_get_position_iterations(const uid world_uid) const;

	void body_set_world(const uid body_uid, const uid world_uid);
	Optional<uid> body_get_world(const uid body_uid) const;
	void body_set_state(const uid body_uid, const BodyState body_state, const body_state_variant &state_value);
	body_state_variant body_get_state(const uid body_uid, const BodyState body_state) const;
};

}

#endif // !B2_INCLUDED