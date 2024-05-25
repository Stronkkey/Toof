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
#include "core/math/vector2.hpp"
#include <scene/2d/tile_map.hpp>
#include <scene/resources/texture2d.hpp>

using namespace Toof;

TileMap::TileMap(): index(1), tiles(), tile_set(nullptr) {
}

TileMap::~TileMap() {
}

bool TileMap::create_grid(const Vector2i &tile_size, const TileSet::size_type source_id) {
	if (tile_size < Vector2i::ONE() || !tile_set || !is_inside_tree())
		return false;

	Optional<TileSet::ConstRefSourceType> source = tile_set->get_source(source_id);

	if (!source)
		return false;

	TileSet::ConstRefSourceType source_value = source.get_value();
	const std::unique_ptr<Texture2D> &texture = source_value->get_texture();

	if (!texture)
		return false;

	using v2int = Vector2i::value_type;
	Vector2i texture_size = texture->get_size();

	for (v2int x = 0; x < texture_size.x; x += tile_size.x)
		for (v2int y = 0; y < texture_size.y; y += tile_size.y) {
			String atlas_coords_string = atlas_coords_to_string(x, y);
			Rect2i rect = Rect2i(x, y, tile_size.x, tile_size.y);
			source_value->create_tile(std::move(atlas_coords_string), std::move(rect));
		}

	return true;
}

uid TileMap::_add_cell(const Transform2D &transform, const UniqueTile &unique_tile) {
	uid id = index++;
	TileData tile_data;

	tile_data.unique_tile = unique_tile;
	tile_data.transform = transform;
	tile_data.index = id;
	tile_data.modulation = ColorV::WHITE();
	
	const auto &iterator = tiles.insert_or_assign(std::move(id), std::move(tile_data));
	_draw_tile(iterator.first->second);

	return id;
}

uid TileMap::_add_cell(Transform2D &&transform, UniqueTile &&unique_tile) {
	uid id = index++;
	TileData tile_data;

	tile_data.unique_tile = std::move(unique_tile);
	tile_data.transform = std::move(transform);
	tile_data.index = id;
	tile_data.modulation = ColorV::WHITE();

	const auto &iterator = tiles.insert_or_assign(std::move(id), std::move(tile_data));
	_draw_tile(iterator.first->second);

	return id;
}

Optional<Rect2i> TileMap::_get_tile_texture_region(const UniqueTile &unique_tile) const {
	if (!tile_set)
		return NullOption;

	Optional<TileSet::ConstRefSourceType> tile_source = tile_set->get_source(unique_tile.source_id);
	return tile_source ? tile_source.get_value()->get_tile_region(unique_tile.tile_name) : NullOption;
}

Optional<uid> TileMap::_get_tile_texture_uid(const UniqueTile &unique_tile) const {
	if (!tile_set)
		return NullOption;

	Optional<TileSet::ConstRefSourceType> tile_source = tile_set->get_source(unique_tile.source_id);
	if (tile_source)
		return tile_source.get_value()->get_uid();

	return NullOption;
}

void TileMap::_draw_tile(const TileData &tile_data) const {
	Optional<Rect2i> texture_region = _get_tile_texture_region(tile_data.unique_tile);
	Optional<uid> texture_uid = _get_tile_texture_uid(tile_data.unique_tile);

	if (!texture_region || !texture_uid)
		return;

	draw_texture_rect(*texture_uid, *texture_region, tile_data.transform, tile_data.modulation);
}

void TileMap::_draw_tiles() const {
	for (const auto &iterator: tiles) {
		_draw_tile(iterator.second);
	}
}

void TileMap::_notification(const int what) {
	Node2D::_notification(what);

	if (what == NOTIFICATION_DRAW)
		_draw_tiles();
}

Optional<uid> TileMap::add_cell(const Vector2f &coords, const UniqueTile &unique_tile) {
	if (!tile_set || !tile_set->has_source(unique_tile.source_id))
		return NullOption;

	return _add_cell(Transform2D(Angle(), coords, Vector2f::ONE()), unique_tile);
}

Optional<uid> TileMap::add_cell(Vector2f &&coords, UniqueTile &&unique_tile) {
	if (!tile_set || !tile_set->has_source(unique_tile.source_id))
		return NullOption;

	return _add_cell(Transform2D(Angle(), std::move(coords), Vector2f::ONE()), std::move(unique_tile));
}

Optional<uid> TileMap::add_cell(const Transform2D &transform, const UniqueTile &unique_tile) {
	if (!tile_set || !tile_set->has_source(unique_tile.source_id))
		return NullOption;

	return _add_cell(transform, unique_tile);
}

Optional<uid> TileMap::add_cell(Transform2D &&transform, UniqueTile &&unique_tile) {
	if (!tile_set || !tile_set->has_source(unique_tile.source_id))
		return NullOption;

	return _add_cell(std::move(transform), std::move(unique_tile));
}

void TileMap::set_tile_set(std::unique_ptr<TileSet> &&new_tile_set) {
	tile_set = std::move(new_tile_set);
}

std::unique_ptr<TileSet> TileMap::get_tile_set() && {
	return std::move(tile_set);
}

Optional<TileData&> TileMap::get_tile_data(uid tile_uid) {
	auto iterator = tiles.find(tile_uid);

	if (iterator != tiles.end())
		return iterator->second;
	return NullOption;
}

void TileMap::clear() {
	tiles.clear();
}
