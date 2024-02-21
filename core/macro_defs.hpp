#pragma once

#ifndef CUSTOM_STRING_TYPE
#include <string>
#define CUSTOM_STRING_TYPE std::string
#endif

namespace sdl {

typedef CUSTOM_STRING_TYPE String;

#define FAIL_COND(condition) if (condition) return;
#define RETURN_FAIL_COND(condition, return_value) if (condition) return return_value;

}