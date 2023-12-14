#ifndef TEXTURE_H
#define TEXTURE_H

#include <rendering/rendering_server.hpp>

#include <SDL_image.h>

namespace sdl {

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
  void set_rendering_server(RenderingServer *rendering_server);

  virtual Vector2i get_size() const { return Vector2i::ZERO; }
  virtual int get_width() const { return int(get_size().x); }
  virtual int get_height() const { return int(get_size().y); }
  virtual uid get_uid() const { return 0; }

  virtual void draw(const RenderingServer::CanvasItemTexture&) const {}
  virtual void draw_region(const RenderingServer::CanvasItemRectTexture&) const {}

};

class UidTexture : public Texture2D, public ILoadableTexture {

private:
  uid texture_uid;

public:
  UidTexture();
  UidTexture(const uid from_uid);

  Vector2i get_size() const override;
  uid get_uid() const override { return texture_uid; }

  void draw(const RenderingServer::CanvasItemTexture &draw_operation) const override;
  void draw_region(const RenderingServer::CanvasItemRectTexture &rect_draw_operation) const override;

  void load_from_path(const std::string &file_path) override;
};

}

#endif // !TEXTURE_H
