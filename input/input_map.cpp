#include <core/math/vector2.hpp>
#include <input/input_map.hpp>

#include <algorithm>

using namespace sdl;

InputMap::InputMap(SDL_Event *event): mapped_inputs(), event(event) {
}

InputMap::~InputMap() {
}

void InputMap::_add_input_to_map(const std::string &map_name, const InputMap::Input &input) {
	auto iterator = mapped_inputs.find(map_name);

	if (iterator != mapped_inputs.end())
		iterator->second.push_back(input);
	else
		mapped_inputs.insert({map_name, {input}});
}

void InputMap::_remove_input_from_map(const std::string &map_name, const InputMap::Input &input) {
	auto iterator = mapped_inputs.find(map_name);

	if (iterator != mapped_inputs.end()) {
		auto input_iterator = std::find(iterator->second.begin(), iterator->second.end(), input);
		if (input_iterator != iterator->second.end())
			iterator->second.erase(input_iterator);
	}
}

constexpr float InputMap::_get_input_strength(const InputMap::Input &input) {
	return _get_event_info(input).strength;
}

float InputMap::_get_input_map_strength(const std::string &map_name) {
	auto iterator = mapped_inputs.find(map_name);
	if (iterator == mapped_inputs.end())
		return 0.0f;

	float strongest_input = 0.0f;
	for (const auto &input: iterator->second) {
		float input_strength = _get_input_strength(input);
		if (input_strength > strongest_input)
			strongest_input = input_strength;
	}

	return strongest_input;
}

void InputMap::add_key_to_input_map(const std::string &map_name, const SDL_Scancode scancode) {
	_add_input_to_map(map_name, _get_input_from_key(scancode));
}

void InputMap::add_key_to_input_map(const std::string &map_name, const SDL_KeyCode key_code) {
	_add_input_to_map(map_name, _get_input_from_key(key_code));
}

void InputMap::remove_key_from_input_map(const std::string &map_name, const SDL_KeyCode key_code) {
	_remove_input_from_map(map_name, _get_input_from_key(key_code));
}

void InputMap::clear_input_map(const std::string &map_name) {
	auto iterator = mapped_inputs.find(map_name);
	if (iterator != mapped_inputs.end())
		mapped_inputs.erase(iterator);
}


bool InputMap::is_action_pressed(const std::string &map_name, const bool allow_echo) {
	auto iterator = mapped_inputs.find(map_name);
	if (iterator == mapped_inputs.end())
		return false;

	for (const auto &input: iterator->second) {
		InputMap::KeyInputEvent key_input_event = _get_event_info(input);

		if (!allow_echo && key_input_event.repeat != 0)
			continue;

		if (!key_input_event.failed && key_input_event.same && key_input_event.holding)
			return true;
	}

	return false;
}

bool InputMap::is_action_just_pressed(const std::string &map_name, const bool allow_echo) {
	auto iterator = mapped_inputs.find(map_name);
	if (iterator == mapped_inputs.end())
		return false;

	for (const auto &input: iterator->second) {
		InputMap::KeyInputEvent key_input_event = _get_event_info(input);

		if (!allow_echo && key_input_event.repeat != 0)
			continue;

		if (!key_input_event.failed && key_input_event.same && key_input_event.holding && key_input_event.repeat != 0)
			return true;
	}

	return false;
}

bool InputMap::is_action_released(const std::string &map_name, const bool allow_echo) {
	auto iterator = mapped_inputs.find(map_name);
	if (iterator == mapped_inputs.end())
		return false;

	for (const auto &input: iterator->second) {
		InputMap::KeyInputEvent key_input_event = _get_event_info(input);

		if (!allow_echo && key_input_event.repeat != 0)
			continue;

		if (!key_input_event.failed && key_input_event.same && !key_input_event.holding && key_input_event.repeat != 0)
			return true;
	}

	return false;
}

float InputMap::get_input_strength(const std::string &input_map_name) {
	return _get_input_map_strength(input_map_name);
}

float InputMap::get_input_axis(
	    const std::string &negative_x_map,
	    const std::string &positive_x_map) {
	const float negative_input_strength = _get_input_map_strength(negative_x_map);
	const float positive_input_strength = _get_input_map_strength(positive_x_map);
	return positive_input_strength - negative_input_strength;
}

Vector2 InputMap::get_input_vector(
	    const std::string &negative_x_map_name,
	    const std::string &positive_x_map_name,
	    const std::string &negative_y_map_name,
	    const std::string &positive_y_map_name) {
	const float x_input_axis = get_input_axis(negative_x_map_name, positive_x_map_name);
	const float y_input_axis = get_input_axis(negative_y_map_name, positive_y_map_name);
	return Vector2(x_input_axis, y_input_axis).normalized();
}

bool InputMap::is_action_active(const std::string &map_name) {
	auto iterator = mapped_inputs.find(map_name);
	if (iterator == mapped_inputs.end())
		return false;

	for (const auto &input: iterator->second) {
		InputMap::KeyInputEvent key_input_event = _get_event_info(input);
		if (!key_input_event.failed && key_input_event.same)
			return true;
	}

	return false;
}
