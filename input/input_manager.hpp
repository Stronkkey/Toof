#pragma once

#include <SDL_keycode.h>
#include <SDL_events.h>

#include <string>
#include <unordered_map>
#include <vector>

namespace sdl {

struct Vector2;

class InputManager {

private:
	enum KeyInputType {
		KEY_INPUT_TYPE_KEYSYM,
		KEY_INPUT_TYPE_SCANCODE,
		KEY_INPUT_TYPE_NONE
	};

	struct KeyInputEvent {
		bool failed;
		bool holding;
		bool same;
		float strength;
		uint8_t repeat;

		constexpr KeyInputEvent(): failed(false), holding(false), same(false), strength(0.0f), repeat(0) {}
	};

	struct Input {
		KeyInputType key_input_type;

		union {
			SDL_KeyCode key_sym;
			SDL_Scancode scan_code;
		};

		constexpr Input(): key_input_type(KEY_INPUT_TYPE_NONE), scan_code(SDL_SCANCODE_UNKNOWN) {}
		constexpr bool operator==(const Input &right) const;
	};

private:
	InputManager() {}
	~InputManager() {}

	static std::unordered_map<std::string, std::vector<Input>> mapped_inputs;

	constexpr static KeyInputEvent _get_event_info(const SDL_Event *event, const Input &input);

	constexpr static Input _get_input_from_key(const SDL_KeyCode key_code);
	constexpr static Input _get_input_from_key(const SDL_Scancode scancode);
 
	static void _add_input_to_map(const std::string &map_name, const Input &input);
	static void _remove_input_from_map(const std::string &map_name, const Input &input);

	constexpr static float _get_input_strength(const SDL_Event *event, const Input &input);
	static float _get_input_map_strength(const std::string &map_name, const SDL_Event *event);

public:
	enum EventInputType {
		EVENT_INPUT_TYPE_NONE = 0,
		EVENT_INPUT_TYPE_AUDIO_DEVICE,
		EVENT_INPUT_TYPE_CONTROLLER_AXIS,
		EVENT_INPUT_TYPE_CONTROLLER_BUTTON,
		EVENT_INPUT_TYPE_CONTROLLER_DEVICE,
		EVENT_INPUT_TYPE_DOLLAR_GESTURE,
		EVENT_INPUT_TYPE_DROP,
		EVENT_INPUT_TYPE_TOUCH_FINGER,
		EVENT_INPUT_TYPE_KEYBOARD,
		EVENT_INPUT_TYPE_JOY_AXIS,
		EVENT_INPUT_TYPE_JOY_BALL,
		EVENT_INPUT_TYPE_JOY_HAT,
		EVENT_INPUT_TYPE_JOY_BUTTON,
		EVENT_INPUT_TYPE_JOY_DEVICE,
		EVENT_INPUT_TYPE_MOUSE_MOTION,
		EVENT_INPUT_TYPE_MOUSE_BUTTON,
		EVENT_INPUT_TYPE_MOUSE_WHEEL,
		EVENT_INPUT_TYPE_MULTI_GESTURE,
		EVENT_INPUT_TYPE_QUIT,
		EVENT_INPUT_TYPE_SYSWM,
		EVENT_INPUT_TYPE_TEXT_EDITING,
		EVENT_INPUT_TYPE_TEXT_INPUT,
		EVENT_INPUT_TYPE_USER,
		EVENT_INPUT_TYPE_WINDOW,
	};

	static void set_input_map(const std::string &map_name, std::vector<Input> &inputs);

	static void add_key_to_input_map(const std::string &map_name, const Input &input);
	static void add_key_to_input_map(const std::string &map_name, const SDL_Scancode scancode);
	static void add_key_to_input_map(const std::string &map_name, const SDL_KeyCode key_code);

	static void remove_key_from_input_map(const std::string &key_name, const Input &input);
	static void remove_key_from_input_map(const std::string &key_name, const SDL_Scancode scancode);
	static void remove_key_from_input_map(const std::string &key_name, const SDL_KeyCode key_code);

	static void clear_input_map(const std::string &map_name);

	static bool input_is_action_pressed(const std::string &map_name, const SDL_Event *event);
	static bool input_is_action_just_pressed(const std::string &map_name, const SDL_Event *event);
	static bool input_is_action_released(const std::string &map_name, const SDL_Event *event);

	static float get_input_strength(const std::string &input_map_name, const SDL_Event *event);
	static float get_input_axis(
	    const std::string &negative_x_map,
	    const std::string &positive_x_map,
	    const SDL_Event *event);
	
	static Vector2 get_input_vector(
	    const std::string &negative_x_map_name,
	    const std::string &positive_x_map_name,
	    const std::string &negative_y_map_name,
	    const std::string &positive_y_map_name,
	    const SDL_Event *event);

	static bool input_is_action_pressed_or_released(const std::string &map_name, const SDL_Event *event);
	constexpr static EventInputType get_event_type(const SDL_Event *event);
};


constexpr bool InputManager::Input::operator==(const InputManager::Input &right) const {
	switch (key_input_type) {
		case KEY_INPUT_TYPE_KEYSYM:
			return key_sym == right.key_sym;
		case KEY_INPUT_TYPE_SCANCODE:
			return scan_code == right.scan_code;
		default:
			return false;
	}
}

constexpr InputManager::KeyInputEvent InputManager::_get_event_info(const SDL_Event *event, const InputManager::Input &input) {
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

constexpr InputManager::Input InputManager::_get_input_from_key(const SDL_KeyCode key_code) {
	InputManager::Input input;
	input.key_input_type = KEY_INPUT_TYPE_KEYSYM;
	input.key_sym = key_code;
	return input;
}

constexpr InputManager::Input InputManager::_get_input_from_key(const SDL_Scancode scancode) {
	InputManager::Input input;
	input.key_input_type = KEY_INPUT_TYPE_SCANCODE;
	input.scan_code = scancode;
	return input;
}

constexpr InputManager::EventInputType InputManager::get_event_type(const SDL_Event *event) {
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

}
