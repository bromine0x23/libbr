/**
 * @file
 * @brief maxmin_element
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
 * @brief Returns the largest and the smallest elements in a range.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TComparator Type of \p comparator.
 * @param first,last The range of elements to examine.
 * @param comparator Comparison function object which returns <code>​true</code>
 *                   if the first argument is less than (i.e. is ordered before) the second.
 * @return A pair consisting of an iterator to the largest element as the first element and an iterator to the smallest element as the second.
 *         Returns <code>make_pair(first, first)</code> if the range is empty.
 *         If several elements are equivalent to the smallest element, the iterator to the first such element is returned.
 *         If several elements are equivalent to the largest element, the iterator to the last such element is returned.
 */
template< typename TForwardIterator, typename TComparator >
constexpr auto maxmin_element(
	TForwardIterator first, TForwardIterator last,
	TComparator && comparator
) -> Pair< TForwardIterator, TForwardIterator >;

/**
 * @brief Returns the largest and the smallest elements in a range.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @param first,last The range of elements to examine.
 * @return A pair consisting of an iterator to the largest element as the first element and an iterator to the smallest element as the second.
 *         Returns <code>make_pair(first, first)</code> if the range is empty.
 *         If several elements are equivalent to the smallest element, the iterator to the first such element is returned.
 *         If several elements are equivalent to the largest element, the iterator to the last such element is returned.
 */
template< typename TForwardIterator >
constexpr auto maxmin_element(
	TForwardIterator first, TForwardIterator last
) -> Pair< TForwardIterator, TForwardIterator >;

} // namespace Algorithms



inline namespace Algorithms {

template< typename TForwardIterator, typename TComparator >
constexpr auto maxmin_element(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> Pair< TForwardIterator, TForwardIterator > {
	auto result = make_pair(first, first);
	if (first != last) {
		if (++first != last) {
			if (forward<TComparator>(comparator)(*result.first, *first)) {
				result.first = first;
			} else {
				result.second = first;
			}
			for (; ++first != last;) {
				auto i = first;
				++first;
				if (first == last) {
					if (forward<TComparator>(comparator)(*result.first, *i)) {
						result.first = i;
					} else if (!forward<TComparator>(comparator)(*result.second, *i)) {
						result.second = i;
					}
					break;
				} else {
					if (forward<TComparator>(comparator)(*i, *first)) {
						if (forward<TComparator>(comparator)(*result.first, *first)) {
							result.first = first;
						}
						if (!forward<TComparator>(comparator)(*result.second, *i)) {
							result.second = i;
						}
					} else {
						if (forward<TComparator>(comparator)(*result.first, *i)) {
							result.first = i;
						}
						if (!forward<TComparator>(comparator)(*result.second, *first)) {
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
constexpr inline auto maxmin_element(TForwardIterator first, TForwardIterator last) -> Pair< TForwardIterator, TForwardIterator > {
	return maxmin_element(first, last, Less<>{});
}

} // namespace Algorithms

} // namespace BR
