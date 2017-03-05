/**
 * @file
 * @brief min_max_element
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

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
auto min_max_element(
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
auto min_max_element(
	TForwardIterator first, TForwardIterator last
) -> Pair< TForwardIterator, TForwardIterator >;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TComparator >
auto min_max_element(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> Pair< TForwardIterator, TForwardIterator > {
	auto result = make_pair(first, first);
	if (first != last) {
		if (++first != last) {
			if (forward<TComparator>(comparator)(*first, *result.first)) {
				result.first = first;
			} else {
				result.second = first;
			}
			for (; ++first != last;) {
				auto i = first;
				if (++first == last) {
					if (forward<TComparator>(comparator)(*i, *result.first)) {
						result.first = i;
					} else if (!forward<TComparator>(comparator)(*i, *result.second)) {
						result.second = i;
					}
					break;
				} else {
					if (forward<TComparator>(comparator)(*first, *i)) {
						if (forward<TComparator>(comparator)(*first, *result.first)) {
							result.first = first;
						}
						if (!forward<TComparator>(comparator)(*i, *result.second)) {
							result.second = i;
						}
					} else {
						if (forward<TComparator>(comparator)(*i, *result.first)) {
							result.first = i;
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
inline auto min_max_element(TForwardIterator first, TForwardIterator last) -> Pair< TForwardIterator, TForwardIterator > {
	return min_max_element(first, last, Less<>());
}

} // namespace Algorithm

} // namespace BR
