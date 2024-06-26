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
#include <scene/resources/tile_set.hpp>
#include <scene/resources/texture2d.hpp>
#include <stringify/to_string.hpp>

using namespace Toof;

String Toof::atlas_coords_to_string(const Vector2i::value_type x, const Vector2i::value_type y) {
	return S_TO_STRING(x, y);
}

uid TileSetAtlasSource::_get_uid() const {
	return texture ? texture->get_uid() : 0;
}

TileSetAtlasSource::TileSetAtlasSource(): texture(), use_texture_padding(false), tiles() {
}

TileSetAtlasSource::~TileSetAtlasSource() {
}

void TileSetAtlasSource::set_texture(std::unique_ptr<Texture2D> &&texture2d) {
	texture = std::move(texture2d);
}

size_t TileSetAtlasSource::get_tiles_count() const {
	return tiles.size();
}

bool TileSetAtlasSource::create_tile(const String &tile_name, const Rect2i &region, const Angle &rotation) {
	__AtlasTileData__ tile_data;
	tile_data.rotation = rotation;
	tile_data.region = region;

	return tiles.insert_or_assign(tile_name, std::move(tile_data)).second;
}

bool TileSetAtlasSource::create_tile(String &&tile_name, Rect2i &&region, Angle &&rotation) {
	__AtlasTileData__ tile_data;
	tile_data.rotation = std::move(rotation);
	tile_data.region = std::move(region);

	return tiles.insert_or_assign(std::move(tile_name), std::move(tile_data)).second;
}

Optional<Rect2i> TileSetAtlasSource::get_tile_region(const String &tile_name) const {
	const auto &iterator = tiles.find(tile_name);
	return iterator != tiles.end() ? iterator->second.region : Optional<Rect2i>();
}

Optional<Angle> TileSetAtlasSource::get_tile_rotation(const String &tile_name) const {
	const auto &iterator = tiles.find(tile_name);
	return iterator != tiles.end() ? iterator->second.rotation : Optional<Angle>();
}

void TileSetAtlasSource::set_tile_data(const String &tile_name, const __AtlasTileData__ &tile_data) {
	const auto &iterator = tiles.find(tile_name);
	if (iterator != tiles.end())
		iterator->second = tile_data;
}

void TileSetAtlasSource::set_tile_data(const String &tile_name, __AtlasTileData__ &&tile_data) {
	const auto &iterator = tiles.find(tile_name);
	if (iterator != tiles.end())
		iterator->second = std::move(tile_data);
}

void TileSetAtlasSource::set_tile_texture_region(const String &tile_name, const Rect2i &region) {
	const auto &iterator = tiles.find(tile_name);
	if (iterator != tiles.end())
		iterator->second.region = region;
}

void TileSetAtlasSource::set_tile_texture_region(const String &tile_name, Rect2i &&region) {
	const auto &iterator = tiles.find(tile_name);
	if (iterator != tiles.end())
		iterator->second.region = std::move(region);
}

void TileSetAtlasSource::set_tile_texture_rotation(const String &tile_name, const Angle &rotation) {
	const auto &iterator = tiles.find(tile_name);
	if (iterator != tiles.end())
		iterator->second.rotation = rotation;
}

void TileSetAtlasSource::set_tile_texture_rotation(const String &tile_name, Angle &&rotation) {
	const auto &iterator = tiles.find(tile_name);
	if (iterator != tiles.end())
		iterator->second.rotation = std::move(rotation);
}


/////////////////////////////////

void TileSet::add_custom_data_layer(const Optional<size_type> &to_position) {
	size_type position = to_position.value_or(get_next_custom_layer_index());
	custom_data_layers.insert({position, __CustomDataLayer__()});
}

TileSet::size_type TileSet::add_source(std::unique_ptr<TileSetAtlasSource> &&source, const Optional<size_type> atlas_source_id_override) {
	size_type position = atlas_source_id_override.value_or(get_next_custom_layer_index());
	
	sources.insert({position, std::move(source)});

	return position;
}

Optional<TileSet::size_type> TileSet::get_custom_data_layer_by_name(const String &layer_name) const {
	for (const auto &iterator: custom_data_layers)
		if (iterator.second.name == layer_name)
			return iterator.first;

	return NullOption;
}

Optional<String> TileSet::get_custom_data_layer_name(const size_type layer_index) const {
	const auto &iterator = custom_data_layers.find(layer_index);
	return iterator != custom_data_layers.end() ? iterator->second.name : Optional<String>();
}

TileSet::size_type TileSet::get_custom_layer_count() const {
	return custom_data_layers.size();
}

TileSet::size_type TileSet::get_next_custom_layer_index() const {
	size_type position = custom_data_layers.size();
	if (!custom_data_layers.count(position))
		return position;

	position = 0;

	while (custom_data_layers.count(position))
		position++;

	return position;
}

TileSet::size_type TileSet::get_next_source_id() const {
	size_type position = sources.size();
	if (!sources.count(position))
		return position;

	position = 0;

	while (sources.count(position))
		position++;

	return position;
}

Optional<TileSet::ConstRefSourceType> TileSet::get_source(const size_type source_id) const {
	const auto &iterator = sources.find(source_id);
	if (iterator != sources.end())
		return iterator->second;

	return NullOption;
}

TileSet::size_type TileSet::get_source_count() const {
	return sources.size();
}

bool TileSet::has_source(const size_type source_id) const {
	return sources.count(source_id);
}

void TileSet::move_custom_data_layer(const size_type layer_index, const size_type to_position) {
	if (layer_index == to_position)
		return;

	const auto &iterator = custom_data_layers.find(layer_index);
	if (iterator != custom_data_layers.end()) {
		custom_data_layers.insert_or_assign(to_position, iterator->second);
		custom_data_layers.erase(iterator);
	}
}

void TileSet::remove_custom_data_layer(const size_type layer_index) {
	custom_data_layers.erase(layer_index);
}

void TileSet::remove_source(const size_type source_id) {
	sources.erase(source_id);
}

void TileSet::set_custom_data_layer_name(const size_type layer_index, const String &layer_name) {
	const auto &iterator = custom_data_layers.find(layer_index);
	if (iterator != custom_data_layers.end())
		iterator->second.name = layer_name;
}

void TileSet::set_source_id(const size_type source_id, const size_type new_source_id) {
	if (source_id == new_source_id)
		return;

	const auto &iterator = sources.find(source_id);
	if (iterator != sources.end()) {
		sources.insert_or_assign(new_source_id, std::move(iterator->second));
		sources.erase(iterator);
	}
}