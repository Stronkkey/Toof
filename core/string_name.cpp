#include <core/string_name.hpp>

std::unordered_set<std::string> sdl::StringName::strings = {};

sdl::StringName::StringName(): string(allocate_string("")) {
	string = allocate_string("");
}

sdl::StringName::StringName(const std::string &string): string(allocate_string(string)) {
}

void sdl::StringName::set_string(const std::string &new_string) {
	if (*string == new_string)
		return;

	deallocate_string(string);
	string = allocate_string(new_string);
}

std::string *sdl::StringName::allocate_string(const std::string &string) {
	auto iterator = strings.find(string);
	if (iterator != strings.end())
		return &iterator._M_cur->_M_v();

	return &strings.insert(string).first._M_cur->_M_v();
}

sdl::StringName::~StringName() {
}
