/**
 * @file
 * @brief is_heap_until
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Finds the largest subrange that is a max heap
 * @tparam TRandomAccessIterator Type of \p first & \p last which satisfies \em RandomAccessIterator.
 * @tparam TComparator Type of \p comparator.
 * @param first,last The range of elements to examine.
 * @param comparator Comparison function object which returns <code>​true</code>
 *                   if the first argument is less than (i.e. is ordered before) the second.
 * @return The upper bound of the largest range beginning at first which is a max heap.
 */
template< typename TRandomAccessIterator, typename TComparator >
auto is_heap_until(
	TRandomAccessIterator first, TRandomAccessIterator last,
	TComparator && comparator
) -> TRandomAccessIterator;

/**
 * @brief Finds the largest subrange that is a max heap
 * @tparam TComparator Type of \p comparator.
 * @param first,last The range of elements to examine.
 * @return The upper bound of the largest range beginning at first which is a max heap.
 */
template< typename TRandomAccessIterator >
auto is_heap_until(
	TRandomAccessIterator first, TRandomAccessIterator last
) -> TRandomAccessIterator;

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

template< typename TRandomAccessIterator, typename TComparator >
auto is_heap_until(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) -> TRandomAccessIterator {
	using Difference = typename IteratorTraits<TRandomAccessIterator>::Difference;
	Difference length = last - first;
	Difference p = 0;
	Difference c = 1;
	auto pp = first;
	for (; c < length;) {
		auto cp = first + c;
		if (forward<TComparator>(comparator)(*pp, *cp)) {
			return cp;
		}
		++c;
		++cp;
		if (c == length) {
			return last;
		}
		if (forward<TComparator>(comparator)(*pp, *cp)) {
			return cp;
		}
		++p;
		++pp;
		c = 2 * p + 1;
	}
	return last;
}

} // namespace Algorithm
} // namespace Detail

inline namespace Algorithm {

template< typename TRandomAccessIterator, typename TComparator >
inline auto is_heap_until(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) -> TRandomAccessIterator {
	return Detail::Algorithm::is_heap_until(first, last, forward<TComparator>(comparator));
}

template< typename TRandomAccessIterator >
inline auto is_heap_until(TRandomAccessIterator first, TRandomAccessIterator last) -> TRandomAccessIterator {
	return is_heap_until(first, last, Less<>());
}

} // namespace Algorithm

} // namespace BR
