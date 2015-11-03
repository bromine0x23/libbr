#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/has_nothrow_move_assign.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

namespace Detail {
namespace Utility {

template< typename T >
inline void swap(T & a, T & b) noexcept(
	BooleanAnd< HasNothrowMoveAssign<T>, HasNothrowMoveConstructor<T> >::value
) {
	T t = move(a);
	a = move(b);
	b = move(t);
}

template< typename T, Size S >
inline void swap(T (&lhs)[S], T (&rhs)[S]) noexcept(noexcept(swap(*lhs, *rhs))) {
	for (Size i = 0; i < S; ++i) {
		swap(lhs[i], rhs[i]);
	}
}

} // namespace Utility
} // namespace Detail

template< typename T >
inline void swap(T & lhs, T & rhs) noexcept(noexcept(Detail::Utility::swap(lhs, rhs))) {
	Detail::Utility::swap(lhs, rhs);
}

} // namespace BR
