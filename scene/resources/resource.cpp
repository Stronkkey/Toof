#include <scene/resources/resource.hpp>

#include <array>

using uid = sdl::uid;
using Resource = sdl::Resource;

uid Resource::_get_uid() const {
	return 0;
}

uid Resource::get_uid() const {
	class_to_bytes(*this);
	return _get_uid();
}
