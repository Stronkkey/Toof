#include "core/math/math_defs.hpp"
#include <core/object/variant.hpp>

#include <core/math/color.hpp>
#include <core/math/rect2.hpp>
#include <core/math/transform2d.hpp>
#include <core/math/vector2.hpp>
#include <core/string/string_name.hpp>

using namespace sdl;

VariantType sdl::get_variant_type_from_variant(const Variant &variant) {
	return static_cast<sdl::VariantType>(variant.index() + 1);
}

size_t sdl::get_variant_size(const Variant &variant) {
	VariantType type = get_variant_type_from_variant(variant);

	switch (type) {
		case VARIANT_TYPE_BOOL:
			return 1;
		case VARIANT_TYPE_u8:
			return 1;
		case VARIANT_TYPE_i8:
			return 1;
		case VARIANT_TYPE_u16:
			return 2;
		case VARIANT_TYPE_i16:
			return 2;
		case VARIANT_TYPE_u32:
			return 4;
		case VARIANT_TYPE_i32:
			return 4;
		case VARIANT_TYPE_u64:
			return 8;
		case VARIANT_TYPE_i64:
			return 8;
		case VARIANT_TYPE_FLOAT:
			return sizeof(float);
		case VARIANT_TYPE_DOUBLE:
			return sizeof(double);
		case VARIANT_TYPE_STRING:
			return std::get<String>(variant).length() + 8; // +8 to encode the length.
		case VARIANT_TYPE_STRING_NAME:
			return std::get<StringName>(variant).length() + 8; // +8 to encode the length.
		case VARIANT_TYPE_VECTOR2_f32:
			return sizeof(float) * 2;
		case VARIANT_TYPE_VECTOR2_f64:
			return sizeof(double) * 2;
		case VARIANT_TYPE_VECTOR2_i32:
			return 8;
		case VARIANT_TYPE_VECTOR2_i64:
			return 16;
		case VARIANT_TYPE_RECT2_f32:
			return sizeof(float) * 4;
		case VARIANT_TYPE_RECT2_f64:
			return sizeof(double) * 4;
		case VARIANT_TYPE_RECT2_i32:
			return 16;
		case VARIANT_TYPE_RECT2_i64:
			return 32;
		case VARIANT_TYPE_TRANSFORM2D:
			return REAL_IS_DOUBLE ? 41 : 21; // 1 byte is used to store if it is float or double.
		case VARIANT_TYPE_COLOR8:
			return 4;
		case VARIANT_TYPE_COLOR16:
			return 8;
		default:
			return 0;
	}
}

template<class T>
void serialize_small(T t, uint8_t *to) {
	to[0] = t;
}

template<class T>
void serialize_t(const T &t, uint8_t *to) {
	T *value = reinterpret_cast<T*>(to);
	(*value) = t;
}

void fill_null(uint8_t *into, size_t size) {
	for (size_t i = 0; i < size; i++)
		into[i] = 0;
}

void serialize_t(const float float_number, uint8_t *to) {
	(*reinterpret_cast<float*>(to)) = float_number;
}

void serialize_t(const double float_number, uint8_t *to) {
	(*reinterpret_cast<double*>(to)) = float_number;
}

void serialize_t(const String &string, uint8_t *to) {
	static_assert(sizeof(String::value_type) == 1, "Non utf-8 string types are not supported.");

	(*reinterpret_cast<uint64_t*>(to)) = string.size();
	string.copy((char*)(to + 8), string.size());
}

void serialize_t(const StringName &string_name, uint8_t *to) {
	serialize_t(String(string_name.get_string()), to);
}

void serialize_t(const Vector2<float> &vector2, uint8_t *to) {
	if (sizeof(float) != 4) {
		fill_null(to, 8);
		return;
	}

	(*reinterpret_cast<float*>(to)) = vector2.x;
	(*reinterpret_cast<float*>(to + 4)) = vector2.y;
}

