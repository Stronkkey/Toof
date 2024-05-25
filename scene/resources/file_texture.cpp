/*  This file is part of the Toof Engine. */
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
#include <scene/resources/file_texture.hpp>
#include <servers/rendering_server.hpp>

using namespace Toof;

FileTexture::FileTexture() {
}

FileTexture::FileTexture(RenderingServer *rendering_server) {
	set_rendering_server(rendering_server);
}

FileTexture::FileTexture(RenderingServer *rendering_server, const String &texture_path): texture_uid(0), texture_path(texture_path) {
	set_rendering_server(rendering_server);
	load_from_path(this->texture_path);
}

FileTexture::FileTexture(RenderingServer *rendering_server, String &&texture_path): texture_uid(), texture_path(std::move(texture_path)) {
	set_rendering_server(rendering_server);
	load_from_path(this->texture_path);
}

Vector2i FileTexture::_get_size() const {
	Optional<RenderingServer::TextureInfo> texture_info;

	if (get_rendering_server())
		texture_info = get_rendering_server()->get_texture_info_from_uid(texture_uid);
	
	return texture_info ? texture_info->size : Vector2i();
}

SDL_Texture *FileTexture::_get_texture() const {
	if (get_rendering_server()) {
		Optional<RenderingServer::TextureInfo> texture_info = get_rendering_server()->get_texture_info_from_uid(texture_uid);
		return texture_info ? texture_info->texture : nullptr;
	}

	return nullptr;
}

void FileTexture::_draw(const uid texture_uid,
	const uid canvas_item_uid,
	const SDL_RendererFlip flip,
	const ColorV &modulate,
	const Transform2D &transform)
{
	if (get_rendering_server())
		get_rendering_server()->canvas_item_add_texture(texture_uid, canvas_item_uid, flip, modulate, transform);
}

void FileTexture::_draw_region(const uid texture_uid,
	const uid canvas_item_uid,
	const Rect2i &src_region,
	const SDL_RendererFlip flip,
	const ColorV &modulate,
	const Transform2D &transform )
{
	if (get_rendering_server())
		get_rendering_server()->canvas_item_add_texture_region(texture_uid, canvas_item_uid, src_region, flip, modulate, transform);
}

void FileTexture::_on_rendering_server_set() {
	if (!get_rendering_server())
		return;

	Optional<uid> text_uid = get_rendering_server()->load_texture_from_path(texture_path);
	texture_uid = text_uid.value_or(0);
}

void FileTexture::load_from_path(const String &file_path) {
	texture_path = file_path;
	if (!get_rendering_server())
		return;

	Optional<uid> text_uid = get_rendering_server()->load_texture_from_path(file_path);
	texture_uid = text_uid.value_or(0);
}

void FileTexture::load_from_path(String &&file_path) {
	texture_path = std::move(file_path);
	if (!get_rendering_server())
		return;

	Optional<uid> text_uid = get_rendering_server()->load_texture_from_path(texture_path);
	texture_uid = text_uid.value_or(0);
}
