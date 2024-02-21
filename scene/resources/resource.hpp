#pragma once

#include <core/math/math_defs.hpp>

#include <array>

namespace sdl {

class Resource {
protected:
	virtual uid _get_uid() const;

public:
	Resource() = default;
	~Resource() = default;

	uid get_uid() const;
};

template<class T>
constexpr std::array<uint8_t, sizeof(T)> class_to_bytes(const T &t) {
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
constexpr T class_from_bytes(const std::array<uint8_t, sizeof(T)> &bytes) {
	constexpr const std::size_t type_size = sizeof(T); 
	T t;
	uint8_t *byte_addr = (uint8_t*)&t;

	for (std::size_t i = 0; i < type_size; i++)
		byte_addr[i] = bytes[i];

	return t;
}
}