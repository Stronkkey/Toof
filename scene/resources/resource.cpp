#include <scene/resources/resource.hpp>

#include <array>

using uid = Toof::uid;
using Resource = Toof::Resource;

uid Resource::_get_uid() const {
	return 0;
}

uid Resource::get_uid() const {
	return _get_uid();
}