void serialize_t(const Vector2<double> &vector2, uint8_t *to) {
	(*reinterpret_cast<double*>(to)) = vector2.x;
	(*reinterpret_cast<double*>(to + 8)) = vector2.y;
}

void serialize_t(const Vector2<int32_t> &vector2, uint8_t *to) {
	(*reinterpret_cast<int32_t*>(to)) = vector2.x;
	(*reinterpret_cast<int32_t*>(to + 4)) = vector2.y;
}

void serialize_t(const Vector2<int64_t> &vector2, uint8_t *to) {
	(*reinterpret_cast<int64_t*>(to)) = vector2.x;
	(*reinterpret_cast<int64_t*>(to + 8)) = vector2.y;
}

void serialize_t(const Rect2<float> &rect2, uint8_t *to) {
	(*reinterpret_cast<float*>(to)) = rect2.x;
	(*reinterpret_cast<float*>(to + 4)) = rect2.y;
	(*reinterpret_cast<float*>(to + 8)) = rect2.w;
	(*reinterpret_cast<float*>(to + 12)) = rect2.h;
}

void serialize_t(const Rect2<double> &rect2, uint8_t *to) {
	(*reinterpret_cast<double*>(to)) = rect2.x;
	(*reinterpret_cast<double*>(to + 8)) = rect2.y;
	(*reinterpret_cast<double*>(to + 16)) = rect2.w;
	(*reinterpret_cast<double*>(to + 24)) = rect2.h;
}

void serialize_t(const Rect2<int32_t> &rect2, uint8_t *to) {
	(*reinterpret_cast<int32_t*>(to)) = rect2.x;
	(*reinterpret_cast<int32_t*>(to + 4)) = rect2.y;
	(*reinterpret_cast<int32_t*>(to + 8)) = rect2.w;
	(*reinterpret_cast<int32_t*>(to + 12)) = rect2.h;
}

void serialize_t(const Rect2<int64_t> &rect2, uint8_t *to) {
	(*reinterpret_cast<int32_t*>(to)) = rect2.x;
	(*reinterpret_cast<int32_t*>(to + 4)) = rect2.y;
	(*reinterpret_cast<int32_t*>(to + 8)) = rect2.w;
	(*reinterpret_cast<int32_t*>(to + 12)) = rect2.h;
}

void serialize_t(const Transform2D &transform2d, uint8_t *to) {
	(*to) = REAL_IS_DOUBLE;

	if (REAL_IS_DOUBLE) {
		(*reinterpret_cast<double*>(to + 1)) = transform2d.origin.x;
		(*reinterpret_cast<double*>(to + 9)) = transform2d.origin.y;
		(*reinterpret_cast<double*>(to + 17)) = transform2d.scale.x;
		(*reinterpret_cast<double*>(to + 25)) = transform2d.scale.y;
		(*reinterpret_cast<double*>(to + 33)) = transform2d.rotation.get_angle_degrees();
	} else {
		(*reinterpret_cast<float*>(to + 1)) = transform2d.origin.x;
		(*reinterpret_cast<float*>(to + 5)) = transform2d.origin.y;
		(*reinterpret_cast<float*>(to + 9)) = transform2d.scale.x;
		(*reinterpret_cast<float*>(to + 13)) = transform2d.scale.y;
		(*reinterpret_cast<float*>(to + 17)) = transform2d.rotation.get_angle_degrees();
	}
}

template<class T>
void serialize_t(const Color<T> &color, uint8_t *to) {
	using NumType = T;

	(*reinterpret_cast<NumType*>(to)) = color.r;
	(*reinterpret_cast<NumType*>(to + sizeof(NumType))) = color.r;
	(*reinterpret_cast<NumType*>(to + sizeof(NumType) * 2)) = color.r;
	(*reinterpret_cast<NumType*>(to + sizeof(NumType) * 3)) = color.r;
}

