/*  This file is part of the Toof Engine. */
/** @file input_map.hpp */
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

#include <input/input_event.hpp>
#include <input/input_proxy.hpp>

#include <SDL_keycode.h>

#include <string>
#include <unordered_map>
#include <set>
#include <memory>
#include <vector>

namespace Toof {

class InputMap {

public:
	struct Action {
		std::set<InputProxy, std::equal_to<InputProxy>> inputs;
	};

private:
	std::unordered_map<String, Action> actions;
	void _add_input_to_action(const String &action_name, const InputProxy &input_proxy);
	void _remove_input_from_action(const String &action_name, const InputProxy &input_proxy);

public:
	InputMap();
	~InputMap();

	void create_action(const String &action_name);
	void add_key_to_action(const String &action_name, const std::shared_ptr<InputEvent> &input_event);
	void remove_key_from_action(const String &action_name, const std::shared_ptr<InputEvent> &input_event);

	bool has_action(const String &action_name) const;
	void clear_action(const String &action_name);

	std::vector<InputEvent> action_get_events(const String &action_name) const;
	const std::unordered_map<String, Action> &get_actions() const;

	bool event_get_action_state(const InputEvent *input_event, const String &action_name, bool *pressed = nullptr, float *strength = nullptr) const;
	bool event_is_action(const InputEvent *input_event, const String &action_name) const;
};

}
