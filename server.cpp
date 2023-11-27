#include "server.hpp"
#include <algorithm>

using namespace sdl;

Server::Server() {
}

Server::~Server() {
}

void Server::free_uid(uid &uid) {
  auto iterator = std::remove(uids.begin(), uids.end(), uid);
  uids.erase(iterator, uids.end());
}

uid *Server::create_uid() {
  return new uid;
}
