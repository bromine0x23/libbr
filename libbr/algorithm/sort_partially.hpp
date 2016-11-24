/**
 * @file
 * @brief sort_partially
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/heap_build.hpp>
#include <libbr/algorithm/heap_pop.hpp>
#include <libbr/algorithm/heap_sort.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::partial_sort
 * @tparam TRandomAccessIterator
 * @tparam TComparator
 * @param[in,out] first,last
 * @param[in,out] middle
 * @param[in] comparator
 */
template< typename TRandomAccessIterator, typename TComparator >
void sort_partially(TRandomAccessIterator first, TRandomAccessIterator middle, TRandomAccessIterator last, TComparator && comparator);

/**
 * @brief like std::partial_sort
 * @tparam TRandomAccessIterator
 * @param[in,out] first,last
 * @param[in,out] middle
 */
template< typename TRandomAccessIterator >
void sort_partially(TRandomAccessIterator first, TRandomAccessIterator middle, TRandomAccessIterator last);

} // namespace Algorithm



inline namespace Algorithm {

template< typename TRandomAccessIterator, typename TComparator >
void sort_partially(TRandomAccessIterator first, TRandomAccessIterator middle, TRandomAccessIterator last, TComparator && comparator) {
	heap_build(first, middle, forward<TComparator>(comparator));
	auto length = middle - first;
	for (auto i = middle; i != last; ++i) {
		if (forward<TComparator>(comparator)(*i, *first)) {
			swap(*i, *first);
			Detail::Algorithm::heap_shift_down(first, middle, length, first, forward<TComparator>(comparator));
		}
	}
	heap_sort(first, middle, forward<TComparator>(comparator));
}

template< typename TRandomAccessIterator >
inline void sort_partially(TRandomAccessIterator first, TRandomAccessIterator middle, TRandomAccessIterator last) {
	sort_partially(first, middle, last, Less<>());
}

} // namespace Algorithm

} // namespace BR