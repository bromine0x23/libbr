/**
 * @file
 * @brief max
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/math/max.hpp>

#if defined(max)
#undef max
#  pragma message("macro \"max\" undefined")
#endif

namespace BR {

template< typename T, typename TComparator >
BR_CONSTEXPR_AFTER_CXX11 auto max(T const & x, T const & y, TComparator && comparator) -> T const & {
	return comparator(x, y) ? y : x;
}

template< typename T >
BR_CONSTEXPR_AFTER_CXX11 auto max(T const & x, T const & y) -> T const & {
	return max(x, y, Less<>());
}

} // namespace BR
