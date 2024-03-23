#pragma once

#include <core/string/string_def.hpp>
#include <core/memory/optional.hpp>

#include <array>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <fstream>

namespace sdl {

class Resource;

template<class T>
constexpr std::array<uint8_t, sizeof(T)> __class_to_bytes__(const T &t) {
	constexpr const std::size_t type_size = sizeof(T);
	auto bytes = std::array<uint8_t, type_size>();
	uint8_t *byte_addr = (uint8_t*)&t;
	
	for (std::size_t i = 0; i < type_size; i++) {
		bytes[i] = *byte_addr;
		byte_addr++;
	}

	return bytes;
}

template<class T>
constexpr T __class_from_bytes__(const std::array<uint8_t, sizeof(T)> &bytes) {
	constexpr const std::size_t type_size = sizeof(T); 
	T t;
	uint8_t *byte_addr = (uint8_t*)&t;

	for (std::size_t i = 0; i < type_size; i++)
		byte_addr[i] = bytes[i];

	return T();
}

template<class T>
[[nodiscard]] inline Optional<T> load_file_to_class(const std::filesystem::path &path) {
	std::ifstream file = std::ifstream(path);

	if (file.rdstate() == std::ifstream::badbit || file.rdstate() == std::ifstream::failbit)
		return NullOption;

	std::array<uint8_t, sizeof(T)> array;
	file.read((char*)array.data(), sizeof(T));
	file.close();

	return __class_from_bytes__<T>(array);
}

template<class T>
inline bool save_class_to_file(const std::filesystem::path &to_path, const T &t) {
	std::ofstream output = std::ofstream(to_path);
	if (output.rdstate() == std::ifstream::badbit || output.rdstate() == std::ifstream::failbit)
		return false;

	const std::array<uint8_t, sizeof(T)> &array = __class_to_bytes__(t);
	output.write((char*)array.data(), sizeof(T));

	return true;
}

}