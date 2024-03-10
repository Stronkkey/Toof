#include <core/string/string_funcs.hpp>

using namespace sdl;

[[nodiscard]] String sdl::to_string(const uint8_t number) {
	return std::to_string(number);
}

[[nodiscard]] String sdl::to_string(const int8_t number) {
	return std::to_string(number);
}

[[nodiscard]] String sdl::to_string(const uint16_t number) {
	return std::to_string(number);
}

[[nodiscard]] String sdl::to_string(const int16_t number) {
	return std::to_string(number);
}

[[nodiscard]] String sdl::to_string(const uint32_t number) {
	return std::to_string(number);
}

[[nodiscard]] String sdl::to_string(const int32_t number) {
	return std::to_string(number);
}

[[nodiscard]] String sdl::to_string(const uint64_t number) {
	return std::to_string(number);
}

[[nodiscard]] String sdl::to_string(const int64_t number) {
	return std::to_string(number);
}

[[nodiscard]] String sdl::to_string(const float number) {
	return std::to_string(number);
}

[[nodiscard]] String sdl::to_string(const double number) {
	return std::to_string(number);
}

[[nodiscard]] String sdl::to_string(const long double number) {
	return std::to_string(number);
}

[[nodiscard]] String sdl::to_string(const bool boolean) {
	return boolean ? "true" : "false";
}

[[nodiscard]] String sdl::to_string(const char character) {
	return String(&character, 1);
}

std::vector<String> sdl::split_string(const StringView &string_view, const StringView &delimiter) {
	const size_t string_length = string_view.length();
	const size_t characters_length = delimiter.length();
	std::vector<String> strings;
	size_t last_occurence = 0;
	size_t found_characters = StringView::npos;

	if (delimiter.empty()) {
		for (const auto &iterator: string_view)
			strings.push_back(String(&iterator, 1));
		return strings;
	}

	for (size_t pos = 0; pos < string_length; pos++) {
		char character = string_view[pos];

		if (found_characters == StringView::npos && character == delimiter.front()) {
			found_characters = 1;
			continue;
		}

		if (found_characters == StringView::npos)
			continue;

		if (characters_length < found_characters && character == delimiter.at(found_characters))
			found_characters++;
		else if (characters_length > 1) {
		 	found_characters = StringView::npos;
			continue;
		}

		if (found_characters >= characters_length) {
			strings.push_back(String(string_view.substr(last_occurence, pos)));
			found_characters = String::npos;
			last_occurence = pos;
		}
	}
	strings.push_back(String(string_view.substr(last_occurence, string_length - last_occurence)));

	return strings;
}

size_t sdl::get_occurences_in_string(const StringView &string_view, const StringView &characters) {
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