void sdl::serialize_variant(const Variant &variant, uint8_t *to) {
	switch (get_variant_type_from_variant(variant)) {
		case VARIANT_TYPE_BOOL:
			serialize_small(std::get<bool>(variant), to);
			break;
		case VARIANT_TYPE_u8:
			serialize_small(std::get<uint8_t>(variant), to);
			break;
		case VARIANT_TYPE_i8:
			serialize_small(std::get<int8_t>(variant), to);
			break;
		case VARIANT_TYPE_u16:
			serialize_t(std::get<uint16_t>(variant), to);
			break;
		case VARIANT_TYPE_i16:
			serialize_t(std::get<int16_t>(variant), to);
			break;
		case VARIANT_TYPE_u32:
			serialize_t(std::get<uint32_t>(variant), to);
			break;
		case VARIANT_TYPE_i32:
			serialize_t(std::get<int32_t>(variant), to);
			break;
		case VARIANT_TYPE_u64:
			serialize_t(std::get<uint64_t>(variant), to);
			break;
		case VARIANT_TYPE_i64:
			serialize_t(std::get<int64_t>(variant), to);
			break;
		case VARIANT_TYPE_FLOAT:
			serialize_t(std::get<float>(variant), to);
			break;
		case VARIANT_TYPE_DOUBLE:
			serialize_t(std::get<double>(variant), to);
			break;
		case VARIANT_TYPE_STRING:
			serialize_t(std::get<String>(variant), to);
			break;
		case VARIANT_TYPE_STRING_NAME:
			serialize_t(std::get<StringName>(variant), to);
			break;
		case VARIANT_TYPE_VECTOR2_f32:
			serialize_t(std::get<Vector2<float>>(variant), to);
			break;
		case VARIANT_TYPE_VECTOR2_f64:
			serialize_t(std::get<Vector2<double>>(variant), to);
			break;
		case VARIANT_TYPE_VECTOR2_i32:
			serialize_t(std::get<Vector2<int32_t>>(variant), to);
			break;
		case VARIANT_TYPE_VECTOR2_i64:
			serialize_t(std::get<Vector2<int64_t>>(variant), to);
			break;
		case VARIANT_TYPE_RECT2_f32:
			serialize_t(std::get<Rect2<float>>(variant), to);
			break;
		case VARIANT_TYPE_RECT2_f64:
			serialize_t(std::get<Rect2<double>>(variant), to);
			break;
		case VARIANT_TYPE_RECT2_i32:
			serialize_t(std::get<Rect2<int32_t>>(variant), to);
			break;
		case VARIANT_TYPE_RECT2_i64:
			serialize_t(std::get<Rect2<int64_t>>(variant), to);
			break;
		case VARIANT_TYPE_TRANSFORM2D:
			serialize_t(std::get<Transform2D>(variant), to);
			break;
		case VARIANT_TYPE_COLOR8:
			serialize_t(std::get<Color<uint8_t>>(variant), to);
			break;
		case VARIANT_TYPE_COLOR16:
			serialize_t(std::get<Color<uint16_t>>(variant), to);
			break;
		default:
			break;
	}
}

VariantMetadata sdl::create_variant_metadata(const Variant &variant) {
	VariantMetadata meta_data;
	meta_data.type = variant_type_to_int(get_variant_type_from_variant(variant));
	return meta_data;
}

size_t sdl::get_required_variant_data_size(const Variant &variant) {
	return get_variant_size(variant) + sizeof(VariantMetadata::IntegerType);
}

void sdl::write_variant_data(const Variant &variant, const VariantMetadata meta_data, uint8_t *to) {
	(*reinterpret_cast<VariantMetadata::IntegerType*>(to)) = meta_data.type;
	serialize_variant(variant, to + sizeof(VariantMetadata::IntegerType));
}

std::pair<std::unique_ptr<uint8_t[]>, size_t> sdl::get_variant_data(const Variant &variant) {
	const size_t variant_data_size = get_required_variant_data_size(variant);
	auto byte_array = std::make_unique<uint8_t[]>(variant_data_size);

	write_variant_data(variant, create_variant_metadata(variant), byte_array.get());
	return {std::move(byte_array), variant_data_size};
}
