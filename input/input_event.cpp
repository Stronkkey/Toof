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
#include <input/input_event.hpp>
#include <input/input.hpp>
#include <input/input_map.hpp>

using InputEvent = Toof::InputEvent;
using InputEventKeyboard = Toof::InputEventKeyboard;
using InputEventAction = Toof::InputEventAction;

bool InputEvent::is_action(const String &action_name) const {
	return input ? input->get_input_map()->event_is_action(this, action_name) : false;
}

bool InputEvent::is_action_pressed(const String &action_name) const {
	return input ? input->is_action_pressed(action_name) : false;
}

bool InputEvent::is_action_released(const String &action_name) const {
	return !is_action_pressed(action_name);
}

void InputEvent::fill_with_event(const SDL_Event *event) {
	_fill_with_event(event);
}

bool InputEvent::same_input(const InputEvent *input_event) const {
	if (!input_event || type != input_event->type)
		return false;

	return _same_input(input_event);
}

bool InputEventKeyboard::_same_input(const InputEvent *input_event) const {
	const InputEventKeyboard *input_event_keyboard = static_cast<const InputEventKeyboard*>(input_event);
	return (key_code == input_event_keyboard->key_code || scan_code == input_event_keyboard->scan_code)
	       && modifiers == input_event_keyboard->modifiers;
}

void InputEventKeyboard::_fill_with_event(const SDL_Event *event) {
	if (get_event_type(event) != EVENT_INPUT_TYPE_KEYBOARD)
		return;

	modifiers = event->key.keysym.mod;
	scan_code = event->key.keysym.scancode;
	key_code = event->key.keysym.sym;
	time_stamp = event->key.timestamp;
	pressed = event->type == SDL_KEYDOWN;
}

bool InputEventAction::_same_input(const InputEvent *input_event) const {
	const InputEventAction *input_event_action = static_cast<const InputEventAction*>(input_event);
	return action_name == input_event_action->action_name && strength == input_event_action->strength;
}