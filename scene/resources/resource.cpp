#include <scene/resources/resource.hpp>

sdl::uid sdl::Resource::_get_uid() const {
	return 0;
}

sdl::uid sdl::Resource::get_uid() const {
	return _get_uid();
}