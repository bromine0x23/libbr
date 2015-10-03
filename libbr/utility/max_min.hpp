/**
 * @file
 * @author Bromine0x23
 * @since 2015/10/2
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/pair.hpp>

namespace BR

#if defined(max)
#undef max
#pragma message("macro \"max\" undefined")
#endif

#if defined(min)
#undef min
#pragma message("macro \"min\" undefined")
#endif

template< typename T >
constexpr T const & max(T const & lhs, T const & rhs) {
	return (lhs < rhs) ? rhs : lhs;
}

template< typename T >
constexpr T const & min(T const & lhs, T const & rhs) {
	return (rhs < lhs) ? rhs : lhs;
}

template< typename T >
BR_CONSTEXPR_AFTER_CXX11 Pair< T const &, T const & > maxmin(T const & lhs, T const & rhs) {
	return (rhs < lhs)
		? Pair< T const &, T const & >(rhs, lhs)
		: Pair< T const &, T const & >(lhs, rhs);
}

template< typename T, typename TComparator >
BR_CONSTEXPR_AFTER_CXX11 T const & max(T const & lhs, T const & rhs, TComparator comparator) {
	return comparator(lhs, rhs) ? rhs : lhs;
}

template< typename T, typename TComparator >
BR_CONSTEXPR_AFTER_CXX11 T const & min(T const & lhs, T const & rhs, TComparator comparator) {
	return comparator(rhs, lhs) ? rhs : lhs;
}

template< typename T, typename TComparator >
BR_CONSTEXPR_AFTER_CXX11 Pair< T const &, T const & > maxmin(T const & lhs, T const & rhs, TComparator comparator) {
	return comparator(rhs, lhs)
		? Pair< T const &, T const & >(rhs, lhs)
		: Pair< T const &, T const & >(lhs, rhs);
}

} // namespace BR
