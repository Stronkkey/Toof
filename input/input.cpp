#include <input/input.hpp>
#include <input/input_map.hpp>

#include <algorithm>

using Input = sdl::Input;
using InputEvent = sdl::InputEvent;

Input::Input(const uint64_t *process_frame_count, const uint64_t *render_frame_count):
            keys_pressed(),
            physical_keys_pressed(),
            process_frame_count(process_frame_count),
            render_frame_count(render_frame_count),
            mouse_position(),
            action_states(),
            buffered_inputs() {
	input_map = std::make_unique<InputMap>();
}

Input::~Input() {
}

const std::unique_ptr<sdl::InputMap> &Input::get_input_map() const {
	return input_map;
}

void Input::_update_action_cache(const std::string &action_name, ActionState &action_state) {
	action_state.pressed = false;
	action_state.strength = 0.0f;
	action_state.raw_strength = 0.0f;

	size_t max_event = input_map->action_get_events(action_name).size();
	for (const auto &iterator: action_state.device_states) {
		const ActionState::DeviceState &device_state = iterator.second;
		for (size_t i = 0; i < max_event; i++) {
			action_state.pressed = action_state.pressed || device_state.pressed[i];
			action_state.strength = std::max(action_state.strength, device_state.strength[i]);
			action_state.raw_strength = std::max(action_state.raw_strength, device_state.raw_strength[i]);
		}
	}

	if (!action_state.api_pressed)
		return;

	action_state.pressed = true;
	action_state.strength = std::max(action_state.strength, action_state.api_strength);
	action_state.raw_strength = std::max(action_state.raw_strength, action_state.api_strength); // Use the strength as raw_strength for API-pressed states.
}

std::unique_ptr<InputEvent> Input::_process_keyboard_event(const SDL_Event *event) {
	const bool pressed = event->key.type == SDL_KEYDOWN;
	const auto &physical_key_iterator = physical_keys_pressed.find(event->key.keysym.scancode);
	const auto &key_iterator = keys_pressed.find(event->key.keysym.sym);

	if (physical_key_iterator == physical_keys_pressed.end())
		physical_keys_pressed.insert(event->key.keysym.scancode);
	else if (!pressed)
		physical_keys_pressed.erase(event->key.keysym.scancode);

	if (key_iterator == keys_pressed.end())
		keys_pressed.insert(event->key.keysym.sym);
	else if (!pressed)
		keys_pressed.erase(key_iterator);

	auto input_event = std::make_unique<InputEventKeyboard>();
	input_event->fill_with_event(event);
	input_event->set_input(this);
	return input_event;
}

std::unique_ptr<InputEvent> Input::process_event(const SDL_Event *event) {
	EventInputType event_input_type = get_event_type(event);

	switch (event_input_type) {
		case EVENT_INPUT_TYPE_KEYBOARD:
			return _process_keyboard_event(event);
			break;
		default:
			break;
	}

	return std::unique_ptr<InputEvent>();
}

bool Input::is_anything_pressed() const {
	if (!keys_pressed.empty() || !physical_keys_pressed.empty())
		return true;

	for (const auto &iterator: action_states)
		if (iterator.second.pressed)
			return true;

	return false;
}

bool Input::is_key_pressed(const SDL_Keycode key_code) const {
	return keys_pressed.count(key_code) == 1;
}

bool Input::is_physical_key_pressed(const SDL_Scancode scan_code) const {
	return physical_keys_pressed.count(scan_code) == 1;
}

bool Input::is_action_pressed(const std::string &action_name, const bool exact) const {
	if (!input_map->has_action(action_name))
		return false;

	const auto &iterator = action_states.find(action_name);
	if (iterator == action_states.end())
		return false;
	return iterator->second.pressed && (exact ? iterator->second.exact : true);
}

bool Input::is_action_just_pressed(const std::string &action_name, const bool exact) const {
	if (!input_map->has_action(action_name))
		return false;

	const auto &iterator = action_states.find(action_name);
	if (iterator == action_states.end() || (exact && !iterator->second.exact))
		return false;

	const ActionState &action_state = iterator->second;
	if (process_frame_count && !render_frame_count)
		return action_state.pressed_process_frame == *process_frame_count;
	else if (!process_frame_count && render_frame_count)
		return action_state.pressed_render_frame == *render_frame_count;
	else if (process_frame_count && render_frame_count)
		return action_state.pressed_process_frame == *process_frame_count;

	return action_state.pressed && (exact ? action_state.exact : true);
}

