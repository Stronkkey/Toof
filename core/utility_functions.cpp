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
#include <core/utility_functions.hpp>

using namespace Toof;

void UtilityFunctions::start_text_modifier(String &string, TextModifier text_modifier) {
	char _string[5];
	StringView text_modifier_string = text_modifier_to_string_view(text_modifier);
	StringView modifier_string;

	_string[0] = '\33';
	_string[1] = '[';

	if (text_modifier_string.size() == 1) {
		_string[2] = text_modifier_string[0];
		_string[3] = 'm';
		modifier_string = StringView(_string, 4);
	} else if (text_modifier_string.size() > 1) {
		_string[2] = text_modifier_string[0];	
		_string[3] = text_modifier_string[1];
		_string[4] = 'm';
		modifier_string  = StringView(_string, 5);
	}
	
	String temp = std::move(string);

	const size_t string_size = modifier_string.length() + temp.length();
	string.resize(string_size);

	modifier_string.copy(string.data(), modifier_string.length(), 0);
	memmove(string.data() + modifier_string.length(), temp.data(), temp.length());
}

void UtilityFunctions::escape_string_text_modifier(String &string) {
	string.resize(string.length() + 4);
	string.append("\x1b[0m");
}

void UtilityFunctions::apply_text_modifier_on_string(String &string, TextModifier text_modifier) {
	start_text_modifier(string, text_modifier);
	escape_string_text_modifier(string);
}

void UtilityFunctions::apply_text_modifiers_on_string(String &string) {
	start_text_modifier(string, TEXT_MODIFIER_NONE);
}
