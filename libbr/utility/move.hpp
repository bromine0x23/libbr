#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/is_copy_constructible.hpp>
#include <libbr/type_operate/is_nothrow_move_constructible.hpp>
#include <libbr/type_operate/remove_reference.hpp>

namespace BR {

template< typename T >
BR_CONSTEXPR_AFTER_CXX11 RemoveReference<T> && move(T && t) noexcept {
	return static_cast< RemoveReference<T> && >(t);
}

template< typename T >
inline BR_CONSTEXPR_AFTER_CXX11
Conditional<
	BooleanAnd<
		NotNothrowMoveConstructible<T>,
		IsCopyConstructible<T>
	>,
	T const &,
	T &&
> move_if_noexcept(T & t) noexcept {
	return move(t);
}

} // namespace BR
