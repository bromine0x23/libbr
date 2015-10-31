/**
 * @file
 * @brief sort_partially
 * @author Bromine0x23
 * @since 2015/10/29
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/heap_build.hpp>
#include <libbr/algorithm/heap_sort.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

template< typename TRandomAccessIterator, typename TComparator >
void sort_partially(TRandomAccessIterator first, TRandomAccessIterator middle, TRandomAccessIterator last, TComparator && comparator) {
	heap_build(first, middle, comparator);
	auto length = middle - first;
	for (auto i = middle; i != last; ++i) {
		if (comparator(*i, *first)) {
			swap(*i, *first);
			Detail::Algorithm::heap_shift_down(first, middle, length, first, comparator);
		}
	}
	heap_sort(first, middle, comparator);
}

template< typename TRandomAccessIterator >
inline void sort_partially(TRandomAccessIterator first, TRandomAccessIterator middle, TRandomAccessIterator last) {
	sort_partially(first, middle, last, Less<>());
}

} // namespace BR