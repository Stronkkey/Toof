#include "math_defs.hpp"

namespace sdl {

enum UidType {
  UID_RENDERING,
  UID_AUTO
};

struct uid {
  uint_t id;
  UidType type;

  bool operator==(const uid &right_uid) const;

};

}
