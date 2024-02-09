#pragma once

#include <input/event_input_type.hpp>
#include <scene/resources/resource.hpp>

#include <memory>
#include <string>

namespace sdl {

class InputMap;

class InputEventKey {
public:
	constexpr bool is_echo() const;
};

class InputEvent : public Resource {
private:
	std::weak_ptr<InputMap> input_map;

	friend class InputMap;
	friend class SceneTree;

public:
	bool pressed;
	bool canceled;
	EventInputType type;

	InputEvent(const std::shared_ptr<InputMap> &input_map);

	bool is_action(const std::string &action_name) const;
	bool is_action_pressed(const std::string &action_name, const bool allow_echo = false) const;
	bool is_action_released(const std::string &action_name, const bool allow_echo = false) const;
};

}
