/**
 * @file
 * @brief binary_search
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/lower_bound.hpp>
#include <libbr/functional/less.hpp>

namespace BR {

template< typename TForwardIterator, typename TValue, typename TComparator >
inline auto binary_search(TForwardIterator first, TForwardIterator last, TValue const & value, TComparator && comparator) -> bool {
	first = lower_bound(first, last, value, comparator);
	return first != last && !comparator(value, *first);
}

template< typename TForwardIterator, typename TValue >
inline auto binary_search(TForwardIterator first, TForwardIterator last, TValue const & value) -> bool {
	return binary_search(first, last, Less<void>());
}

} // namespace BR
