#pragma once

#include <core/math/math_defs.hpp>
#include <core/string/string_funcs.hpp>

#include <fstream>
#include <sstream>

#include <cereal/archives/binary.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/xml.hpp>

namespace sdl {

template<class T>
struct __var_size__ : public std::integral_constant<std::size_t, sizeof(T)> {
};

template<class T>
struct __var_size__<T[]> : public std::integral_constant<std::size_t, sizeof(T)> {
};

template<class T, std::size_t N>
struct __var_size__<T[N]> : public std::integral_constant<std::size_t, sizeof(T)> {
};

template<class T>
struct __sub_array__ : public std::integral_constant<T, false> {
};

template<class T>
struct __sub_array__<T[]> : public std::integral_constant<T, false> {
};

template<class T, std::size_t N>
struct __sub_array__<T[N]> : public std::integral_constant<T, false> {
};

template<class T, std::size_t N, std::size_t N2>
struct __sub_array__<T[N][N2]> : public std::integral_constant<T, true> {
};

template<class T>
struct __underlying_type__ {
	using value_type = T;
};

template<class T>
struct __underlying_type__<T[]> {
	using value_type = T;
};

template<class T, size_t N>
struct __underlying_type__<T[N]> {
	using value_type = T;
};

template<class T, size_t N, size_t N2>
struct __underlying_type__<T[N][N2]> {
	using value_type = typename __underlying_type__<T>::value_type;
};

template<class T, class Archive = cereal::PortableBinaryOutputArchive>
inline void write_variant_binary_data(const T &variant, Archive &archive) {
	constexpr const bool is_array = std::is_array<T>();
	constexpr const uint64_t array_size = sizeof(T) / __var_size__<T>::value;

	if (is_array)
		archive(array_size, variant);
	else
		archive(variant);
}

template<class T, class Archive = cereal::PortableBinaryOutputArchive>
inline void write_variant_text_data_with_name(const T &variant, Archive &archive, const String &variant_name) {
	archive(cereal::make_nvp(variant_name, variant));
}

template<class T>
constexpr bool __is_string_array__() {
	using underlying_type = typename __underlying_type__<T>::value_type;
	return std::is_same<underlying_type, const char>::value || std::is_same<underlying_type, char>::value || std::is_same<underlying_type, const char*>::value || std::is_same<underlying_type, char*>::value;
}

template<class T, class Archive = cereal::PortableBinaryOutputArchive>
inline void write_variant_text_data(const T &variant, Archive &archive) {
	constexpr const bool is_string_array = __is_string_array__<T>();

	if (is_string_array)
		archive(to_string(variant));
	else
		archive(variant);
}

template<class Archive>
constexpr bool __is_archive_binary_type__() {
	return std::is_same<Archive, cereal::BinaryOutputArchive>::value || std::is_same<Archive, cereal::PortableBinaryOutputArchive>::value;
}

template<class T>
inline std::stringstream get_variant_data(const T &variant) {
	std::stringstream string_stream = std::stringstream();
	write_variant_binary_data(variant, string_stream);
	return string_stream;
}

template<class, bool>
struct __text_writer__;

template<class Archive>
struct __text_writer__<Archive, true> {
	void start_node(Archive&, const char*) {}
	void finish_node(Archive&) {}
	void go_into_node(Archive&) {}

	template<class T>
	void load_value(Archive&, T&) {}
};

template<class Archive>
struct __text_writer__<Archive, false> {
	void start_node(Archive &archive, const char *name) {
		archive.setNextName(name);
		archive.startNode();
	}

	void finish_node(Archive &archive) {
		archive.finishNode();
	}

	void go_into_node(Archive &archive) {
		archive.startNode();
	}

	template<class T>
	void load_value(Archive &archive, T &t) {
		archive.loadValue(t);
	}
};


template<class Archive>
class VariantFileWriter {
public:
	using ArchiveType = Archive;
private:
	std::ofstream file;
	Archive archive;

	std::ofstream get_stream(const char *path) const {
		if (__is_archive_binary_type__<Archive>())
			return std::ofstream(path, std::ios::binary);
		return std::ofstream(path);
	}

