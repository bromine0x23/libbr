/**
 * @file
 * @brief max_element
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>

namespace BR {

template< typename TForwardIterator, typename TComparator >
BR_CONSTEXPR_AFTER_CXX11 inline auto max_element(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> TForwardIterator {
	if (first != last) {
		for (auto i = first; ++i != last;) {
			if (comparator(*first, *i)) {
				first = i;
			}
		}
	}
	return first;
}

template< typename TForwardIterator >
BR_CONSTEXPR_AFTER_CXX11 inline auto max_element(TForwardIterator first, TForwardIterator last) -> TForwardIterator {
	return max_element(first, last, Less<>());
}

} // namespace BR
