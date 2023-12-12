#ifndef TEXTURE
#define TEXTURE

#include <types/rect2.hpp>
#include <types/transform2d.hpp>
#include <types/uid.hpp>

#include <SDL_image.h>

#include <memory>

namespace sdl {

class RenderingServer;

struct Texture {
  SDL_Texture *texture_reference;
  Vector2i size;
  uint32_t format;
};

class ILoadableTexture {
public:
  virtual void load_from_path(const std::string &file_path) =0;
};

class Texture2D {

protected:
  RenderingServer *rendering_server;

public:
  struct DrawOperation {
    uid *canvas_item;
    Transform2D *transform;
    SDL_RendererFlip flip;

    inline bool can_draw() const { return canvas_item && transform; }
  };

  struct RectDrawOperation {
    uid *canvas_item;
    Rect2i *src_region;
    Transform2D *transform;
    SDL_RendererFlip flip;

    inline bool can_draw() const { return canvas_item && src_region && transform; }
  };

  void set_rendering_server(RenderingServer *rendering_server);

  virtual Vector2i get_size() const { return Vector2i::ZERO; }
  virtual int get_width() const { return int(get_size().x); }
  virtual int get_height() const { return int(get_size().y); }
  virtual uid get_uid() const { return uid(); }

  virtual void draw(const DrawOperation&) const {}
  virtual void draw_region(const RectDrawOperation&) const {}

};

class UidTexture : public Texture2D, public ILoadableTexture {

private:
  uid texture_uid;

public:
  UidTexture();
  UidTexture(const uid &from_uid);

  Vector2i get_size() const override;
  uid get_uid() const override { return texture_uid; }

  void draw(const DrawOperation &draw_operation) const override;
  void draw_region(const RectDrawOperation &rect_draw_operation) const override;

  void load_from_path(const std::string &file_path) override;
};

}

#endif // !TEXTURE
