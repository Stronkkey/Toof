#include <cstdlib>

namespace sdl {

template<class T>
struct MemoryPointer {
  T *reference;

  MemoryPointer() {
    reference = nullptr;
  }

  MemoryPointer(T *type) {
    reference = type;
  }
};

template<class T>
struct Ref {

  MemoryPointer<T> mem_pointer;

  Ref() {
    mem_pointer = MemoryPointer<T>();
  }

  Ref(T *type) {
    mem_pointer = MemoryPointer<T>(type);
  }

  T *operator->() const {
    return mem_pointer.reference;
  }

  operator T() {
    return mem_pointer.reference;
  }

  void operator delete(void* ptr) {
    std::free(ptr);
  }

  bool is_valid() const {
    return mem_pointer.reference != nullptr;
  }

  bool is_null() const {
    return mem_pointer.reference == nullptr;
  }

  T *get_reference() const {
    return mem_pointer.reference;
  }

};

};
