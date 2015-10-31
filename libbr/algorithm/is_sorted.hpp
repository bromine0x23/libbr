/**
 * @file
 * @brief is_sorted
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/is_sorted_until.hpp>
#include <libbr/functional/less.hpp>

namespace BR {

template< typename TForwardIterator, typename TComparator >
inline auto is_sorted(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> bool {
	return is_sorted_until(first, last, comparator) == last;
}

template< typename TForwardIterator >
inline auto is_sorted(TForwardIterator first, TForwardIterator last) -> bool {
	return is_sorted(first, last, Less<>());
}

} // namespace BR
