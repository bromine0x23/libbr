/**
 * @file
 * @brief swap
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/type_traits/_/forward_declare_is_swappable.hpp>
#include <libbr/type_traits/_/forward_declare_is_nothrow_swappable.hpp>
#include <libbr/utility/conjunction.hpp>
#include <libbr/utility/transfer.hpp>

namespace BR {

/**
 * @tparam T
 * @param a
 * @param b
 */
template< typename T >
constexpr inline void swap(T & a, T & b) noexcept(conjunction< HasNothrowMoveConstructor<T>, HasNothrowMoveAssignment<T> >) {
	T t = transfer(a);
	a = transfer(b);
	b = transfer(t);
}

/**
 * @tparam T
 * @tparam S
 * @param lhs
 * @param rhs
 */
template< typename T, Size S >
constexpr inline void swap(CArray<T, S> & lhs, CArray<T, S> & rhs) noexcept(boolean_constant< IsNothrowSwappable<T> >) {
	for (Size i = 0; i < S; ++i) {
		swap(lhs[i], rhs[i]);
	}
}

} // namespace BR

#include <libbr/type_traits/is_nothrow_swappable.hpp>
