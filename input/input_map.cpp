#include <core/math/vector2.hpp>
#include <input/input_map.hpp>

#include <algorithm>

using namespace sdl;

InputMap::InputMap(): actions() {
}

InputMap::~InputMap() {
}

void InputMap::_add_input_to_action(const String &action_name, const InputProxy &input_proxy) {
	const auto &iterator = actions.find(action_name);

	if (iterator != actions.end())
		iterator->second.inputs.insert(std::move(input_proxy));
}

void InputMap::_remove_input_from_action(const String &action_name, const InputProxy &input_proxy) {
	const auto &iterator = actions.find(action_name);

	if (iterator != actions.end())
		iterator->second.inputs.erase(input_proxy);
}

void InputMap::create_action(const String &action_name) {
	const auto &iterator = actions.find(action_name);

	if (iterator == actions.end())
		actions.insert({action_name, {}});
}

void InputMap::add_key_to_action(const String &action_name, const std::shared_ptr<InputEvent> &input_event) {
	_add_input_to_action(action_name, input_event);
}

void InputMap::remove_key_from_action(const String &action_name, const std::shared_ptr<InputEvent> &input_event) {
	_remove_input_from_action(action_name, input_event);
}

bool InputMap::has_action(const String &action_name) const {
	return actions.count(action_name);
}

void InputMap::clear_action(const String &action_name) {
	const auto &iterator = actions.find(action_name);

	if (iterator != actions.end())
		actions.erase(iterator);
}

std::vector<InputEvent> InputMap::action_get_events(const String &action_name) const {
	const auto &iterator = actions.find(action_name);
	if (iterator == actions.end())
		return {};

	std::vector<InputEvent> input_events = {};
	for (const InputProxy &input_proxy: iterator->second.inputs)
		input_events.push_back(*input_proxy.input_event);

	return input_events;
}

const std::unordered_map<String, InputMap::Action> &InputMap::get_actions() const {
	return actions;
}

bool InputMap::event_get_action_state(const InputEvent *input_event, const String &action_name, bool *pressed, float *strength) const {
	const auto &iterator = actions.find(action_name);
	const InputEventAction *input_event_action = dynamic_cast<const InputEventAction*>(input_event);
	if (iterator == actions.end() || input_event_action)
		return false;

	const bool input_pressed = input_event_action->is_pressed();
	const float input_strength = input_pressed ? input_event_action->get_strength() : 0.0f;

	if (pressed)
		*pressed = input_pressed;

	if (strength)
		*strength = input_strength;

	return input_event_action->get_action_name() == action_name;
}


bool InputMap::event_is_action(const InputEvent *input_event, const String &action_name) const {
	return event_get_action_state(input_event, action_name);
}
