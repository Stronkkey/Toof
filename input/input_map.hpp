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

class InputMap {

public:
	struct Action {
		std::set<InputProxy, std::equal_to<InputProxy>> inputs;
	};

private:
	std::unordered_map<String, Action> actions;
	void _add_input_to_action(const String &action_name, const InputProxy &input_proxy);
	void _remove_input_from_action(const String &action_name, const InputProxy &input_proxy);

public:
	InputMap();
	~InputMap();

	void create_action(const String &action_name);
	void add_key_to_action(const String &action_name, const std::shared_ptr<InputEvent> &input_event);
	void remove_key_from_action(const String &action_name, const std::shared_ptr<InputEvent> &input_event);

	bool has_action(const String &action_name) const;
	void clear_action(const String &action_name);

	std::vector<InputEvent> action_get_events(const String &action_name) const;
	const std::unordered_map<String, Action> &get_actions() const;

	bool event_get_action_state(const InputEvent *input_event, const String &action_name, bool *pressed = nullptr, float *strength = nullptr) const;
	bool event_is_action(const InputEvent *input_event, const String &action_name) const;
};

}
