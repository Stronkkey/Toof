#pragma once

#include <core/math/math_defs.hpp>
#include <core/math/transform2d.hpp>
#include <core/math/color.hpp>
#include <scene/resources/resource.hpp>

#include <SDL_render.h>

#include <memory>

namespace sdl {

template<class>
struct Rect2;
typedef Rect2<integer> Rect2i;
class RenderingServer;

class Texture2D : public Resource {
private:
	RenderingServer *rendering_server;

	virtual Vector2i _get_size() const {
		return Vector2i();
	}

	virtual integer _get_width() const {
		return 0;
	}

	virtual integer _get_height() const {
		return 0;
	}

	virtual uid _get_uid() const {
		return 0;
	}

	virtual SDL_Texture *_get_texture() const {
		return nullptr;
	}

	virtual void _draw(const uid, const uid, const SDL_RendererFlip, const ColorV&, const Transform2D&) {
	}

	virtual void _draw_region(const uid, const uid, const Rect2i&, const SDL_RendererFlip, const ColorV&, const Transform2D&) {
	}
protected:
	Texture2D();
public:
	~Texture2D() = default;

	constexpr void set_rendering_server(RenderingServer *rendering_server) {
		this->rendering_server = rendering_server;
	}

	constexpr RenderingServer *get_rendering_server() {
		return rendering_server;
	}

	constexpr const RenderingServer *get_rendering_server() const {
		return rendering_server;
	}

	inline Vector2i get_size() const {
		return _get_size();
	}

	inline int get_width() const {
		return _get_width();
	}

	inline int get_height() const {
		return _get_height();
	}

	inline uid get_uid() const {
		return _get_uid();
	}

	inline SDL_Texture *get_texture() const {
		return _get_texture();
	}

	inline void draw(const uid texture_uid,
	    const uid canvas_item_uid,
	    const SDL_RendererFlip flip = SDL_FLIP_NONE,
	    const ColorV &modulate = ColorV::WHITE(),
	    const Transform2D &transform = Transform2D::IDENTITY)
		{
			_draw(texture_uid, canvas_item_uid, flip, modulate, transform);
		}

	inline void draw_region(const uid texture_uid,
	    const uid canvas_item_uid,
	    const Rect2i &src_region,
	    const SDL_RendererFlip flip = SDL_FLIP_NONE,
	    const ColorV &modulate = ColorV::WHITE(),
	    const Transform2D &transform = Transform2D::IDENTITY)
	{
		_draw_region(texture_uid, canvas_item_uid, src_region, flip, modulate, transform);
	}
};

}
