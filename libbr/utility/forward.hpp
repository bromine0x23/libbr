#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/is_lvalue_reference.hpp>
#include <libbr/type_operate/remove_reference.hpp>

namespace BR {

template< typename T >
constexpr T && forward(TypeOperate::RemoveReference< T > & t) noexcept {
	return static_cast< T && >(t);
}

template< typename T >
constexpr T && forward(TypeOperate::RemoveReference< T > && t) noexcept {
	static_assert(TypeOperate::NotLValueReference< T >::value, "Template argument substituting type is an lvalue reference type.");
	return static_cast< T && >(t);
}

} // namespace BR
