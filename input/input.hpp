#pragma once

#include <core/math/vector2.hpp>

#include <unordered_set>
#include <unordered_map>
#include <set>
#include <vector>
#include <memory>

#include <SDL_keyboard.h>
#include <SDL_events.h>

namespace sdl {

struct InputProxy;
class InputMap;
class InputEvent;

class Input {

private:
	static constexpr uint64_t MAX_EVENT = 32;

	std::unordered_set<SDL_Keycode> keys_pressed;
	std::unordered_set<SDL_Scancode> physical_keys_pressed;
	std::unique_ptr<InputMap> input_map;
	const uint64_t *process_frame_count, *render_frame_count;
	Vector2 mouse_position;

	struct ActionState {
		uint64_t pressed_render_frame = -1;
		uint64_t pressed_process_frame = -1;
		uint64_t released_render_frame = -1;
		uint64_t released_process_frame = -1;
		bool exact = true;
		bool api_pressed = false;
		bool pressed = false;

		struct DeviceState {
			bool pressed[MAX_EVENT] = { false };
			float strength[MAX_EVENT] = { 0.0 };
			float raw_strength[MAX_EVENT] = { 0.0 };
		};

		float api_strength = 0.0;
		std::unordered_map<int, DeviceState> device_states;

		float strength = 0.0f;
		float raw_strength = 0.0f;
	};

	std::unordered_map<std::string, ActionState> action_states;

	bool emulate_touch_from_mouse = false;
	bool emulate_mouse_from_touch = false;
	bool use_input_buffering = false;
	bool use_accumulated_input = true;

	std::set<InputProxy, std::equal_to<InputProxy>> buffered_inputs;

	void _update_action_cache(const std::string &action_name, ActionState &action_state);
	std::unique_ptr<InputEvent> _process_keyboard_event(const SDL_Event *event);
public:
	Input(const uint64_t *process_frame_count = nullptr, const uint64_t *render_frame_count = nullptr);
	~Input();

	std::unique_ptr<InputEvent> process_event(const SDL_Event *event);

	const std::unique_ptr<InputMap> &get_input_map() const;

	bool is_anything_pressed() const;
	bool is_key_pressed(const SDL_Keycode keycode) const;
	bool is_physical_key_pressed(const SDL_Scancode scan_code) const;

	bool is_action_pressed(const std::string &action_name, const bool exact = false) const;
	bool is_action_just_pressed(const std::string &action_name, const bool exact = false) const;
	bool is_action_just_released(const std::string &action_name, const bool exact = false) const;
	float get_action_strength(const std::string &action_name, const bool exact = false) const;
	float get_action_raw_strength(const std::string &action_name, const bool exact = false) const;

	float get_axis(const std::string &negative_action_name, const std::string &positive_action_name) const;
	Vector2 get_vector(const std::string &negative_x_action_name, const std::string &positive_x_action_name, const std::string &negative_y_action_name, const std::string &positive_y_action_name, float deadzone = -1.0f) const;

	void action_press(const std::string &action_name, const float strength = 1.0f);
	void action_release(const std::string &action_name);
};

}