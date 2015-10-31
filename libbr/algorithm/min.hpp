/**
 * @file
 * @brief min
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>

#if defined(min)
#undef min
#  pragma message("macro \"min\" undefined")
#endif

namespace BR {

template< typename T, typename TComparator >
BR_CONSTEXPR_AFTER_CXX11 auto min(T const & x, T const & y, TComparator && comparator) -> T const & {
	return comparator(y, x) ? y : x;
}

template< typename T >
BR_CONSTEXPR_AFTER_CXX11 auto min(T const & x, T const & y) -> T const & {
	return min(x, y, Less<>());
}

} // namespace BR
