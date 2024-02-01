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
	};

	struct Input {
		KeyInputType key_input_type;

		union {
			SDL_KeyCode key_sym;
			SDL_Scancode scan_code;
		};

		bool operator==(const Input &right) const;
	};

private:
	InputManager() {}
	~InputManager() {}

	static std::unordered_map<std::string, std::vector<Input>> mapped_inputs;

	static KeyInputEvent _get_event_info(const SDL_Event *event, const Input &input);

	static Input _get_input_from_key(const SDL_KeyCode key_code);
	static Input _get_input_from_key(const SDL_Scancode scancode);
 
	static void _add_input_to_map(const std::string &map_name, const Input &input);
	static void _remove_input_from_map(const std::string &map_name, const Input &input);

	static float _get_input_strength(const SDL_Event *event, const Input &input);
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
	static EventInputType get_event_type(const SDL_Event *event);
};

}
