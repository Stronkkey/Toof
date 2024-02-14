#include <input/input_event.hpp>
#include <input/input.hpp>
#include <input/input_map.hpp>

using InputEvent = sdl::InputEvent;
using InputEventKeyboard = sdl::InputEventKeyboard;
using InputEventAction = sdl::InputEventAction;

bool InputEvent::is_action(const std::string &action_name) const {
	return input ? input->get_input_map()->event_is_action(this, action_name) : false;
}

bool InputEvent::is_action_pressed(const std::string &action_name, const bool allow_echo, const bool exact_match) const {
	(void)allow_echo;
	return input ? input->is_action_pressed(action_name, exact_match) : false;
}

bool InputEvent::is_action_released(const std::string &action_name, const bool allow_echo, const bool exact_match) const {
	return !is_action_pressed(action_name, allow_echo, exact_match);
}

void InputEvent::fill_with_event(const SDL_Event *event) {
	_fill_with_event(event);
}

bool InputEvent::same_input(const InputEvent *input_event) const {
	if (!input_event || type != input_event->type)
		return false;

	return pressed && _same_input(input_event);
}

bool InputEventKeyboard::_same_input(const InputEvent *input_event) const {
	const InputEventKeyboard *input_event_keyboard = static_cast<const InputEventKeyboard*>(input_event);
	return key_code == input_event_keyboard->key_code
	       && scan_code == input_event_keyboard->scan_code
	       && modifiers == input_event_keyboard->modifiers;
}

void InputEventKeyboard::_fill_with_event(const SDL_Event *event) {
	if (get_event_type(event) != EVENT_INPUT_TYPE_KEYBOARD)
		return;

	modifiers = event->key.keysym.mod;
	scan_code = event->key.keysym.scancode;
	key_code = event->key.keysym.sym;
	time_stamp = event->key.timestamp;
}

bool InputEventAction::_same_input(const InputEvent *input_event) const {
	const InputEventAction *input_event_action = static_cast<const InputEventAction*>(input_event);
	return action_name == input_event_action->action_name && strength == input_event_action->strength;
}