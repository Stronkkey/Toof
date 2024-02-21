#include <core/string_name.hpp>

using String = sdl::String;
using StringName = sdl::StringName;

std::unordered_set<StringName::string_storer> StringName::stored_strings = {};
std::unordered_set<StringName::string_saver> StringName::strings = {};

StringName::StringName(): saved_string(allocate_string("")) {
}

StringName::StringName(const String &string): saved_string(allocate_string(string)) {
}

void StringName::set_string(const String &new_string) {
	if (saved_string == new_string)
		return;

	saved_string = allocate_string(new_string);
}

StringName::string_saver StringName::allocate_string(const String &string) {
	auto iterator = stored_strings.find(string);
	if (iterator != stored_strings.end())
		return iterator._M_cur->_M_v();

	return stored_strings.insert(string).first._M_cur->_M_v();
}

StringName::~StringName() {
}

String StringName::get_string() const {
	return *saved_string.stored_string.string;
}

const String *StringName::get_string_ptr() const {
	return saved_string.stored_string.string.get();
}