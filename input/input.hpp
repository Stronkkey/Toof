/*  This file is part of the Toof Engine. */
/** @file input.hpp */
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
#pragma once

#include <core/math/vector2.hpp>

#include <unordered_set>
#include <unordered_map>
#include <memory>

#include <SDL_keyboard.h>
#include <SDL_events.h>

namespace Toof {

struct InputProxy;
class InputMap;
class InputEvent;

class Input {

private:
	std::unordered_set<SDL_Keycode> keys_pressed;
	std::unordered_set<SDL_Scancode> physical_keys_pressed;
	std::unique_ptr<InputMap> input_map;
	const uint64_t *process_frame_count, *render_frame_count;
	Vector2f mouse_position;

	struct ActionState {
		uint64_t pressed_render_frame = -1;
		uint64_t pressed_process_frame = -1;
		uint64_t released_render_frame = -1;
		uint64_t released_process_frame = -1;
		bool api_pressed = false;
		bool pressed = false;

		float api_strength = 0.0;
		float strength = 0.0f;
	};

	std::unordered_map<String, ActionState> action_states;

	void _update_action_with_event(const String &action_name, const std::shared_ptr<InputEvent> &input_event);
	void _flush_buffered_inputs();

	std::shared_ptr<InputEvent> _process_keyboard_event(const SDL_Event *event);
public:
	Input(const uint64_t *process_frame_count = nullptr, const uint64_t *render_frame_count = nullptr);
	~Input();

	std::shared_ptr<InputEvent> process_event(const SDL_Event *event);
	const std::unordered_map<String, ActionState> &get_action_states() const;

	const std::unique_ptr<InputMap> &get_input_map() const;

	bool is_anything_pressed() const;
	bool is_key_pressed(const SDL_Keycode keycode) const;
	bool is_physical_key_pressed(const SDL_Scancode scan_code) const;

	bool is_action_pressed(const String &action_name) const;
	bool is_action_just_pressed(const String &action_name) const;
	bool is_action_just_released(const String &action_name) const;
	float get_action_strength(const String &action_name) const;

	float get_axis(const String &negative_action_name, const String &positive_action_name) const;
	Vector2f get_vector(const String &negative_x_action_name, const String &positive_x_action_name, const String &negative_y_action_name, const String &positive_y_action_name) const;

	void action_press(const String &action_name, const float strength = 1.0f);
	void action_release(const String &action_name);
};

}