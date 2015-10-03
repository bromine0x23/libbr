/**
 * @file
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/remove_reference.hpp>
#include <libbr/type_traits/is_copy_constructible.hpp>
#include <libbr/type_traits/is_nothrow_move_constructible.hpp>

namespace BR {

/**
 * @brief 强制转换为右值引用
 * @author Bromine0x23
 */
template< typename T >
constexpr RemoveReference<T> && move(T && t) noexcept {
	return static_cast< RemoveReference<T> && >(t);
}

template< typename T >
constexpr Conditional<
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
