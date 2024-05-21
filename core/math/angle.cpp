#include <core/math/angle.hpp>

#include <stringify/format.hpp>

using namespace Toof;

std::ostream &Toof::operator<<(std::ostream &stream, const Toof::Angle &angle) {
	S_STREAM_FORMAT(stream, "{}* angle ({} radians)", angle.get_angle_degrees(), angle.get_angle_radians());
	return stream;
}

Angle::operator String() const {
	return S_FORMAT("{}° angle ({} radians)", angle_degrees, Math::degrees_to_radians(angle_degrees));
}
