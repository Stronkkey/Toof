#pragma once

#include <core/math/rect2.hpp>
#include <core/memory/optional.hpp>
#include <scene/resources/texture2d.hpp>

#include <unordered_map>

namespace sdl {

class TileSet;

class TileSetAtlasSource : public Resource {
public:
	struct TileData {
		Rect2i region;
		Angle rotation;
	};
private:
	Texture2D *texture;
	bool use_texture_padding;
	std::unordered_map<String, TileData> tiles;
public:
	TileSetAtlasSource() = default;
	~TileSetAtlasSource() = default;

	constexpr void set_texture(Texture2D *texture) {
		this->texture = texture;
	}

	[[nodiscard]] constexpr Texture2D *get_texture() const {
		return texture;
	}

	constexpr void set_use_texture_padding(const bool use_texture_padding) {
		this->use_texture_padding = use_texture_padding;
	}

	[[nodiscard]] constexpr bool is_texture_padding_used() const {
		return use_texture_padding;
	}

	[[nodiscard]] size_t get_tiles_count() const;
	[[nodiscard]] bool has_tile(const String &tile_name) const;

	bool create_tile(const String &tile_name, const TileData &tile_data);
	bool create_tile(String &&tile_name, TileData &&tile_data);

	[[nodiscard]] Optional<TileData> get_tile_data(const String &tile_name) const;
	[[nodiscard]] Optional<Rect2i> get_tile_region(const String &tile_name) const;
	[[nodiscard]] Optional<Angle> get_tile_rotation(const String &tile_name) const;

	void set_tile_data(const String &tile_name, const TileData &tile_data);
	void set_tile_data(const String &tile_name, TileData &&tile_data);

	void set_tile_texture_region(const String &tile_name, const Rect2i &region);
	void set_tile_texture_region(const String &tile_name, Rect2i &&region);

	void set_tile_texture_rotation(const String &tile_name, const Angle &rotation);
	void set_tile_texture_rotation(const String &tile_name, Angle &&rotation);
};

class TileSet : public Resource {
public:
	using size_type = size_t;
private:
	struct __CustomDataLayer__ {
		String name;
	};
	using __CustomDataLayerContainerType__ = std::unordered_map<size_type, __CustomDataLayer__>;
	using __AtlasSourceContainerType__ = std::unordered_map<size_type, std::unique_ptr<TileSetAtlasSource>>;

	__CustomDataLayerContainerType__ custom_data_layers;
	__AtlasSourceContainerType__ sources;
public:
	using custom_data_iterator = __CustomDataLayerContainerType__::iterator;

	TileSet() = default;
	~TileSet() = default;

	void add_custom_data_layer(const Optional<size_type> &to_position = NullOption);
	size_type add_source(std::unique_ptr<TileSetAtlasSource> &&source, const Optional<size_type> atlas_source_id_override = NullOption);

	Optional<size_type> get_custom_data_layer_by_name(const String &layer_name) const;
	Optional<String> get_custom_data_layer_name(const size_type index) const;
	size_type get_custom_layer_count() const;
	size_type get_next_custom_layer_index() const;

	size_type get_next_source_id() const;
	const std::unique_ptr<TileSetAtlasSource> &get_source(const size_type source_id) const;
	size_type get_source_count() const;
	bool has_source(const size_type source_id) const;

	void move_custom_data_layer(const size_type layer_index, const size_type to_position);

	void remove_custom_data_layer(const size_type layer_index);
	void remove_source(const size_type source_id);

	void set_custom_data_layer_name(const size_type layer_index, const String &layer_name);

	void set_source_id(const size_type source_id, const size_type new_source_id);
};

}