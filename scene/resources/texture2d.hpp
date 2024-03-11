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
public:
	virtual Vector2i get_size(const std::unique_ptr<RenderingServer>& = nullptr) const;
	virtual int get_width(const std::unique_ptr<RenderingServer>& = nullptr) const;
	virtual int get_height(const std::unique_ptr<RenderingServer>& = nullptr) const;
	virtual uid get_uid() const;
	virtual SDL_Texture *get_texture(const std::unique_ptr<RenderingServer>& = nullptr) const;

	virtual void draw(const std::unique_ptr<RenderingServer> &rendering_server,
	    const uid texture_uid,
	    const uid canvas_item_uid,
	    const SDL_RendererFlip flip = SDL_FLIP_NONE,
	    const ColorV &modulate = ColorV::WHITE(),
	    const Transform2D &transform = Transform2D::IDENTITY) const;

	virtual void draw_region(const std::unique_ptr<RenderingServer> &rendering_server,
	    const uid texture_uid,
	    const uid canvas_item_uid,
	    const Rect2i &src_region,
	    const SDL_RendererFlip flip = SDL_FLIP_NONE,
	    const ColorV &modulate = ColorV::WHITE(),
	    const Transform2D &transform = Transform2D::IDENTITY) const;
};

}
