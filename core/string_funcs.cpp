#include <core/string_funcs.hpp>

using namespace sdl;

[[nodiscard]] String StringFuncs::to_string(const uint8_t number) {
	return std::to_string(number);
}

[[nodiscard]] String StringFuncs::to_string(const int8_t number) {
	return std::to_string(number);
}

[[nodiscard]] String StringFuncs::to_string(const uint16_t number) {
	return std::to_string(number);
}

[[nodiscard]] String StringFuncs::to_string(const int16_t number) {
	return std::to_string(number);
}

[[nodiscard]] String StringFuncs::to_string(const uint32_t number) {
	return std::to_string(number);
}

[[nodiscard]] String StringFuncs::to_string(const int32_t number) {
	return std::to_string(number);
}

[[nodiscard]] String StringFuncs::to_string(const uint64_t number) {
	return std::to_string(number);
}

[[nodiscard]] String StringFuncs::to_string(const int64_t number) {
	return std::to_string(number);
}

[[nodiscard]] String StringFuncs::to_string(const float number) {
	return std::to_string(number);
}

[[nodiscard]] String StringFuncs::to_string(const double number) {
	return std::to_string(number);
}

[[nodiscard]] String StringFuncs::to_string(const long double number) {
	return std::to_string(number);
}

[[nodiscard]] String StringFuncs::to_string(const bool boolean) {
	return boolean ? "true" : "false";
}

[[nodiscard]] String StringFuncs::to_string(const char *string) {
	return String(string);
}

[[nodiscard]] String StringFuncs::to_string(const String &string) {
	return String(string);
}

[[nodiscard]] String StringFuncs::to_string(const char character) {
	return String(&character, 1);
}

std::vector<String> StringFuncs::split_string(const StringView &string_view, const String &delimiter) {
	uint64_t pos = 0;
	std::vector<String> strings;
	(void)pos;
	(void)string_view;
	(void)delimiter;
/**
	while (pos != String::npos) {
		strings.push_back(str_copy.substr(0, pos));
		str_copy.erase(0, pos + delimiter.length());
		pos = str_copy.find(delimiter);
	}
**/
	return strings;
}

size_t StringFuncs::get_occurences_in_string(const StringView &string_view, const StringView &characters) {
	const size_t characters_length = characters.length();
	const size_t string_length = string_view.length();
	if (characters.empty())
		return string_length;
	if (characters_length > string_length || string_view.empty())
		return 0;

	size_t occurences = 0;
	size_t found_characters = String::npos;

	for (size_t pos = 0; pos < string_length; pos++) {
		char character = string_view[pos];

		if (found_characters == String::npos && character == characters.front()) {
			found_characters = 1;
			continue;
		}

		if (found_characters == String::npos)
			continue;

		if (character == characters.at(found_characters))
			found_characters++;
		else {
		 	found_characters = String::npos;
			continue;
		}

		if (found_characters >= characters_length) {
			occurences++;
			found_characters = String::npos;
		}
	}

	return occurences;
}
