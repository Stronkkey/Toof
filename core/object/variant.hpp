#pragma once

#include <core/string/string_def.hpp>

#include <cstdint>
#include <climits>
#include <memory>
#include <fstream>

#include <cereal/archives/binary.hpp>

namespace sdl {

template<class>
struct Vector2;

template<class>
struct Rect2;

template<class>
struct Color;

struct Transform2D;
class StringName;

enum EncoderVersion {
	ENCODER_VERSION_01 = 0x313030646f636e67, // gncod001
};

constexpr const EncoderVersion ENCODER_VERSION = ENCODER_VERSION_01;

enum VariantType {
	VARIANT_TYPE_UNKNOWN = 0,
	VARIANT_TYPE_BOOL = 1,
	VARIANT_TYPE_u8 = 2,
	VARIANT_TYPE_i8 = 3,
	VARIANT_TYPE_u16 = 4,
	VARIANT_TYPE_i16 = 5,
	VARIANT_TYPE_u32 = 6,
	VARIANT_TYPE_i32 = 7,
	VARIANT_TYPE_u64 = 8,
	VARIANT_TYPE_i64 = 9,
	VARIANT_TYPE_FLOAT = 10,
	VARIANT_TYPE_DOUBLE = 11,
	VARIANT_TYPE_STRING = 12,
	VARIANT_TYPE_VECTOR2_f32 = 13,
	VARIANT_TYPE_VECTOR2_f64 = 14,
	VARIANT_TYPE_VECTOR2_i32 = 15,
	VARIANT_TYPE_VECTOR2_i64 = 16,
	VARIANT_TYPE_RECT2_f32 = 17,
	VARIANT_TYPE_RECT2_f64 = 18,
	VARIANT_TYPE_RECT2_i32 = 19,
	VARIANT_TYPE_RECT2_i64 = 20,
	VARIANT_TYPE_TRANSFORM2D = 21,
	VARIANT_TYPE_COLOR8 = 22,
	VARIANT_TYPE_COLOR16 = 23,
	VARIANT_TYPE_ARRAY = 24
};

#define __EQUAL_TO_RETURN_VARIANT_IMPL__(type, returnval) if (std::is_same<T, type>::value) return returnval;

template<class T>
struct __underlying_type__ {
	using value_type = T;
};

template<class T>
struct __underlying_type__<T[]> {
	using value_type = T;
};

template<class T, std::size_t N>
struct __underlying_type__<T[N]> {
	using value_type = T;
};

template<class T>
constexpr bool __is_char_type__() {
	using underlying_type = typename __underlying_type__<T>::value_type;
	return std::is_same<underlying_type, char>::value || std::is_same<underlying_type, const char>::value;
}

template<class T>
constexpr VariantType get_variant_type_from_type() {
	__EQUAL_TO_RETURN_VARIANT_IMPL__(bool, VARIANT_TYPE_BOOL)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(char, CHAR_MIN == 0 ? VARIANT_TYPE_u8 : VARIANT_TYPE_i8)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(uint8_t, VARIANT_TYPE_u8)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(int8_t, VARIANT_TYPE_i8)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(uint16_t, VARIANT_TYPE_u16)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(int16_t, VARIANT_TYPE_i16)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(uint32_t, VARIANT_TYPE_u32)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(int32_t, VARIANT_TYPE_i32)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(uint64_t, VARIANT_TYPE_u64)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(int64_t, VARIANT_TYPE_i64)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(float, VARIANT_TYPE_FLOAT)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(double, VARIANT_TYPE_DOUBLE)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(String, VARIANT_TYPE_STRING)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(StringName, VARIANT_TYPE_STRING)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(Vector2<float>, VARIANT_TYPE_VECTOR2_f32)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(Vector2<double>, VARIANT_TYPE_VECTOR2_f64)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(Vector2<uint32_t>, VARIANT_TYPE_VECTOR2_i32)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(Vector2<uint64_t>, VARIANT_TYPE_VECTOR2_i64)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(Rect2<float>, VARIANT_TYPE_RECT2_f32)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(Rect2<double>, VARIANT_TYPE_RECT2_f64)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(Rect2<uint32_t>, VARIANT_TYPE_RECT2_i32)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(Rect2<uint64_t>, VARIANT_TYPE_RECT2_i64)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(Transform2D, VARIANT_TYPE_TRANSFORM2D)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(Color<uint8_t>, VARIANT_TYPE_COLOR8)
	__EQUAL_TO_RETURN_VARIANT_IMPL__(Color<uint16_t>, VARIANT_TYPE_COLOR16)

	if (__is_char_type__<T>())
		return VARIANT_TYPE_STRING;

	if (std::is_array<T>::value)
		return VARIANT_TYPE_ARRAY;

	return VARIANT_TYPE_UNKNOWN;
}

struct VariantMetadata {
	using IntegerType = int16_t;
	using StoredSizeType = uint64_t;
	IntegerType type;

