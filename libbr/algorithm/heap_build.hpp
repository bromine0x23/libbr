/**
 * @file
 * @brief heap_build
 * @author Bromine0x23
 * @since 2015/10/29
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/heap_pop.hpp>
#include <libbr/functional/less.hpp>

namespace BR {

template< typename TRandomAccessIterator, typename TComparator >
inline void heap_build(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) {
	auto length = last - first;
	if (length > 1) {
		for (auto start = (length - 2) / 2; start >= 0; --start) {
			heap_shift_down(first, last, length, first + start, comparator);
		}
	}
}

template< typename TRandomAccessIterator >
inline void heap_build(TRandomAccessIterator first, TRandomAccessIterator last) {
	heap_build(first, last, Less<>());
}

} // namespace BR