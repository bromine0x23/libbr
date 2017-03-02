/**
 * @file
 * @brief heap_push
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Adds an element to a max heap.
 * @tparam TRandomAccessIterator Type of \p first & \p last which satisfies \em RandomAccessIterator.
 * @tparam TComparator Type of \p comparator.
 * @param[in,out] first,last The range of elements defining the heap to modify.
 * @param[in] comparator comparison function object which returns <code>​true</code> if the first argument is less than the second.
 */
template< typename TRandomAccessIterator, typename TComparator >
void heap_push(
	TRandomAccessIterator first, TRandomAccessIterator last,
	TComparator && comparator
);

/**
 * @brief Adds an element to a max heap.
 * @tparam TRandomAccessIterator Type of \p first & \p last which satisfies \em RandomAccessIterator.
 * @param[in,out] first,last The range of elements defining the heap to modify.
 */
template< typename TRandomAccessIterator >
void heap_push(
	TRandomAccessIterator first, TRandomAccessIterator last
);

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

template< typename TRandomAccessIterator, typename TDifference, typename TComparator >
void heap_shift_up(TRandomAccessIterator first, TRandomAccessIterator last, TDifference length, TComparator && comparator) {
	if (length > 1) {
		length = (length - 2) / 2;
		auto p = first + length;
		if (forward<TComparator>(comparator)(*p, *--last)) {
			auto t = move(*last);
			do {
				*last = move(*p);
				last = p;
				if (length == 0) {
					break;
				}
				length = (length - 1) / 2;
				p = first + length;
			} while (forward<TComparator>(comparator)(*p, t));
			*last = move(t);
		}
	}
}

} // namespace Algorithm
} // namespace Detail

inline namespace Algorithm {

template< typename TRandomAccessIterator, typename TComparator >
inline void heap_push(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) {
	Detail::Algorithm::heap_shift_up(first, last, last - first, forward<TComparator>(comparator));
}

template< typename TRandomAccessIterator >
inline void heap_push(TRandomAccessIterator first, TRandomAccessIterator last) {
	heap_push(first, last, Less<>());
}

} // namespace Algorithm

} // namespace BR
