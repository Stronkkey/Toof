/*  This file is part of the Toof Engine. */
/** @file tile_set.hpp */
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

#include <core/math/color.hpp>
#include <core/math/rect2.hpp>
#include <core/memory/optional.hpp>
#include <scene/resources/resource.hpp>
#include <core/math/angle.hpp>

#include <unordered_map>
#include <memory>

namespace Toof {

class TileSet;
class Texture2D;

String atlas_coords_to_string(const Vector2i::value_type x, const Vector2i::value_type y);

class TileSetAtlasSource : public Resource {
private:
	struct __AtlasTileData__ {
		Rect2i region;
		Angle rotation;
	};
public:
	using TilesType = std::unordered_map<String, __AtlasTileData__>;
private:
	std::unique_ptr<Texture2D> texture;
	bool use_texture_padding;
	TilesType tiles;

	uid _get_uid() const override;
public:
	TileSetAtlasSource();
	~TileSetAtlasSource();

	constexpr const TilesType &get_tiles() const & {
		return tiles;
	}

	constexpr const TilesType &&get_tiles() const && {
		return std::move(tiles);
	}

	void set_texture(std::unique_ptr<Texture2D> &&texture);

	[[nodiscard]] constexpr const std::unique_ptr<Texture2D> &get_texture() const {
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

	bool create_tile(const String &tile_name, const Rect2i &region, const Angle &rotation = Angle());
	bool create_tile(String &&tile_name, Rect2i &&region, Angle &&rotation = Angle());

	[[nodiscard]] Optional<Rect2i> get_tile_region(const String &tile_name) const;
	[[nodiscard]] Optional<Angle> get_tile_rotation(const String &tile_name) const;

	void set_tile_data(const String &tile_name, const __AtlasTileData__ &tile_data);
	void set_tile_data(const String &tile_name, __AtlasTileData__ &&tile_data);

	void set_tile_texture_region(const String &tile_name, const Rect2i &region);
	void set_tile_texture_region(const String &tile_name, Rect2i &&region);

	void set_tile_texture_rotation(const String &tile_name, const Angle &rotation);
	void set_tile_texture_rotation(const String &tile_name, Angle &&rotation);
};

class TileSet : public Resource {
public:
	using size_type = size_t;
	using SourceType = std::unique_ptr<TileSetAtlasSource>;
	using ConstSourceType = const SourceType;
	using ConstRefSourceType = ConstSourceType&;
private:
	struct __CustomDataLayer__ {
		String name;
	};
	using __CustomDataLayerContainerType__ = std::unordered_map<size_type, __CustomDataLayer__>;
	using __AtlasSourceContainerType__ = std::unordered_map<size_type, SourceType>;

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
	Optional<ConstRefSourceType> get_source(const size_type source_id) const;
	size_type get_source_count() const;
	bool has_source(const size_type source_id) const;

	void move_custom_data_layer(const size_type layer_index, const size_type to_position);

	void remove_custom_data_layer(const size_type layer_index);
	void remove_source(const size_type source_id);

	void set_custom_data_layer_name(const size_type layer_index, const String &layer_name);

	void set_source_id(const size_type source_id, const size_type new_source_id);
};

}