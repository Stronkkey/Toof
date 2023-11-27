#ifndef SERVERS_LIB
#define SERVERS_LIB

#include <vector>
#include "uid.hpp"

namespace sdl {

class Server {

protected:
  std::vector<uid> uids;

public:
  Server();
  ~Server();

  void free_uid(uid &freeing_uid);
  uid *create_uid();

};

}

#endif // !SERVERS_LIB
