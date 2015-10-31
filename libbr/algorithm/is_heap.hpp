/**
 * @file
 * @brief is_heap
 * @author Bromine0x23
 * @since 2015/10/29
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/is_sorted_until.hpp>
#include <libbr/functional/less.hpp>

namespace BR {

template< typename TRandomAccessIterator, typename TComparator >
inline auto is_heap(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) -> bool {
	return is_heap_until(first, last, comparator) == last;
}

template< typename TRandomAccessIterator >
inline auto is_heap(TRandomAccessIterator first, TRandomAccessIterator last) -> bool {
	return is_heap(first, last, Less<>());
}

} // namespace BR
