/**
 * @file
 * @brief 完美转发
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_lvalue_reference.hpp>
#include <libbr/type_traits/remove_reference.hpp>

namespace BR {

/**
 * @brief 完美转发
 */
template< typename T >
constexpr auto forward(RemoveReference<T> & t) noexcept -> T && {
	return static_cast< T && >(t);
}

/**
 * @brief 完美转发
 */
template< typename T >
constexpr auto forward(RemoveReference<T> && t) noexcept -> T && {
	static_assert(NotLValueReference<T>{}, "Template argument substituting type is an lvalue reference type.");
	return static_cast< T && >(t);
}

} // namespace BR
