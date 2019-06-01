/**
 * @file
 * @brief sorted_until
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Finds the largest sorted subrange.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TComparator Type of \p comparator.
 * @param first,last The range of elements to examine.
 * @param comparator Comparison function object which returns <code>​true</code>
 *                   if the first argument is less than (i.e. is ordered before) the second.
 * @return The upper bound of the largest range beginning at first in which the elements are sorted in ascending order.
 */
template< typename TForwardIterator, typename TComparator >
constexpr auto sorted_until(
	TForwardIterator first, TForwardIterator last,
	TComparator && comparator
) -> TForwardIterator;

/**
 * @brief Finds the largest sorted subrange.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @param first,last The range of elements to examine.
 * @return The upper bound of the largest range beginning at first in which the elements are sorted in ascending order.
 */
template< typename TForwardIterator >
constexpr auto sorted_until(
	TForwardIterator first, TForwardIterator last
) -> TForwardIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TComparator >
constexpr auto sorted_until(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> TForwardIterator {
	if (first != last) {
		for (auto after_first = first; ++after_first != last; first = after_first) {
			if (forward<TComparator>(comparator)(*after_first, *first)) {
				return after_first;
			}
		}
	}
	return last;
}

template< typename TForwardIterator >
constexpr inline auto sorted_until(TForwardIterator first, TForwardIterator last) -> TForwardIterator {
	return sorted_until(first, last, Less<>{});
}

} // namespace Algorithm

} // namespace BR
