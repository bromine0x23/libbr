/**
 * @file
 * @brief is_heap
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/is_heap_until.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Checks if the given range is a max heap.
 * @tparam TRandomAccessIterator Type of \p first & \p last which satisfies \em RandomAccessIterator.
 * @tparam TComparator Type of \p comparator.
 * @param first,last The range of elements to examine.
 * @param comparator comparison function object which returns <code>​true</code> if the first argument is less than the second.
 * @retval true The range is max heap.
 * @retval false Otherwise.
 */
template< typename TRandomAccessIterator, typename TComparator >
auto is_heap(
	TRandomAccessIterator first, TRandomAccessIterator last,
	TComparator && comparator
) -> Boolean;

/**
 * @brief Checks if the given range is a max heap.
 * @tparam TRandomAccessIterator Type of \p first & \p last which satisfies \em RandomAccessIterator.
 * @param first,last The range of elements to examine.
 * @retval true The range is max heap.
 * @retval false Otherwise.
 */
template< typename TRandomAccessIterator >
auto is_heap(
	TRandomAccessIterator first, TRandomAccessIterator last
) -> Boolean;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TRandomAccessIterator, typename TComparator >
inline auto is_heap(TRandomAccessIterator first, TRandomAccessIterator last, TComparator && comparator) -> Boolean {
	return is_heap_until(first, last, forward<TComparator>(comparator)) == last;
}

template< typename TRandomAccessIterator >
inline auto is_heap(TRandomAccessIterator first, TRandomAccessIterator last) -> Boolean {
	return is_heap(first, last, Less<>());
}

} // namespace Algorithm

} // namespace BR
