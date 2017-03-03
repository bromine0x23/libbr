/**
 * @file
 * @brief sort_partially
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
 * @brief Sorts the first N (\f$ middle - first \f$) elements of a range.
 * @tparam TRandomAccessIterator Type of \p first , \p middle & \p last which satisfies \em RandomAccessIterator.
 * @tparam TComparator Type of \p comparator.
 * @param[in,out] first,last The range of elements to sort.
 * @param[in,out] middle Indicate the number of elements to sort with \p first, and get the end of the range to place sorted elements.
 * @param[in] comparator Comparison function object which returns <code>​true</code>
 *                       if the first argument is less than (i.e. is ordered before) the second.
 */
template< typename TRandomAccessIterator, typename TComparator >
void sort_partially(
	TRandomAccessIterator first, TRandomAccessIterator middle, TRandomAccessIterator last,
	TComparator && comparator
);

/**
 * @brief Sorts the first N elements of a range.
 * @tparam TRandomAccessIterator Type of \p first , \p middle & \p last which satisfies \em RandomAccessIterator.
 * @param[in,out] first,last The range of elements to sort.
 * @param[in,out] middle Indicate the number of elements to sort with \p first, and get the end of the range to place sorted elements.
 */
template< typename TRandomAccessIterator >
void sort_partially(
	TRandomAccessIterator first, TRandomAccessIterator middle, TRandomAccessIterator last
);

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