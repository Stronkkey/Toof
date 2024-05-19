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
