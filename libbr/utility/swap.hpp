#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/has_nothrow_move_assignment.hpp>
#include <libbr/type_operate/has_nothrow_move_constructor.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

namespace Detail {

template< typename T >
inline void swap(T & a, T & b) noexcept(
	TypeOperate::BooleanAnd<
		TypeOperate::HasNothrowMoveAssignment< T >,
		TypeOperate::HasNothrowMoveConstructor< T >
	>::value
) {
	T t = move(a);
	a = move(b);
	b = move(t);
}

template< typename T, Size S >
inline void swap(T (&lhs)[S], T (&rhs)[S]) noexcept(noexcept(swap(*lhs, *rhs))) {
	for (Size i = 0; i < S; ++i) {
		swap_imp(lhs[i], rhs[i]);
	}
}

} // namespace Detail

template< typename T >
inline void swap(T & lhs, T & rhs) noexcept(noexcept(Detail::swap(lhs, rhs))) {
	Detail::swap(lhs, rhs);
}

} // namespace BR
