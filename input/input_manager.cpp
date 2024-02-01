#include <core/math/vector2.hpp>
#include <input/input_manager.hpp>

#include <algorithm>

using namespace sdl;

bool InputManager::Input::operator==(const InputManager::Input &right) const {
	switch (key_input_type) {
		case KEY_INPUT_TYPE_KEYSYM:
			return key_sym == right.key_sym;
		case KEY_INPUT_TYPE_SCANCODE:
			return scan_code == right.scan_code;
		default:
			return false;
	}

	return false;
}

std::unordered_map<std::string, std::vector<InputManager::Input>> InputManager::mapped_inputs = {};

InputManager::KeyInputEvent InputManager::_get_event_info(const SDL_Event *event, const InputManager::Input &input) {
	InputManager::KeyInputEvent key_input_event;
	key_input_event.failed = false;

	bool is_key_event = event->type == SDL_KEYDOWN || event->type == SDL_KEYUP;
	if (is_key_event) {
		key_input_event.repeat = event->key.repeat;
		key_input_event.holding = event->type == SDL_KEYDOWN;

		if (input.key_input_type == KEY_INPUT_TYPE_KEYSYM)
			key_input_event.same = event->key.keysym.sym == input.key_sym;
		else if (input.key_input_type == KEY_INPUT_TYPE_SCANCODE)
			key_input_event.same = event->key.keysym.scancode == input.scan_code;

		key_input_event.strength = key_input_event.same && key_input_event.holding ? 1.0f : 0.0f;
	} else
		key_input_event.failed = true;

	return key_input_event;
}

InputManager::Input InputManager::_get_input_from_key(const SDL_KeyCode key_code) {
	InputManager::Input input;
	input.key_input_type = KEY_INPUT_TYPE_KEYSYM;
	input.key_sym = key_code;
	return input;
}

InputManager::Input InputManager::_get_input_from_key(const SDL_Scancode scancode) {
	InputManager::Input input;
	input.key_input_type = KEY_INPUT_TYPE_SCANCODE;
	input.scan_code = scancode;
	return input;
}

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

float InputManager::_get_input_strength(const SDL_Event *event, const InputManager::Input &input) {
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

InputManager::EventInputType InputManager::get_event_type(const SDL_Event *event) {
	switch (event->type) {
		case SDL_AUDIODEVICEADDED:
			return EVENT_INPUT_TYPE_AUDIO_DEVICE;
		case SDL_AUDIODEVICEREMOVED:
			return EVENT_INPUT_TYPE_AUDIO_DEVICE;
		case SDL_CONTROLLERAXISMOTION:
			return EVENT_INPUT_TYPE_CONTROLLER_AXIS;
		case SDL_CONTROLLERBUTTONDOWN:
			return EVENT_INPUT_TYPE_CONTROLLER_BUTTON;
		case SDL_CONTROLLERBUTTONUP:
			return EVENT_INPUT_TYPE_CONTROLLER_BUTTON;
		case SDL_CONTROLLERDEVICEADDED:
			return EVENT_INPUT_TYPE_CONTROLLER_DEVICE;
		case SDL_CONTROLLERDEVICEREMOVED:
			return EVENT_INPUT_TYPE_CONTROLLER_DEVICE;
		case SDL_CONTROLLERDEVICEREMAPPED:
			return EVENT_INPUT_TYPE_CONTROLLER_DEVICE;
		case SDL_DOLLARGESTURE:
			return EVENT_INPUT_TYPE_DOLLAR_GESTURE;
		case SDL_DOLLARRECORD:
			return EVENT_INPUT_TYPE_DOLLAR_GESTURE;
		case SDL_DROPFILE:
			return EVENT_INPUT_TYPE_DROP;
		case SDL_DROPTEXT:
			return EVENT_INPUT_TYPE_DROP;
		case SDL_DROPBEGIN:
			return EVENT_INPUT_TYPE_DROP;
		case SDL_DROPCOMPLETE:
			return EVENT_INPUT_TYPE_DROP;
		case SDL_FINGERMOTION:
			return EVENT_INPUT_TYPE_TOUCH_FINGER;
		case SDL_FINGERDOWN:
			return EVENT_INPUT_TYPE_TOUCH_FINGER;
		case SDL_FINGERUP:
			return EVENT_INPUT_TYPE_TOUCH_FINGER;
		case SDL_KEYDOWN:
			return EVENT_INPUT_TYPE_KEYBOARD;
		case SDL_KEYUP:
			return EVENT_INPUT_TYPE_KEYBOARD;
		case SDL_JOYAXISMOTION:
			return EVENT_INPUT_TYPE_JOY_AXIS;
		case SDL_JOYBALLMOTION:
			return EVENT_INPUT_TYPE_JOY_BALL;
		case SDL_JOYHATMOTION:
			return EVENT_INPUT_TYPE_JOY_HAT;
		case SDL_JOYBUTTONDOWN:
			return EVENT_INPUT_TYPE_JOY_BUTTON;
		case SDL_JOYBUTTONUP:
			return EVENT_INPUT_TYPE_JOY_BUTTON;
		case SDL_JOYDEVICEADDED:
			return EVENT_INPUT_TYPE_JOY_DEVICE;
		case SDL_JOYDEVICEREMOVED:
			return EVENT_INPUT_TYPE_JOY_DEVICE;
		case SDL_MOUSEMOTION:
			return EVENT_INPUT_TYPE_MOUSE_MOTION;
		case SDL_MOUSEBUTTONDOWN:
			return EVENT_INPUT_TYPE_MOUSE_BUTTON;
		case SDL_MOUSEBUTTONUP:
			return EVENT_INPUT_TYPE_MOUSE_BUTTON;
		case SDL_MOUSEWHEEL:
			return EVENT_INPUT_TYPE_MOUSE_WHEEL;
		case SDL_MULTIGESTURE:
			return EVENT_INPUT_TYPE_MULTI_GESTURE;
		case SDL_QUIT:
			return EVENT_INPUT_TYPE_QUIT;
		case SDL_SYSWMEVENT:
			return EVENT_INPUT_TYPE_SYSWM;
		case SDL_TEXTEDITING:
			return EVENT_INPUT_TYPE_TEXT_EDITING;
		case SDL_TEXTINPUT:
			return EVENT_INPUT_TYPE_TEXT_INPUT;
		case SDL_USEREVENT:
			return EVENT_INPUT_TYPE_USER;
		case SDL_WINDOWEVENT:
			return EVENT_INPUT_TYPE_WINDOW;
	}
	return EVENT_INPUT_TYPE_NONE;
}