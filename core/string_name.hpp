#pragma once

#include <core/string_def.hpp>

#include <memory>
#include <unordered_set>
#include <vector>

namespace sdl {

class StringName {

public:
	struct string_storer {
		std::shared_ptr<String> string;

		string_storer() = default;
		string_storer(const String &string) {
			this->string = std::make_shared<String>(string);
		}

		bool operator==(const string_storer &string_storer) const {
			return string.get() == string_storer.string.get();
		}
	};

	struct string_saver {
		string_storer stored_string;

		string_saver() = default;
		string_saver(const string_storer &string_storer): stored_string(string_storer) {
		}

		bool operator==(const string_storer &string_saver) const {
			return stored_string.string.get() == string_saver.string.get();
		}

		bool operator==(const String &string) const {
			return *this->stored_string.string == string;
		}
	};

private:
	static std::unordered_set<string_storer> stored_strings;
	static std::unordered_set<string_saver> strings;
	string_saver saved_string;

	void set_string(const String &new_string);
	string_saver allocate_string(const String &string);
	
public:
	StringName();
	StringName(const String &string);

	~StringName();

	String get_string() const;
	const String *get_string_ptr() const;
};

}

template<>
struct std::hash<sdl::StringName::string_storer> {
	size_t operator()(const sdl::StringName::string_storer &string_storer) const noexcept {
		return std::hash<sdl::String>()(*string_storer.string);
	}
};

template<>
struct std::hash<sdl::StringName::string_saver> {
	size_t operator()(const sdl::StringName::string_saver &string_saver) const noexcept {
		return std::hash<sdl::String>()(*string_saver.stored_string.string);
	}
};
