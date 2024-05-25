/*  This file is part of the Toof Engine. */
/** @file input_event.hpp */
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

#include <core/string/string_def.hpp>
#include <input/event_input_type.hpp>
#include <scene/resources/resource.hpp>

#include <memory>

namespace Toof {

class Input;

// Equal to EVENT_INPUT_TYPE_NONE
class InputEvent : public Resource {
private:
	const Input *input;

	virtual bool _same_input(const InputEvent*) const {
		return true;
	}

	virtual void _fill_with_event(const SDL_Event*) {
	}

protected:
	bool pressed;
	EventInputType type;

public:
	constexpr InputEvent(): input(nullptr), pressed(false), type(EVENT_INPUT_TYPE_NONE) {
	}

	constexpr void set_input(const Input *input) {
		this->input = input;
	}

	constexpr bool is_pressed() const {
		return pressed;
	}
	
	constexpr EventInputType get_type() const {
		return type;
	}

	bool is_action(const String &action_name) const;
	bool is_action_pressed(const String &action_name) const;
	bool is_action_released(const String &action_name) const;

	void fill_with_event(const SDL_Event *event);
	bool same_input(const InputEvent *input_event) const;
};

// Equal to EVENT_INPUT_TYPE_KEYBOARD
class InputEventKeyboard : public InputEvent {
private:
	SDL_Keycode key_code;
	SDL_Scancode scan_code;
	uint32_t time_stamp;
	uint16_t modifiers;

	void _fill_with_event(const SDL_Event *event) override;
	bool _same_input(const InputEvent *input_event) const override;
public:
	constexpr InputEventKeyboard(): key_code(SDLK_UNKNOWN), scan_code(SDL_SCANCODE_UNKNOWN), time_stamp(0), modifiers(0) {
		type = EVENT_INPUT_TYPE_KEYBOARD;
	}

	constexpr void set_keycode(const SDL_Keycode key_code) {
		this->key_code = key_code;
	}

	constexpr SDL_Keycode get_keycode() const {
		return key_code;
	}

	constexpr void set_scan_code(const SDL_Scancode scan_code) {
		this->scan_code = scan_code;
	}

	constexpr SDL_Scancode get_scan_code() const {
		return scan_code;
	}

	constexpr void set_time_stamp(const uint32_t time_stamp) {
		this->time_stamp = time_stamp;
	}

	constexpr uint32_t get_time_stamp() const {
		return time_stamp;
	}

	constexpr void set_modifiers(const uint16_t modifiers) {
		this->modifiers = modifiers;
	}

	constexpr uint16_t get_modifiers() const {
		return modifiers;
	}
};

// Equal to EVENT_INPUT_TYPE_USER << EVENT_INPUT_TYPE_WINDOW
class InputEventAction : public InputEvent {
private:
	String action_name;
	float strength;

	bool _same_input(const InputEvent *input_event) const override;
public:
	InputEventAction(): action_name(), strength(0.0f) {
		type = (EventInputType)(EVENT_INPUT_TYPE_USER << EVENT_INPUT_TYPE_WINDOW);
	}

	constexpr void set_pressed(const bool pressed) {
		this->pressed = pressed;
	}

	void set_action_name(const String &action_name) {
		this->action_name = action_name;
	}

	constexpr const String &get_action_name() const {
		return action_name;
	}

	constexpr void set_strength(const float strength) {
		this->strength = strength;
	}

	constexpr float get_strength() const {
		return strength;
	}
};

}
