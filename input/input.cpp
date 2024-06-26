/*  This file is part of the Toof Engine. */
/*
  BSD 3-Clause License

  Copyright (c) 2024-present, Stronkkey and Contributors

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
      list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <input/input.hpp>
#include <input/input_map.hpp>

#include <algorithm>

using Input = Toof::Input;
using InputEvent = Toof::InputEvent;

Input::Input(const uint64_t *process_frame_count, const uint64_t *render_frame_count):
            keys_pressed(),
            physical_keys_pressed(),
            process_frame_count(process_frame_count),
            render_frame_count(render_frame_count),
            mouse_position(),
            action_states() {
	input_map = std::make_unique<InputMap>();
}

Input::~Input() {
}

const std::unique_ptr<Toof::InputMap> &Input::get_input_map() const {
	return input_map;
}

void Input::_update_action_with_event(const String &action_name, const std::shared_ptr<InputEvent> &input_event) {
	ActionState &action_state = action_states[action_name];

	action_state.pressed = input_event->is_pressed();
	if (action_state.pressed) {
		if (process_frame_count)
			action_state.pressed_process_frame = *process_frame_count;

		if (render_frame_count)
			action_state.pressed_render_frame = *render_frame_count;
	} else {
		if (process_frame_count)
			action_state.released_process_frame = *process_frame_count;

		if (render_frame_count)
			action_state.released_render_frame = *render_frame_count;
	}

	action_state.strength = action_state.pressed;
}

std::shared_ptr<InputEvent> Input::_process_keyboard_event(const SDL_Event *event) {
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

std::shared_ptr<InputEvent> Input::process_event(const SDL_Event *event) {
	EventInputType event_input_type = get_event_type(event);
	std::shared_ptr<InputEvent> input_event;

	switch (event_input_type) {
		case EVENT_INPUT_TYPE_KEYBOARD:
			input_event = _process_keyboard_event(event);
			break;
		default:
			return std::shared_ptr<InputEvent>();
			break;
	}

	for (const auto &iterator: input_map->get_actions())
		if (iterator.second.inputs.count(input_event))
			_update_action_with_event(iterator.first, input_event);

	return input_event;
}

const std::unordered_map<Toof::String, Input::ActionState> &Input::get_action_states() const {
	return action_states;
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

bool Input::is_action_pressed(const String &action_name) const {
	if (!input_map->has_action(action_name))
		return false;

	const auto &iterator = action_states.find(action_name);
	const int b = action_states.count(action_name);
	(void)b;
	if (iterator == action_states.end())
		return false;
	return iterator->second.pressed;
}

bool Input::is_action_just_pressed(const String &action_name) const {
	if (!input_map->has_action(action_name))
		return false;

	const auto &iterator = action_states.find(action_name);
	if (iterator == action_states.end())
		return false;

	const ActionState &action_state = iterator->second;
	if (process_frame_count && !render_frame_count)
		return action_state.pressed_process_frame == *process_frame_count;
	else if (!process_frame_count && render_frame_count)
		return action_state.pressed_render_frame == *render_frame_count;
	else if (process_frame_count && render_frame_count)
		return action_state.pressed_process_frame == *process_frame_count;

	return action_state.pressed;
}

bool Input::is_action_just_released(const String &action_name) const {
	if (!input_map->has_action(action_name))
		return false;

	const auto &iterator = action_states.find(action_name);
	if (iterator == action_states.end())
		return false;

	const ActionState &action_state = iterator->second;
	if (process_frame_count && !render_frame_count)
		return action_state.released_process_frame == *process_frame_count;
	else if (!process_frame_count && render_frame_count)
		return action_state.released_render_frame == *render_frame_count;
	else if (process_frame_count && render_frame_count)
		return action_state.released_process_frame == *process_frame_count;

	return !action_state.pressed;
}

float Input::get_action_strength(const String &action_name) const {
	if (!input_map->has_action(action_name))
		return 0.0f;

	const auto &iterator = action_states.find(action_name);
	if (iterator == action_states.end())
		return 0.0f;

	return iterator->second.strength;
}

float Input::get_axis(const String &negative_action_name, const String &positive_action_name) const {
	return get_action_strength(negative_action_name) - get_action_strength(positive_action_name);
}

Toof::Vector2f Input::get_vector(const String &negative_x_action_name, const String &positive_x_action_name, const String &negative_y_action_name, const String &positive_y_action_name) const {
	Vector2f vector = Vector2f(
	        get_action_strength(positive_x_action_name) - get_action_strength(negative_x_action_name),
	        get_action_strength(positive_y_action_name) - get_action_strength(negative_y_action_name));
	return vector.normalized();
}

void Input::action_press(const String &action_name, const float strength) {
	if (!input_map->has_action(action_name))
		return;

	ActionState &action_state = action_states[action_name];

	if (!action_state.pressed) {
		if (process_frame_count)
			action_state.pressed_process_frame = *process_frame_count;

		if (render_frame_count)
			action_state.pressed_render_frame = *render_frame_count;
	}

	action_state.api_pressed = true;
	action_state.api_strength = strength;

	action_state.pressed = std::max(action_state.pressed, action_state.api_pressed);
	action_state.strength = std::max(action_state.api_strength, action_state.strength);
}

void Input::action_release(const String &action_name) {
	if (input_map->has_action(action_name))
		return;

	ActionState &action_state = action_states[action_name];

	action_state.pressed = false;
	action_state.strength = 0.0f;

	if (render_frame_count)
		action_state.released_render_frame = *render_frame_count;
	if (process_frame_count)
		action_state.released_process_frame = *process_frame_count;

	action_state.api_pressed = false;
	action_state.api_strength = 0.0f;
}
