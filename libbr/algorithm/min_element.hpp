/**
 * @file
 * @brief min_element
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>

namespace BR {

template< typename TForwardIterator, typename TComparator >
BR_CONSTEXPR_AFTER_CXX11 inline auto min_element(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> TForwardIterator {
	if (first != last) {
		for (auto i = first; ++i != last;) {
			if (comparator(*i, *first)) {
				first = i;
			}
		}
	}
	return first;
}

template< typename TForwardIterator >
BR_CONSTEXPR_AFTER_CXX11 inline auto min_element(TForwardIterator first, TForwardIterator last) -> TForwardIterator {
	return min_element(first, last, Less<>());
}

} // namespace BR