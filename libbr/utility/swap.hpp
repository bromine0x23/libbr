/**
 * @file
 * @brief swap
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

/**
 * @tparam T
 * @param a
 * @param b
 */
template< typename T >
inline void swap(T & a, T & b) noexcept(BooleanAnd< HasNothrowMoveAssignment<T>, HasNothrowMoveConstructor<T> >{}) {
	T t = move(a);
	a = move(b);
	b = move(t);
}

/**
 * @tparam T
 * @tparam S
 * @param lhs
 * @param rhs
 */
template< typename T, Size S >
inline void swap(CArray<T, S> & lhs, CArray<T, S> & rhs) noexcept(noexcept(swap(*lhs, *rhs))) {
	for (Size i = 0; i < S; ++i) {
		swap(lhs[i], rhs[i]);
	}
}

} // namespace BR
