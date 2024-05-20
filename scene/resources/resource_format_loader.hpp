#pragma once

#include <cstdint>
#include <memory>

#include <cereal/cereal.hpp>

#define TOOF_DETAIL_RESOURCE_ID(type, id) \
template<> \
struct Toof::detail::__Defined_Ids__<id> : public std::true_type {}; \
template<> \
struct Toof::detail::__Resource_Id__<type> : public std::integral_constant<int32_t, id> {};

#define TOOF_RESOURCE_ID(type) (Toof::detail::__Resource_Id__<type>::value)

#define TOOF_DETAIL_LOAD_TYPE(type, id, archive) \
if (id == TOOF_RESOURCE_ID(type)) { \
	auto type_text = std::make_unique<type>(); \
	archive(*type_text); \
	return type_text; }

#define TOOF_DETAIL_LOAD_TYPE_DEFAULT_ARGS(type) TOOF_DETAIL_LOAD_TYPE(type, id, archive)

namespace Toof {

namespace detail {

template<int32_t __i>
struct __Defined_Ids__ : public std::false_type {
};

template<class ResourceType>
struct __Resource_Id__ : std::integral_constant<int32_t, 0> {
};

}

class Resource;

TOOF_DETAIL_RESOURCE_ID(Resource, 0)

template<class ArchiveType>
struct ResourceFormatLoader {
	virtual std::unique_ptr<Resource> load(int32_t, ArchiveType&) const {
		return std::make_unique<Resource>();
	}

	int32_t get_id(ArchiveType &archive) const {
		int32_t id;
		archive(id);
		return id;
	}

	std::unique_ptr<Resource> load_resource(ArchiveType &archive) const {
		return load(get_id(), archive);
	}

	template<class ResourceType>
	void save_resource(const ResourceType &resource, ArchiveType &archive) {
		constexpr const int32_t id = TOOF_RESOURCE_ID(ResourceType);

		archive(cereal::make_nvp("TextUnused", id));
		archive(resource);
	}
};

}