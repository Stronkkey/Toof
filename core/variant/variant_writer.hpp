#pragma once

#include <core/math/math_defs.hpp>
#include <core/string/string_def.hpp>

#include <filesystem>
#include <fstream>
#include <sstream>

#include <cereal/archives/binary.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/xml.hpp>

#include <stringify/to_string.hpp>

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
		archive(S_TO_STRING_N(variant));
	else
		archive(variant);
}

template<class T>
inline std::stringstream get_variant_data(const T &variant) {
	std::stringstream string_stream = std::stringstream();
	write_variant_binary_data(variant, string_stream);
	return string_stream;
}

namespace detail {

template<class Archive>
constexpr bool __is_archive_binary_type__() {
	return std::is_same<Archive, cereal::BinaryOutputArchive>::value || std::is_same<Archive, cereal::PortableBinaryOutputArchive>::value || std::is_same<Archive, cereal::BinaryInputArchive>::value || std::is_same<Archive, cereal::PortableBinaryInputArchive>::value;
}

template<class StreamType, class Archive, typename std::enable_if<__is_archive_binary_type__<Archive>(), bool>::type = true>
StreamType __get_stream__(const std::filesystem::path &path) {
	return StreamType(path, std::ios::binary);
}

template<class StreamType, class Archive, typename std::enable_if<!__is_archive_binary_type__<Archive>(), bool>::type = true>
StreamType __get_stream__(const std::filesystem::path &path) {
	return StreamType(path);
}

template<class Archive, typename std::enable_if<!__is_archive_binary_type__<Archive>(), bool>::type = true>
void __start_node__(Archive &archive, const char *name) {
	archive.setNextName(name);
	archive.startNode();
}

template<class Archive, typename std::enable_if<__is_archive_binary_type__<Archive>(), bool>::type = true>
void __start_node__(Archive&, const char*) {
}

template<class Archive, typename std::enable_if<!__is_archive_binary_type__<Archive>(), bool>::type = true>
void __go_into_node__(Archive &archive) {
	archive.startNode();
}

template<class Archive, typename std::enable_if<__is_archive_binary_type__<Archive>(), bool>::type = true>
void __go_into_node__(Archive&) {
}

template<class Archive, typename std::enable_if<!__is_archive_binary_type__<Archive>(), bool>::type = true>
void __finish_node__(Archive &archive) {
	archive.finishNode();
}

template<class Archive, typename std::enable_if<__is_archive_binary_type__<Archive>(), bool>::type = true>
void __finish_node__(Archive&) {
}

template<class Archive, class T, typename std::enable_if<!__is_archive_binary_type__<Archive>(), bool>::type = true>
void __load_value__(Archive &archive, const T &object) {
	archive.loadValue(object);
}

template<class Archive, class T, typename std::enable_if<__is_archive_binary_type__<Archive>(), bool>::type = true>
void __load_value__(Archive&, const T&) {
}

}

template<class Archive>
class VariantWriter {
public:
	using ArchiveType = Archive;
private:
	std::ostream &stream;
	Archive archive;

	template<class T>
	inline void _call_write_function(const T &variant) {
		if (detail::__is_archive_binary_type__<Archive>())
			write_variant_binary_data<T, Archive>(variant, archive);
		else
			write_variant_text_data<T, Archive>(variant, archive);
	}

	template<class T>
	inline void _call_write_function_with_name(const T &variant, const String &variant_name) {
		if (detail::__is_archive_binary_type__<Archive>())
			write_variant_binary_data<T, Archive>(variant, archive);
		else
			write_variant_text_data_with_name<T, Archive>(variant, archive, variant_name);
	}
public:
	VariantWriter(std::ostream &stream): stream(stream), archive(stream) {
	}

	~VariantWriter() = default;

	void start_node(const char *name = nullptr) {
		if (name == nullptr)
			detail::__go_into_node__(archive);
		else
			detail::__start_node__(archive, name);
	}

	void finish_node() {
		detail::__finish_node__(archive);
	}

	template<class T>
	inline void write_with_name(const String &name, const T &variant) {
		_call_write_function_with_name(variant, name);
	}

