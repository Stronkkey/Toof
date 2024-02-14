#pragma once

#include <input/input_event.hpp>
#include <input/input_proxy.hpp>

#include <SDL_keycode.h>

#include <string>
#include <unordered_map>
#include <set>
#include <memory>
#include <vector>

namespace sdl {

struct Vector2;

class InputMap {

private:
	enum KeyInputType {
		KEY_INPUT_TYPE_KEYSYM,
		KEY_INPUT_TYPE_SCANCODE,
		KEY_INPUT_TYPE_NONE
	};

	struct Action {
		float deadzone;
		std::set<InputProxy, std::equal_to<InputProxy>> inputs;
	};

private:
	std::unordered_map<std::string, Action> actions;
	void _add_input_to_action(const std::string &action_name, InputProxy input_proxy);
	void _remove_input_from_action(const std::string &action_name, const InputProxy &input_proxy);

public:
	InputMap();
	~InputMap();

	void create_action(const std::string &action_name);
	void add_key_to_action(const std::string &action_name, std::unique_ptr<InputEvent> input_event);
	void remove_key_from_action(const std::string &action_name, std::unique_ptr<InputEvent> input_event);

	bool has_action(const std::string &action_name) const;
	void clear_action(const std::string &action_name);

	void action_set_deadzone(const std::string &action_name, const float deadzone);
	float action_get_deadzone(const std::string &action_name) const;

	std::vector<InputEvent> action_get_events(const std::string &action_name) const;

	bool event_get_action_state(const InputEvent *input_event, const std::string &action_name, bool *pressed = nullptr, float *strength = nullptr) const;
	bool event_is_action(const InputEvent *input_event, const std::string &action_name) const;
};

}
