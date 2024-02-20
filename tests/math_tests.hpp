#pragma once

#include <tests/base_tests.hpp>

namespace sdl {

namespace Tests {
/*
#define GET_PROPERTY(property_name, return_type) public: constexpr return_type get_##property_name() { return property_name; }
#define SET_PROPERTY(property_name, property_type) public: constexpr void set_##property_name(const property_type& new_##property_name) { property_name = new_##property_name; }
#define SET_GET_PROPERTY(property_name, property_type) private: property_type property_name; GET_PROPERTY(property_name, property_type); SET_PROPERTY(property_name, property_type); 
*/

OVERRIDE_TEST(ColorTest)
OVERRIDE_TEST(Geometry2DTest);
OVERRIDE_TEST(Rect2Test);
OVERRIDE_TEST(Transform2DTest);
OVERRIDE_TEST(Vector2Test);
OVERRIDE_TEST(MathTest);

}

}
