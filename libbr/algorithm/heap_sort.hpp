/**
 * @file
 * @brief heap_sort
 * @author Bromine0x23
 * @since 2015/10/29
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/heap_pop.hpp>
#include <libbr/functional/less.hpp>

namespace BR {

template< typename TRandomAccessIterator, typename TComparator >
inline void heap_sort(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) {
	for (auto length = last - first; length > 1; --last, (void)--length) {
		heap_pop(first, last, length, comparator);
	}
}

template< typename TRandomAccessIterator >
inline void heap_sort(TRandomAccessIterator first, TRandomAccessIterator last) {
	heap_sort(first, last, Less<>());
}

} // namespace BR
