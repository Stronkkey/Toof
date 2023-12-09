#include <types/math_defs.hpp>

#include <SDL_timer.h>

namespace sdl {

namespace UtilityFunctions {

inline real_t get_passed_time() {
  real_t time = SDL_GetTicks64();
  time *= 0.001;
  return time;
}

}
}
