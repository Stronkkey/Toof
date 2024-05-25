/*  This file is part of the Toof Engine. */
/** @file file_texture.hpp */
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

#include <scene/resources/texture2d.hpp>

#include <cereal/cereal.hpp>

#include <cereal/types/string.hpp>

namespace Toof {

class FileTexture : public Texture2D {
private:
	uid texture_uid;
	String texture_path;

	Vector2i _get_size() const override;

	inline uid _get_uid() const override {
		return texture_uid;
	}

	SDL_Texture *_get_texture() const override;
	void _draw(const uid, const uid, const SDL_RendererFlip, const ColorV&, const Transform2D&) override;
	void _draw_region(const uid, const uid, const Rect2i&, const SDL_RendererFlip, const ColorV&, const Transform2D&) override;
protected:
	void _on_rendering_server_set() override;
public:
	FileTexture();
	FileTexture(RenderingServer *rendering_server);
	FileTexture(RenderingServer *rendering_server, const String &texture_path);
	FileTexture(RenderingServer *rendering_server, String &&texture_path);

	constexpr const String &get_texture_path() const & {
		return texture_path;
	}

	inline String get_texture_path() const && {
		return std::move(texture_path);
	}

	void load_from_path(const String &file_path);
	void load_from_path(String &&file_path);
};

}

namespace cereal {

template<class Archive>
void load(Archive &archive, Toof::FileTexture &file_texture) {
	Toof::String file_path;
	archive(file_path);
	file_texture.load_from_path(std::move(file_path));
}

template<class Archive>
void save(Archive &archive, const Toof::FileTexture &file_texture) {
	archive(file_texture.get_texture_path());
}

}
