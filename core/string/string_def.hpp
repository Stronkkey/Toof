#pragma once

#ifndef STRING_TYPE
#include <string>
#define STRING_TYPE std::string
#endif

#ifndef CUSTOM_STRING_VIEW_TYPE
#include <string_view>
#define STRING_VIEW_TYPE std::string_view
#endif

namespace sdl {

typedef STRING_TYPE String;
typedef STRING_VIEW_TYPE StringView;

}