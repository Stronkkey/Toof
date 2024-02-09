#pragma once

#include <SDL_keycode.h>
#include <SDL_events.h>

#include <string>
#include <unordered_map>
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

	struct Action {
		float deadzone;
	};

private:
	std::unordered_map<std::string, std::vector<Input>> mapped_inputs;
	SDL_Event *event;

	constexpr KeyInputEvent _get_event_info(const Input &input);

	constexpr Input _get_input_from_key(const SDL_KeyCode key_code);
	constexpr Input _get_input_from_key(const SDL_Scancode scancode);
 
	void _add_input_to_map(const std::string &map_name, const Input &input);
	void _remove_input_from_map(const std::string &map_name, const Input &input);

	constexpr float _get_input_strength(const Input &input);
	float _get_input_map_strength(const std::string &map_name);

public:
	InputMap(SDL_Event *event);
	~InputMap();

	void add_key_to_input_map(const std::string &map_name, const SDL_Scancode scancode);
	void add_key_to_input_map(const std::string &map_name, const SDL_KeyCode key_code);

	void remove_key_from_input_map(const std::string &key_name, const SDL_Scancode scancode);
	void remove_key_from_input_map(const std::string &key_name, const SDL_KeyCode key_code);

	void clear_input_map(const std::string &map_name);

	bool is_action_pressed(const std::string &map_name, const bool allow_echo = false);
	bool is_action_just_pressed(const std::string &map_name, const bool allow_echo = false);
	bool is_action_released(const std::string &map_name, const bool allow_echo = false);

	float get_input_strength(const std::string &input_map_name);
	float get_input_axis(const std::string &negative_x_map, const std::string &positive_x_map);
	
	Vector2 get_input_vector(
	    const std::string &negative_x_map_name,
	    const std::string &positive_x_map_name,
	    const std::string &negative_y_map_name,
	    const std::string &positive_y_map_name);

	bool is_action_active(const std::string &map_name);
};

constexpr bool InputMap::Input::operator==(const InputMap::Input &right) const {
	switch (key_input_type) {
		case KEY_INPUT_TYPE_KEYSYM:
			return key_sym == right.key_sym;
		case KEY_INPUT_TYPE_SCANCODE:
			return scan_code == right.scan_code;
		default:
			return false;
	}
}

constexpr InputMap::KeyInputEvent InputMap::_get_event_info(const InputMap::Input &input) {
	InputMap::KeyInputEvent key_input_event;
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

constexpr InputMap::Input InputMap::_get_input_from_key(const SDL_KeyCode key_code) {
	InputMap::Input input;
	input.key_input_type = KEY_INPUT_TYPE_KEYSYM;
	input.key_sym = key_code;
	return input;
}

constexpr InputMap::Input InputMap::_get_input_from_key(const SDL_Scancode scancode) {
	InputMap::Input input;
	input.key_input_type = KEY_INPUT_TYPE_SCANCODE;
	input.scan_code = scancode;
	return input;
}

}
