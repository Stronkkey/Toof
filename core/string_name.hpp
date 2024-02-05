#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

namespace sdl {

class StringName {

typedef std::string string_type;

private:
	static std::unordered_set<std::string> strings;
	std::string *string;

	void set_string(const std::string &new_string);
	constexpr void deallocate_string(std::string *string);
	std::string *allocate_string(const std::string &string);
	
public:
	StringName();
	StringName(const string_type &string);

	~StringName();

	constexpr const std::string *get_string() const;
};

constexpr void sdl::StringName::deallocate_string(std::string *string) {
	// TODO: Free string
	(void)string;
}

constexpr const std::string *sdl::StringName::get_string() const {
	return string;
}

}