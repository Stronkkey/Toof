#include <core/string_funcs.hpp>
#include <core/math/angle.hpp>

using namespace sdl;

String Angle::to_string() const {
	return vformat("{}° angle ({} radians)", angle_degrees, Math::degrees_to_radians(angle_degrees));
}

Angle::operator String() const {
	return vformat("{}° angle ({} radians)", angle_degrees, Math::degrees_to_radians(angle_degrees));
}
