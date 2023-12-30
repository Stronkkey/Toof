#pragma once

namespace sdl {

#define ERROR_FAIL_CONDITION(condition) if (condition) return;
#define ERROR_FAIL_CONDITION_RETURN(condition, return_value) if (condition) return return_value;

}