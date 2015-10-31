/**
 * @file
 * @brief max_min
 * @author Bromine0x23
 * @since 2015/10/23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/functional/less.hpp>

namespace BR {

template< typename T, typename TComparator >
BR_CONSTEXPR_AFTER_CXX11 auto max_min(T const & x, T const & y, TComparator && comparator) -> Pair< T const &, T const & > {
	return comparator(x, y) ? Pair< T const &, T const & >(y, x) : Pair< T const &, T const & >(x, y);
}

template< typename T >
BR_CONSTEXPR_AFTER_CXX11 auto max_min(T const & x, T const & y) -> Pair< T const &, T const & > {
	return max_min(x, y, Less<>());
}

} // namespace BR
