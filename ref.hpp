#include <cstdint>

namespace sdl {

template<class T>
struct Ref {

  T *reference;

  Ref() {
    reference = nullptr;
  }

  Ref(T *type) {
    reference = type;
  }

  T *operator->() const {
    return reference;
  }

  operator T() {
    return reference;
  }

  bool is_valid() const {
    return reference != nullptr;
  }

  bool is_null() const {
    return reference == nullptr;
  }

};

};