	void _write_file_metadata() {
		archive(cereal::make_nvp("Unused1", uint8_t(REAL_IS_DOUBLE)));
	}

	template<class T>
	inline void _call_write_function(const T &variant) {
		if (__is_archive_binary_type__<Archive>())
			write_variant_binary_data<T, Archive>(variant, archive);
		else
			write_variant_text_data<T, Archive>(variant, archive);
	}

	template<class T>
	inline void _call_write_function_with_name(const T &variant, const String &variant_name) {
		if (__is_archive_binary_type__<Archive>())
			write_variant_binary_data<T, Archive>(variant, archive);
		else
			write_variant_text_data_with_name<T, Archive>(variant, archive, variant_name);
	}
public:
	VariantFileWriter(const char *path): file(path), archive(file) {
		_write_file_metadata();
	}

	~VariantFileWriter() {
	}

	void start_node(const char *name = nullptr) {
		__text_writer__<Archive, __is_archive_binary_type__<Archive>()> __wr;
		__wr.start_node(archive, name);
	}

	void finish_node() {
		__text_writer__<Archive, __is_archive_binary_type__<Archive>()> __wr;
		__wr.finish_node(archive);
	}

	template<class T>
	inline void write(const T &variant) {
		_call_write_function(variant);
	}

	template<class T>
	inline void write_with_name(const String &variant_name, const T &variant) {
		_call_write_function_with_name(variant, variant_name);
	}

	template<class T>
	std::ofstream &operator<<(const T &variant) {
		_call_write_function(variant);
		return file;
	}

	std::ofstream &get_file() & {
		return file;
	}

	std::ofstream &&get_file() && {
		return std::move(file);
	}

	const std::ofstream &get_file() const & {
		return file;
	}

	const std::ofstream &&get_file() const && {
		return std::move(file);
	}

	Archive &get_archive() & {
		return archive;
	}

	Archive &&get_archive() && {
		return std::move(archive);
	}

	const Archive &get_archive() const & {
		return archive;
	}

	const Archive &&get_archive() const && {
		return std::move(archive);
	}
};

template<class Archive>
class VariantFileReader {
public:
	using ArchiveType = Archive;
private:
	std::ifstream file;
	Archive archive;
	uint8_t uses_double;

	std::ifstream get_stream(const char *path) const {
		if (__is_archive_binary_type__<Archive>())
			return std::ifstream(path, std::ios::binary);
		return std::ifstream(path);
	}

	void _set_uses_double() {
		archive(uses_double);
	}
public:
	VariantFileReader(const char *path): file(path), archive(file), uses_double() {
		_set_uses_double();
	}

	template<class T>
	T read_value() {
		T t;
		archive(t);
		return t;
	}

	template<class T, class... Args>
	std::tuple<T, Args...> read_values() {
		std::tuple<T, Args...> tuple;
		archive(tuple);
		return tuple;
	}

	template<class... Args>
	void read_to(Args&&... args) {
		archive(args...);
	}

	template<class T>
	void load_value(T &t) {
		__text_writer__<Archive, __is_archive_binary_type__<Archive>()> __wr;
		__wr.load_value(archive, t);
	}
	
	void go_into_node() {
		__text_writer__<Archive, __is_archive_binary_type__<Archive>()> __wr;
		__wr.go_into_node(archive);
	}

	void exit_out_of_node() {
		__text_writer__<Archive, __is_archive_binary_type__<Archive>()> __wr;
		__wr.finish_node(archive);
	}

	bool file_uses_double() const {
		return uses_double;
	}

	std::ifstream &get_file() & {
		return file;
	}

	std::ifstream &&get_file() && {
		return std::move(file);
	}

	const std::ifstream &get_file() const & {
		return file;
	}

	const std::ifstream &&get_file() const && {
		return std::move(file);
	}

	Archive &get_archive() & {
		return archive;
	}

	Archive &&get_archive() && {
		return std::move(archive);
	}

	const Archive &get_archive() const & {
		return archive;
	}

	const Archive &&get_archive() const && {
		return std::move(archive);
	}
};

}