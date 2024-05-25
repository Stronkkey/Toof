/*  This file is part of the Toof Engine. */
/** @file texture_format_loader.hpp */
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

#include <scene/resources/resource_format_loader.hpp>

#include <scene/resources/file_texture.hpp>

namespace Toof {

TOOF_DETAIL_RESOURCE_ID(Texture2D, 1000)
TOOF_DETAIL_RESOURCE_ID(FileTexture, 1001)

template<class ArchiveType>
struct TextureFormatLoader : public ResourceFormatLoader<ArchiveType> {
	std::unique_ptr<Texture2D> load_texture(int32_t id, ArchiveType &archive) const;
	std::unique_ptr<Resource> load(int32_t id, ArchiveType &archive) const override {
		return load_texture(id, archive);
	}
};

template<class ArchiveType>
std::unique_ptr<Texture2D> TextureFormatLoader<ArchiveType>::load_texture(int32_t id, ArchiveType &archive) const {
	TOOF_DETAIL_LOAD_TYPE_DEFAULT_ARGS(FileTexture)

	return {};
}

}
