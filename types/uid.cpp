#include "types/uid.hpp"

using namespace sdl;

bool uid::operator==(const uid &right_uid) const {
  return right_uid.id == id && right_uid.type == type;
}

String uid::to_string() const {
  return "UID(" + std::to_string(id) + ")";
}