	template<class T>
	VariantWriter &operator<<(const T &object) {
		__call_write_function(object);
		return *this;
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
class VariantReader {
public:
	using ArchiveType = Archive;
private:
	std::istream &stream;
	Archive archive;
public:
	VariantReader(std::istream &stream): stream(stream), archive(stream) {
	}

	~VariantReader() = default;

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
		detail::__load_value__(archive, t);
	}

	void go_into_node() {
		detail::__go_into_node__(archive);
	}

	void exit_out_of_node() {
		detail::__finish_node__(archive);
	}

	std::istream &get_stream() & {
		return stream;
	}

	std::istream &&get_stream() && {
		return std::move(stream);
	}

	const std::istream &get_stream() const & {
		return stream;
	}

	const std::istream &&get_stream() const && {
		return std::move(stream);
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
class VariantFileWriter {
public:
	using ArchiveType = Archive;
private:
	std::ofstream file;
	VariantWriter<ArchiveType> variant_writer;
public:
	VariantFileWriter(const std::filesystem::path &path): file(detail::__get_stream__<std::ofstream, ArchiveType>(path)), variant_writer(file) {
	}

	~VariantFileWriter() = default;

	void start_node(const char *name = nullptr) {
		variant_writer.start_node(name);
	}

	void finish_node() {
		variant_writer.finish_node();
	}

	template<class T>
	inline void write_with_name(const String &name, const T &variant) {
		variant_writer.write_with_name(name, variant);
	}

	template<class T>
	VariantFileWriter &operator<<(const T &object) {
		variant_writer << object;
		return *this;
	}

	ArchiveType &get_archive() & {
		return variant_writer.get_archive();
	}

	ArchiveType &&get_archive() && {
		return std::move(variant_writer.get_archive());
	}

	const ArchiveType &get_archive() const & {
		return variant_writer.get_archive();
	}

	const ArchiveType &&get_archive() const && {
		return std::move(variant_writer.get_archive());
	}
};

template<class Archive>
class VariantFileReader {
public:
	using ArchiveType = Archive;
private:
	std::ifstream file;
	VariantReader<ArchiveType> variant_reader;
public:
	VariantFileReader(const std::filesystem::path &path): file(detail::__get_stream__<std::ifstream, ArchiveType>(path)), variant_reader(file) {
	}

	~VariantFileReader() = default;

	template<class T>
	T read_value() {
		return variant_reader.template read_value<T>();
	}

	template<class T, class... Args>
	std::tuple<T, Args...> read_values() {
		return variant_reader.template read_values<T, Args...>();
	}

	template<class... Args>
	void read_to(Args&&... args) {
		variant_reader.read_to(args...);
	}

	template<class T>
	void load_value(T &object) {
		variant_reader.load_value(object);
	}

	void go_into_node() {
		variant_reader.go_into_node();
	}

	void exit_out_of_node() {
		variant_reader.exit_out_of_node();
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

	ArchiveType &get_archive() & {
		return variant_reader.get_archive();
	}

	ArchiveType &&get_archive() && {
		return std::move(variant_reader.get_archive());
	}

	const ArchiveType &get_archive() const & {
		return variant_reader.get_archive();
	}

	const Archive &&get_archive() const && {
		return std::move(variant_reader.get_archive());
	}
};

using PBVariantFileWriter = VariantFileWriter<cereal::PortableBinaryOutputArchive>;
using PBVariantFileReader = VariantFileWriter<cereal::PortableBinaryInputArchive>;
using BVariantFileWriter = VariantFileWriter<cereal::BinaryOutputArchive>;
using BVariantFileReader = VariantFileWriter<cereal::BinaryInputArchive>;
using JSONVariantFileWriter = VariantFileWriter<cereal::JSONOutputArchive>;
using JSONVariantFileReader = VariantFileWriter<cereal::JSONInputArchive>;
using XMLVariantFileWriter = VariantFileWriter<cereal::XMLOutputArchive>;
using XMLVariantFileReader = VariantFileWriter<cereal::XMLInputArchive>;

}
