/**
 * @file
 * @brief heap_build
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
 * @brief Creates a max heap out of a range of elements.
 * @tparam TRandomAccessIterator Type of \p first & \p last which satisfies \em RandomAccessIterator.
 * @tparam TComparator Type of \p comparator.
 * @param[in,out] first,last The range of elements to make the heap from.
 * @param[in] comparator comparison function object which returns <code>​true</code> if the first argument is less than the second.
 */
template< typename TRandomAccessIterator, typename TComparator >
void heap_build(
	TRandomAccessIterator first, TRandomAccessIterator last,
	TComparator && comparator
);

/**
 * @brief Creates a max heap out of a range of elements.
 * @tparam TRandomAccessIterator Type of \p first & \p last which satisfies \em RandomAccessIterator.
 * @param[in,out] first,last The range of elements to make the heap from.
 */
template< typename TRandomAccessIterator >
void heap_build(
	TRandomAccessIterator first, TRandomAccessIterator last
);

} // namespace Algorithm



inline namespace Algorithm {

template< typename TRandomAccessIterator, typename TComparator >
inline void heap_build(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) {
	auto length = last - first;
	if (length > 1) {
		for (auto start = (length - 2) / 2; start >= 0; --start) {
			Detail::Algorithm::heap_shift_down(first, last, length, first + start, forward<TComparator>(comparator));
		}
	}
}

template< typename TRandomAccessIterator >
inline void heap_build(TRandomAccessIterator first, TRandomAccessIterator last) {
	heap_build(first, last, Less<>());
}

} // namespace Algorithm

} // namespace BR