#pragma once

#include <scene/2d/node2d.hpp>

namespace sdl {

class Texture2D;

class Sprite2D : public Node2D {
private:
	std::shared_ptr<Texture2D> texture;

	Rect2i texture_region;
	Transform2D texture_transform;
	SDL_RendererFlip flip;
	bool centered;

	Transform2D _get_placement_texture_transform() const;
	void _draw_full_texture() const;
	void _draw_rect_texture() const;
	void _draw_texture() const;
	void _notification(const int what) override;
public:
	Sprite2D();
	~Sprite2D() = default;

	Signal<> texture_changed;

	void set_texture(const std::shared_ptr<Texture2D> &new_texture);
	constexpr const std::shared_ptr<Texture2D> &get_texture() const {
		return texture;
	}

	void set_texture_region(const Rect2i &new_texture_region);
	constexpr const Rect2i &get_texture_region() const {
		return texture_region;
	}

	void set_offset(const Vector2f &new_offset);
	constexpr const Vector2f &get_offset() const {
		return texture_transform.origin;
	}

	void set_texture_rotation(const Angle new_rotation);
	constexpr Angle get_texture_rotation() const {
		return texture_transform.rotation;
	}

	void set_texture_scale(const Vector2f &new_texture_scale);
	constexpr const Vector2f &get_texture_scale() const {
		return texture_transform.scale;
	}

	void set_texture_transform(const Transform2D &new_texture_transform);
	constexpr const Transform2D &get_texture_transform() const {
		return texture_transform;
	}

	void set_flip(const SDL_RendererFlip new_flip);
	constexpr SDL_RendererFlip get_flip() const {
		return flip;
	}

	void set_centered(const bool new_centered);
	constexpr bool is_centered() const {
		return centered;
	}
};

}
