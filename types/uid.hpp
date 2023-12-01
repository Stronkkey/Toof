#ifndef UID
#define UID

#include <cstdint>
#include <functional>

namespace sdl {

enum UidType {
  UID_RENDERING,
  UID_RENDERING_TEXTURE,
  UID_AUTO
};

struct uid {
  uint64_t id;
  UidType type;

  bool operator==(const uid &right_uid) const;

};
}

namespace std {

template<>
struct hash<sdl::uid> {
  size_t operator()(const sdl::uid &uid) const noexcept {
    size_t hash_id = hash<uint64_t>{}(uid.id);
    size_t hash_type = hash<int>{}(uid.type);
    return hash_id ^ (hash_type << 1);
  }
};
}

#endif // !UID