	constexpr VariantMetadata(): type(0) {
	}

	constexpr VariantMetadata(IntegerType integer): type(integer) {
	}
};

constexpr VariantMetadata::IntegerType variant_type_to_int(const VariantType variant_type) {
	return static_cast<VariantMetadata::IntegerType>(variant_type);
}

template<class T>
constexpr VariantMetadata::IntegerType variant_type_to_int() {
	return variant_type_to_int(get_variant_type_from_type<T>());
}

template<class T>
struct __var_size__ : public std::integral_constant<size_t, sizeof(T)> {
};

template<class T>
struct __var_size__<T[]> : public std::integral_constant<size_t, sizeof(T)> {
};

template<class T, std::size_t N>
struct __var_size__<T[N]> : public std::integral_constant<size_t, sizeof(T)> {
};

template<class T>
struct __sub_array__ : public std::integral_constant<bool, false> {
};

template<class T>
struct __sub_array__<T[]> : public std::integral_constant<bool, false> {
};

template<class T, std::size_t N>
struct __sub_array__<T[N]> : public std::integral_constant<bool, false> {
};

template<class T, std::size_t N, std::size_t N2>
struct __sub_array__<T[N][N2]> : public std::integral_constant<bool, true> {
};

template<class T>
constexpr VariantMetadata get_variant_metadata(const T&) {
	VariantMetadata meta_data;
	meta_data.type = variant_type_to_int<T>();

	return meta_data;
}

inline void write_variants_metadata(std::ostream &to) {
	uint64_t version = static_cast<uint64_t>(ENCODER_VERSION);
	to.write(reinterpret_cast<const char*>(&version), 8);
}

template<class T>
inline void write_variant_data(const T &variant, std::ostream &to) {
	VariantMetadata meta_data = get_variant_metadata(variant);

	constexpr const bool is_array = std::is_array<T>();
	constexpr const VariantMetadata::StoredSizeType array_size = sizeof(T) / __var_size__<T>::value;
	constexpr const bool has_subarray = __sub_array__<T>::value;
	static_assert(!has_subarray, "Arrays inside arrays cannot be serialized.");

	cereal::BinaryOutputArchive output_archive = to;
	
	output_archive(meta_data.type);

	if (__is_char_type__<T>() && is_array)
		output_archive(array_size, variant);
	else if (is_array) {
		using underlying_type = typename __underlying_type__<T>::value_type;
		output_archive(variant_type_to_int<underlying_type>(), array_size, variant);
	} else if (meta_data.type == VARIANT_TYPE_UNKNOWN)
		output_archive(sizeof(T), variant);
	else
		output_archive(variant);
}

template<class T>
inline std::stringstream get_variant_data(const T &variant) {
	std::stringstream string_stream = std::stringstream();
	write_variant_data(variant, string_stream);
	return string_stream;
}

struct VariantEncodedFile {
private:
	std::ofstream file;
public:
	VariantEncodedFile(): file() {
		write_variants_metadata(file);
	}

	VariantEncodedFile(const char *file_name): file(file_name) {
		write_variants_metadata(file);
	}

	template<class T>
	inline void write(const T &variant) {
		write_variant_data(variant, file);
	}

	template<class T>
	std::ostream &operator<<(const T &variant) {
		write_variant_data(variant, file);
		return file;
	}
};

}