/**
 * @file
 * @brief is_sorted_until
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>

namespace BR {

template< typename TForwardIterator, typename TComparator >
auto is_sorted_until(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> TForwardIterator {
	if (first != last) {
		for (auto after_first = first; ++after_first != last; first = after_first) {
			if (comparator(*after_first, *first)) {
				return after_first;
			}
		}
	}
	return last;
}

template< typename TForwardIterator >
inline auto is_sorted_until(TForwardIterator first, TForwardIterator last) -> TForwardIterator {
	return is_sorted_until(first, last, Less<>());
}

} // namespace BR
