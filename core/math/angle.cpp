#include <core/string/string_funcs.hpp>
#include <core/math/angle.hpp>

using namespace sdl;

Angle::operator String() const {
	return vformat("{}° angle ({} radians)", angle_degrees, Math::degrees_to_radians(angle_degrees));
}
