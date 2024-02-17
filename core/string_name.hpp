#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

namespace sdl {

class StringName {

typedef std::string string_t;

public:
	struct string_storer {
		std::shared_ptr<string_t> string;

		string_storer() = default;
		string_storer(const string_t &string) {
			this->string = std::make_shared<string_t>(string);
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

		bool operator==(const string_t &string) const {
			return *this->stored_string.string == string;
		}
	};

private:
	static std::unordered_set<string_storer> stored_strings;
	static std::unordered_set<string_saver> strings;
	string_saver saved_string;

	void set_string(const std::string &new_string);
	string_saver allocate_string(const string_t &string);
	
public:
	StringName();
	StringName(const string_t &string);

	~StringName();

	string_t get_string() const;
	const string_t *get_string_ptr() const;
};

}

template<>
struct std::hash<sdl::StringName::string_storer> {
	size_t operator()(const sdl::StringName::string_storer &string_storer) const noexcept {
		return std::hash<std::string>()(*string_storer.string);
	}
};

template<>
struct std::hash<sdl::StringName::string_saver> {
	size_t operator()(const sdl::StringName::string_saver &string_saver) const noexcept {
		return std::hash<std::string>()(*string_saver.stored_string.string);
	}
};
