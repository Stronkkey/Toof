#pragma once

#ifndef SDL_LIBS_STRING_TYPE
#include <string>
#define SDL_LIBS_STRING_TYPE std::string
#endif

#ifndef SDL_LIBS_STRING_VIEW_TYPE
#include <string_view>
#define SDL_LIBS_STRING_VIEW_TYPE std::string_view
#endif

#ifndef STRINGIFY_STRING_TYPE
#define STRINGIFY_STRING_TYPE SDL_LIBS_STRING_TYPE
#endif

#ifndef STRINGIFY_STRING_VIEW_TYPE
#define STRINGIFY_STRING_VIEW_TYPE SDL_LIBS_STRING_VIEW_TYPE
#endif

namespace sdl {

using String = SDL_LIBS_STRING_TYPE;
using StringView = SDL_LIBS_STRING_VIEW_TYPE;

}
