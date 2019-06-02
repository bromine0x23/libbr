/**
 * @file
 * @brief min_element
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Returns the smallest element in the range \f$ [first, last) \f$.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TComparator Type of \p comparator.
 * @param first,last The range of elements to examine.
 * @param comparator Comparison function object which returns <code>​true</code>
 *                   if the first argument is less than (i.e. is ordered before) the second.
 * @return Iterator to the smallest element in the range \f$ [first, last) \f$.
 *         If several elements in the range are equivalent to the smallest element, returns the iterator to the first such element.
 *         Returns \p last if the range is empty.
 */
template< typename TForwardIterator, typename TComparator >
constexpr auto min_element(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> TForwardIterator;

/**
 * @brief Returns the smallest element in the range \f$ [first, last) \f$.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @param first,last The range of elements to examine.
 * @return Iterator to the smallest element in the range \f$ [first, last) \f$.
 *         If several elements in the range are equivalent to the smallest element, returns the iterator to the first such element.
 *         Returns \p last if the range is empty.
 */
template< typename TForwardIterator >
constexpr auto min_element(TForwardIterator first, TForwardIterator last) -> TForwardIterator;

} // namespace Algorithms



inline namespace Algorithms {

template< typename TForwardIterator, typename TComparator >
constexpr inline auto min_element(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> TForwardIterator {
	if (first != last) {
		for (auto i = first; ++i != last;) {
			if (forward<TComparator>(comparator)(*i, *first)) {
				first = i;
			}
		}
	}
	return first;
}

template< typename TForwardIterator >
constexpr inline auto min_element(TForwardIterator first, TForwardIterator last) -> TForwardIterator {
	return min_element(first, last, Less<>{});
}

} // namespace Algorithms

} // namespace BR
