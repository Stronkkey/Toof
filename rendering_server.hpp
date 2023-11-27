#include "server.hpp"

namespace sdl {

class RenderingServer : public Server {
private:
  static RenderingServer *rendering_server;

public:
  RenderingServer();
  ~RenderingServer();

  static RenderingServer *get_singleton();

};
}
