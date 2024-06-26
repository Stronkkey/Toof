/*  This file is part of the Toof Engine. */
/** @file tile_map.hpp */
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

#include <scene/2d/node2d.hpp>

#include <scene/resources/tile_set.hpp>

#include <core/memory/vector2_hash.hpp>

namespace Toof {

struct UniqueTile {
	String tile_name;
	TileSet::size_type source_id;

	UniqueTile(): tile_name(), source_id(-1) {
	}
	
	UniqueTile(const String &tile_name, const TileSet::size_type source_id): tile_name(tile_name), source_id(source_id) {
	}

	UniqueTile(String &&tile_name, const TileSet::size_type source_id): tile_name(std::move(tile_name)), source_id(source_id) {
	}

	bool operator==(const UniqueTile &unique_tile) {
		return tile_name == unique_tile.tile_name && source_id == unique_tile.source_id;
	}

	bool operator!=(const UniqueTile &unique_tile) {
		return tile_name != unique_tile.tile_name || source_id != unique_tile.source_id;
	}
};

struct TileData {
private:
	uid index;

	constexpr void set_index(const uid index) {
		this->index = index;
	}

	TileData() = default;

	friend class TileMap;
public:
	~TileData() = default;

	UniqueTile unique_tile;
	Transform2D transform;
	ColorV modulation;

	constexpr uid __get_index__() const {
		return index;
	}

	constexpr bool operator==(const TileData &right) const {
		return index == right.index;
	}
};

}

template<>
struct std::hash<Toof::UniqueTile> {
	size_t operator()(const Toof::UniqueTile &unique_tile) const noexcept {
		return std::hash<Toof::String>()(unique_tile.tile_name) ^ (std::hash<Toof::TileSet::size_type>()(unique_tile.source_id) << 1);
	}
};

template<>
struct std::hash<Toof::TileData> {
	size_t operator()(const Toof::TileData &tile_data) const noexcept {
		return tile_data.__get_index__();
	}
};

namespace Toof {

class TileMap : public Node2D {
public:
	using size_type = size_t;
private:
	uid index;
	std::unordered_map<uid, TileData> tiles;
	std::unique_ptr<TileSet> tile_set;

	uid _add_cell(const Transform2D &transform, const UniqueTile &unique_tile);
	uid _add_cell(Transform2D &&transform, UniqueTile &&unique_tile);

	Optional<Rect2i> _get_tile_texture_region(const UniqueTile &unique_tile) const;
	Optional<uid> _get_tile_texture_uid(const UniqueTile &unique_tile) const;
	void _draw_tile(const TileData &tile) const;
	void _draw_tiles() const;
protected:
	void _notification(const int what);
public:
	TileMap();
	~TileMap();

	bool create_grid(const Vector2i &tile_size, const TileSet::size_type source_id);

	Optional<uid> add_cell(const Vector2f &coords, const UniqueTile &unique_tile);
	Optional<uid> add_cell(Vector2f &&coords, UniqueTile &&unique_tile);
	Optional<uid> add_cell(const Transform2D &transform, const UniqueTile &unique_tile);
	Optional<uid> add_cell(Transform2D &&transform, UniqueTile &&unique_tile);

	void set_tile_set(std::unique_ptr<TileSet> &&new_tile_set);

	constexpr std::unique_ptr<TileSet> &get_tile_set() & {
		return tile_set;
	}
	
	std::unique_ptr<TileSet> get_tile_set() &&;
	Optional<TileData&> get_tile_data(uid tile_uid);
	Optional<const TileData&> get_tile_data(uid tile_uid) const;

	constexpr const std::unique_ptr<TileSet> &get_tile_set() const & {
		return tile_set;
	}

	void clear();
};

}
