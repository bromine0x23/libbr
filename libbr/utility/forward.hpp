#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/is_lvalue_reference.hpp>
#include <libbr/type_operate/remove_reference.hpp>

namespace BR {

template< typename T >
BR_CONSTEXPR_AFTER_CPP11 T && forward(RemoveReference<T> & t) noexcept {
	return static_cast<T &&>(t);
}

template< typename T >
BR_CONSTEXPR_AFTER_CPP11 T && forward(RemoveReference<T> && t) noexcept {
	static_assert(NotLValueReference<T>::value, "Template argument substituting type is an lvalue reference type.");
	return static_cast<T &&>(t);
}

} // namespace BR
