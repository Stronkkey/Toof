#pragma once

#include <core/string/string_def.hpp>

#include <cstdint>
#include <memory>
#include <variant>

namespace sdl {

template<class>
struct Vector2;

template<class>
struct Rect2;

template<class>
struct Color;

struct Transform2D;
class StringName;

enum VariantType {
	VARIANT_TYPE_INVALID = 0,
	VARIANT_TYPE_BOOL,
	VARIANT_TYPE_u8,
	VARIANT_TYPE_i8,
	VARIANT_TYPE_u16,
	VARIANT_TYPE_i16,
	VARIANT_TYPE_u32,
	VARIANT_TYPE_i32,
	VARIANT_TYPE_u64,
	VARIANT_TYPE_i64,
	VARIANT_TYPE_FLOAT,
	VARIANT_TYPE_DOUBLE,
	VARIANT_TYPE_STRING,
	VARIANT_TYPE_STRING_NAME,
	VARIANT_TYPE_VECTOR2_f32,
	VARIANT_TYPE_VECTOR2_f64,
	VARIANT_TYPE_VECTOR2_i32,
	VARIANT_TYPE_VECTOR2_i64,
	VARIANT_TYPE_RECT2_f32,
	VARIANT_TYPE_RECT2_f64,
	VARIANT_TYPE_RECT2_i32,
	VARIANT_TYPE_RECT2_i64,
	VARIANT_TYPE_TRANSFORM2D,
	VARIANT_TYPE_COLOR8,
	VARIANT_TYPE_COLOR16,
	VARIANT_TYPE_MAX,
};

using Variant = std::variant<bool,
    uint8_t,
    int8_t,
    uint16_t,
    int16_t,
    uint32_t,
    int32_t,
    uint64_t,
    int64_t,
    float,
    double,
    String,
    StringName,
    Vector2<float>,
	Vector2<double>,
    Vector2<int32_t>,
	Vector2<int64_t>,
    Rect2<float>,
	Rect2<double>,
    Rect2<int32_t>,
	Rect2<int64_t>,
    Transform2D,
    Color<uint8_t>,
    Color<uint16_t>>;


VariantType get_variant_type_from_variant(const Variant &variant);
size_t get_variant_size(const Variant &variant);
void serialize_variant(const Variant &variant, uint8_t *to);

struct VariantMetadata {
	using IntegerType = int16_t;
	IntegerType type;
};

constexpr VariantMetadata::IntegerType variant_type_to_int(const VariantType variant_type) {
	return static_cast<VariantMetadata::IntegerType>(variant_type);
}

VariantMetadata create_variant_metadata(const Variant &variant);
size_t get_required_variant_data_size(const Variant &variant);
void write_variant_data(const Variant &variant, const VariantMetadata meta_data, uint8_t *to);
std::pair<std::unique_ptr<uint8_t[]>, size_t> get_variant_data(const Variant &variant);

}