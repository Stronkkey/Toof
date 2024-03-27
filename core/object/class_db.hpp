#pragma once

#include <core/string/string_def.hpp>
#include <core/string/string_name.hpp>

#include <any>
#include <cstdint>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace sdl {

struct PropertyInfo {
	std::type_index type;
	StringName name;
	StringName class_name;

	PropertyInfo(): type(typeid(void)), name(), class_name() {
	}
};

}

template<>
struct std::hash<sdl::PropertyInfo> {
	size_t operator()(const sdl::PropertyInfo &property_info) const noexcept {
		return std::hash<sdl::StringName>()(property_info.name);
	}
};

namespace sdl {

class ClassDB {
private:
	struct ClassInfo {
		std::unordered_set<PropertyInfo> property_list;

		ClassInfo() = default;
		~ClassInfo() = default;
	};

	std::unordered_map<StringName, ClassInfo> classes;
public:
	ClassDB() = default;
	~ClassDB() = default;

	void add_property(const StringName &class_name, const std::any &property);
};

}
