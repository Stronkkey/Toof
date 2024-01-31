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
	std::string *allocate_string(const std::string &string);
	void deallocate_string(std::string *string);
	
public:
	StringName();
	StringName(const string_type &string);

	~StringName();

	const std::string *get_string() const;
};

}