/*  This file is part of the Toof Engine. */
/** @file resource_format_loader.hpp */
/*
  BSD 3-Clause License

  Copyright (c) 2024-present, Stronkkey and Contributors

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
      list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
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