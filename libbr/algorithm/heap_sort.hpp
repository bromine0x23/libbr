/**
 * @file
 * @brief heap_sort
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
 * @brief Turns a max heap into a range of elements sorted in ascending order.
 * @tparam TRandomAccessIterator Type of \p first & \p last which satisfies \em RandomAccessIterator.
 * @tparam TComparator Type of \p comparator.
 * @param[in,out] first,last The range of elements to sort.
 * @param[in] comparator comparison function object which returns <code>​true</code> if the first argument is less than the second.
 */
template< typename TRandomAccessIterator, typename TComparator >
void heap_sort(
	TRandomAccessIterator first, TRandomAccessIterator last,
	TComparator && comparator
);

/**
 * @brief Turns a max heap into a range of elements sorted in ascending order.
 * @tparam TRandomAccessIterator Type of \p first & \p last which satisfies \em RandomAccessIterator.
 * @param[in,out] first,last The range of elements to sort.
 */
template< typename TRandomAccessIterator >
void heap_sort(
	TRandomAccessIterator first, TRandomAccessIterator last
);

} // namespace Algorithm



inline namespace Algorithm {

template< typename TRandomAccessIterator, typename TComparator >
inline void heap_sort(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) {
	for (auto length = last - first; length > 1; --last, (void)--length) {
		Detail::Algorithm::heap_pop(first, last, length, forward<TComparator>(comparator));
	}
}

template< typename TRandomAccessIterator >
inline void heap_sort(TRandomAccessIterator first, TRandomAccessIterator last) {
	heap_sort(first, last, Less<>());
}

} // namespace Algorithm

} // namespace BR