bool Input::is_action_just_released(const std::string &action_name, const bool exact) const {
	if (!input_map->has_action(action_name))
		return false;

	const auto &iterator = action_states.find(action_name);
	if (iterator == action_states.end() || (exact && !iterator->second.exact))
		return false;

	const ActionState &action_state = iterator->second;
	if (process_frame_count && !render_frame_count)
		return action_state.released_process_frame == *process_frame_count;
	else if (!process_frame_count && render_frame_count)
		return action_state.released_render_frame == *render_frame_count;
	else if (process_frame_count && render_frame_count)
		return action_state.released_process_frame == *process_frame_count;

	return !action_state.pressed && (exact ? action_state.exact : true);
}

float Input::get_action_strength(const std::string &action_name, const bool exact) const {
	if (!input_map->has_action(action_name))
		return 0.0f;

	const auto &iterator = action_states.find(action_name);
	if (iterator == action_states.end() || (exact && !iterator->second.exact))
		return 0.0f;

	return iterator->second.strength;
}

float Input::get_action_raw_strength(const std::string &action_name, const bool exact) const {
	if (!input_map->has_action(action_name))
		return 0.0f;

	const auto &iterator = action_states.find(action_name);
	if (iterator == action_states.end() || (exact && !iterator->second.exact))
		return 0.0f;

	return iterator->second.raw_strength;
}

float Input::get_axis(const std::string &negative_action_name, const std::string &positive_action_name) const {
	return get_action_strength(positive_action_name) - get_action_strength(negative_action_name);
}

sdl::Vector2 Input::get_vector(const std::string &negative_x_action_name, const std::string &positive_x_action_name, const std::string &negative_y_action_name, const std::string &positive_y_action_name, float deadzone) const {
	Vector2 vector = Vector2(
			get_action_raw_strength(positive_x_action_name) - get_action_raw_strength(negative_x_action_name),
			get_action_raw_strength(positive_y_action_name) - get_action_raw_strength(negative_y_action_name));

	if (deadzone < 0.0f) {
		// If the deadzone isn't specified, get it from the average of the actions.
		deadzone = 0.25 *
				(input_map->action_get_deadzone(positive_x_action_name) +
						input_map->action_get_deadzone(negative_x_action_name) +
						input_map->action_get_deadzone(positive_y_action_name) +
						input_map->action_get_deadzone(negative_y_action_name));
	}

	// Circular length limiting and deadzone.
	float length = vector.length();
	if (length <= deadzone) 
		return Vector2::ZERO;
	else if (length > 1.0f)
		return vector / length;
	else
		// Inverse lerp length to map (p_deadzone, 1) to (0, 1).
		return vector;// * (Math::inverse_lerp(p_deadzone, 1.0f, length) / length);
}

void Input::action_press(const std::string &action_name, const float strength) {
	if (!input_map->has_action(action_name))
		return;

	ActionState &action_state = action_states[action_name];

	if (!action_state.pressed) {
		if (process_frame_count)
			action_state.pressed_process_frame = *process_frame_count;
		if (render_frame_count)
			action_state.pressed_render_frame = *render_frame_count;
	}

	action_state.exact = true;
	action_state.api_pressed = true;
	action_state.api_strength = strength;
	_update_action_cache(action_name, action_state);
}

void Input::action_release(const std::string &action_name) {
	if (input_map->has_action(action_name))
		return;

	ActionState &action_state = action_states[action_name];

	action_state.pressed = false;
	action_state.strength = 0.0f;
	action_state.raw_strength = 0.0f;

	if (render_frame_count)
		action_state.released_render_frame = *render_frame_count;
	if (process_frame_count)
		action_state.released_process_frame = *process_frame_count;

	action_state.device_states.clear();
	action_state.exact = true;
	action_state.api_pressed = false;
	action_state.api_strength = 0.0f;
}
