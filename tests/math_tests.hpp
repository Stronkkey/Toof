#pragma once

#include <tests/base_tests.hpp>

namespace sdl {

namespace Tests {
/*
#define GET_PROPERTY(property_name, return_type) public: constexpr return_type get_##property_name() { return property_name; }
#define SET_PROPERTY(property_name, property_type) public: constexpr void set_##property_name(const property_type& new_##property_name) { property_name = new_##property_name; }
#define SET_GET_PROPERTY(property_name, property_type) private: property_type property_name; GET_PROPERTY(property_name, property_type); SET_PROPERTY(property_name, property_type); 
*/

__OVERRIDE_TEST__(ColorTest)
__OVERRIDE_TEST__(Geometry2DTest);
__OVERRIDE_TEST__(Rect2Test);
__OVERRIDE_TEST__(Transform2DTest);
__OVERRIDE_TEST__(Vector2Test);
__OVERRIDE_TEST__(MathTest);

}

}
