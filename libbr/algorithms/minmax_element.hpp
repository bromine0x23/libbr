/**
 * @file
 * @brief minmax_element
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/containers/pair.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Returns the smallest and the largest elements in a range.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TComparator Type of \p comparator.
 * @param first,last The range of elements to examine.
 * @param comparator Comparison function object which returns <code>​true</code>
 * @return A pair consisting of an iterator to the smallest element as the first element and an iterator to the greatest element as the second.
 *         Returns <code>make_pair(first, first)</code> if the range is empty.
 *         If several elements are equivalent to the smallest element, the iterator to the first such element is returned.
 *         If several elements are equivalent to the largest element, the iterator to the last such element is returned.
 */
template< typename TForwardIterator, typename TComparator >
constexpr auto minmax_element(
	TForwardIterator first, TForwardIterator last,
	TComparator && comparator
) -> Pair< TForwardIterator, TForwardIterator >;

/**
 * @brief Returns the smallest and the largest elements in a range.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @param first,last The range of elements to examine.
 * @return A pair consisting of an iterator to the smallest element as the first element and an iterator to the greatest element as the second.
 *         Returns <code>make_pair(first, first)</code> if the range is empty.
 *         If several elements are equivalent to the smallest element, the iterator to the first such element is returned.
 *         If several elements are equivalent to the largest element, the iterator to the last such element is returned.
 */
template< typename TForwardIterator >
constexpr auto minmax_element(
	TForwardIterator first, TForwardIterator last
) -> Pair< TForwardIterator, TForwardIterator >;

} // namespace Algorithms



inline namespace Algorithms {

template< typename TForwardIterator, typename TComparator >
constexpr auto minmax_element(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> Pair< TForwardIterator, TForwardIterator > {
	auto result = make_pair(first, first);
	if (first != last) {
		if (++first != last) {
			if (forward<TComparator>(comparator)(*first, *result.first)) {
				result.first = first;
			} else {
				result.second = first;
			}
			for (; ++first != last;) {
				auto current = first;
				if (++first == last) {
					if (forward<TComparator>(comparator)(*current, *result.first)) {
						result.first = current;
					} else if (!forward<TComparator>(comparator)(*current, *result.second)) {
						result.second = current;
					}
					break;
				} else {
					if (forward<TComparator>(comparator)(*first, *current)) {
						if (forward<TComparator>(comparator)(*first, *result.first)) {
							result.first = first;
						}
						if (!forward<TComparator>(comparator)(*current, *result.second)) {
							result.second = current;
						}
					} else {
						if (forward<TComparator>(comparator)(*current, *result.first)) {
							result.first = current;
						}
						if (!forward<TComparator>(comparator)(*first, *result.second)) {
							result.second = first;
						}
					}
				}
			}
		}
	}
	return result;
}

template< typename TForwardIterator >
constexpr inline auto minmax_element(TForwardIterator first, TForwardIterator last) -> Pair< TForwardIterator, TForwardIterator > {
	return minmax_element(first, last, Less<>{});
}

} // namespace Algorithms

} // namespace BR
