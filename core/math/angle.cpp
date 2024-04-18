#include <core/math/angle.hpp>

#include <stringify/format.hpp>

using namespace sdl;

Angle::operator String() const {
	return S_FORMAT("{}° angle ({} radians)", angle_degrees, Math::degrees_to_radians(angle_degrees));
}
