#pragma once

#ifndef TOOF_STRING_TYPE
#include <string>
#define TOOF_STRING_TYPE std::string
#endif

#ifndef TOOF_STRING_VIEW_TYPE
#include <string_view>
#define TOOF_STRING_VIEW_TYPE std::string_view
#endif

#ifndef STRINGIFY_STRING_TYPE
#define STRINGIFY_STRING_TYPE TOOF_STRING_TYPE
#endif

#ifndef STRINGIFY_STRING_VIEW_TYPE
#define STRINGIFY_STRING_VIEW_TYPE TOOF_STRING_VIEW_TYPE
#endif

namespace Toof {

using String = TOOF_STRING_TYPE;
using StringView = TOOF_STRING_VIEW_TYPE;

}
