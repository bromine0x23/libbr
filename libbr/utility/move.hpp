#pragma once

#include <libbr/config.hpp>

#include <libbr/type_operate/remove_reference.hpp>

namespace BR {

template< typename type >
constexpr TypeOperate::RemoveReference< type > && move(type && t) noexcept {
	return static_cast< TypeOperate::RemoveReference< type > && >(t);
}

} // namespace BR
