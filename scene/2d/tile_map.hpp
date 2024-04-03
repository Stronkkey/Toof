#pragma once

#include <scene/2d/node2d.hpp>

#include <scene/resources/tile_set.hpp>

#include <core/memory/vector2_hash.hpp>

namespace sdl {

struct UniqueTile {
	String tile_name;
	TileSet::size_type source_id;

	UniqueTile(): tile_name(), source_id(-1) {
	}
	
	UniqueTile(const Vector2i &tile_name, const TileSet::size_type source_id): tile_name(tile_name), source_id(source_id) {
	}

	UniqueTile(Vector2i &&tile_name, const TileSet::size_type source_id): tile_name(std::move(tile_name)), source_id(source_id) {
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
struct std::hash<sdl::UniqueTile> {
	size_t operator()(const sdl::UniqueTile &unique_tile) const noexcept {
		return std::hash<sdl::String>()(unique_tile.tile_name) ^ (std::hash<sdl::TileSet::size_type>()(unique_tile.source_id) << 1);
	}
};

template<>
struct std::hash<sdl::TileData> {
	size_t operator()(const sdl::TileData &tile_data) const noexcept {
		return tile_data.__get_index__();
	}
};

namespace sdl {

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

	constexpr const std::unique_ptr<TileSet> &get_tile_set() const & {
		return tile_set;
	}

	void clear();
};

}
