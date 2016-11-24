/**
 * @file
 * @brief heap_sort
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/heap_pop.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::sort_heap
 * @tparam TRandomAccessIterator
 * @tparam TComparator
 * @param[in,out] first,last
 * @param[in] comparator
 */
template< typename TRandomAccessIterator, typename TComparator >
void heap_sort(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator);

/**
 * @brief like std::sort_heap
 * @tparam TRandomAccessIterator
 * @param[in,out] first,last
 */
template< typename TRandomAccessIterator >
void heap_sort(TRandomAccessIterator first, TRandomAccessIterator last);

} // namespace Algorithm



inline namespace Algorithm {

template< typename TRandomAccessIterator, typename TComparator >
inline void heap_sort(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) {
	for (auto length = last - first; length > 1; --last, (void)--length) {
		heap_pop(first, last, length, forward<TComparator>(comparator));
	}
}

template< typename TRandomAccessIterator >
inline void heap_sort(TRandomAccessIterator first, TRandomAccessIterator last) {
	heap_sort(first, last, Less<>());
}

} // namespace Algorithm

} // namespace BR
