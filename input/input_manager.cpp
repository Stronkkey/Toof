#include <core/math/vector2.hpp>
#include <input/input_manager.hpp>

#include <algorithm>

using namespace sdl;

std::unordered_map<std::string, std::vector<InputManager::Input>> InputManager::mapped_inputs = {};

void InputManager::_add_input_to_map(const std::string &map_name, const InputManager::Input &input) {
	auto iterator = mapped_inputs.find(map_name);

	if (iterator != mapped_inputs.end())
		iterator->second.push_back(input);
	else
		mapped_inputs.insert({map_name, {input}});
}

void InputManager::_remove_input_from_map(const std::string &map_name, const InputManager::Input &input) {
	auto iterator = mapped_inputs.find(map_name);

	if (iterator != mapped_inputs.end()) {
		auto input_iterator = std::find(iterator->second.begin(), iterator->second.end(), input);
		if (input_iterator != iterator->second.end())
			iterator->second.erase(input_iterator);
	}
}

constexpr float InputManager::_get_input_strength(const SDL_Event *event, const InputManager::Input &input) {
	return _get_event_info(event, input).strength;
}

float InputManager::_get_input_map_strength(const std::string &map_name, const SDL_Event *event) {
	auto iterator = mapped_inputs.find(map_name);
	if (iterator == mapped_inputs.end())
		return 0.0f;

	float strongest_input = 0.0f;
	for (const auto &input: iterator->second) {
		float input_strength = _get_input_strength(event, input);
		if (input_strength > strongest_input)
			strongest_input = input_strength;
	}

	return strongest_input;
}

void InputManager::set_input_map(const std::string &map_name, std::vector<InputManager::Input> &inputs) {
	mapped_inputs.insert({map_name, inputs});
}

void InputManager::add_key_to_input_map(const std::string &map_name, const InputManager::Input &input) {
	_add_input_to_map(map_name, input);
}

void InputManager::add_key_to_input_map(const std::string &map_name, const SDL_Scancode scancode) {
	_add_input_to_map(map_name, _get_input_from_key(scancode));
}

void InputManager::add_key_to_input_map(const std::string &map_name, const SDL_KeyCode key_code) {
	_add_input_to_map(map_name, _get_input_from_key(key_code));
}

void InputManager::remove_key_from_input_map(const std::string &map_name, const InputManager::Input &input) {
	_remove_input_from_map(map_name, input);
}

void InputManager::remove_key_from_input_map(const std::string &map_name, const SDL_KeyCode key_code) {
	_remove_input_from_map(map_name, _get_input_from_key(key_code));
}

void InputManager::clear_input_map(const std::string &map_name) {
	auto iterator = mapped_inputs.find(map_name);
	if (iterator != mapped_inputs.end())
		mapped_inputs.erase(iterator);
}


bool InputManager::input_is_action_pressed(const std::string &map_name, const SDL_Event *event) {
	auto iterator = mapped_inputs.find(map_name);
	if (iterator == mapped_inputs.end())
		return false;

	for (const auto &input: iterator->second) {
		InputManager::KeyInputEvent key_input_event = _get_event_info(event, input);
		if (!key_input_event.failed && key_input_event.same && key_input_event.holding)
			return true;
	}

	return false;
}

bool InputManager::input_is_action_just_pressed(const std::string &map_name, const SDL_Event *event) {
	auto iterator = mapped_inputs.find(map_name);
	if (iterator == mapped_inputs.end())
		return false;

	for (const auto &input: iterator->second) {
		InputManager::KeyInputEvent key_input_event = _get_event_info(event, input);
		if (!key_input_event.failed && key_input_event.same && key_input_event.holding && key_input_event.repeat != 0)
			return true;
	}

	return false;
}

bool InputManager::input_is_action_released(const std::string &map_name, const SDL_Event *event) {
	auto iterator = mapped_inputs.find(map_name);
	if (iterator == mapped_inputs.end())
		return false;

	for (const auto &input: iterator->second) {
		InputManager::KeyInputEvent key_input_event = _get_event_info(event, input);
		if (!key_input_event.failed && key_input_event.same && !key_input_event.holding && key_input_event.repeat != 0)
			return true;
	}

	return false;
}

float InputManager::get_input_strength(const std::string &input_map_name, const SDL_Event *event) {
	return _get_input_map_strength(input_map_name, event);
}

float InputManager::get_input_axis(
	        const std::string &negative_x_map,
	        const std::string &positive_x_map,
	        const SDL_Event *event) {
	const float negative_input_strength = _get_input_map_strength(negative_x_map, event);
	const float positive_input_strength = _get_input_map_strength(positive_x_map, event);
	return positive_input_strength - negative_input_strength;
}

Vector2 InputManager::get_input_vector(
	    const std::string &negative_x_map_name,
	    const std::string &positive_x_map_name,
	    const std::string &negative_y_map_name,
	    const std::string &positive_y_map_name,
	    const SDL_Event *event) {
	const float x_input_axis = get_input_axis(negative_x_map_name, positive_x_map_name, event);
	const float y_input_axis = get_input_axis(negative_y_map_name, positive_y_map_name, event);
	return Vector2(x_input_axis, y_input_axis).normalized();
}

bool InputManager::input_is_action_pressed_or_released(const std::string &map_name, const SDL_Event *event) {
	auto iterator = mapped_inputs.find(map_name);
	if (iterator == mapped_inputs.end())
		return false;

	for (const auto &input: iterator->second) {
		InputManager::KeyInputEvent key_input_event = _get_event_info(event, input);
		if (key_input_event.same)
			return true;
	}

	return false;
}
