/**
 * @file
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/remove_reference.hpp>
#include <libbr/type_traits/has_copy_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>

namespace BR {

/**
 * @brief 强制转换为右值引用
 * @author Bromine0x23
 */
template< typename T >
constexpr auto move(T && t) noexcept -> RemoveReference<T> && {
	return static_cast< RemoveReference<T> && >(t);
}

template< typename T >
constexpr auto move_if_noexcept(T & t) noexcept -> Conditional< BooleanAnd< NoNothrowMoveConstructor<T>, HasCopyConstructor<T> >, T const &, T && > {
	return move(t);
}

} // namespace BR
