/**
 * @file
 * @brief max_element
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Returns the largest element in the range \f$ [first, last) \f$.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TComparator Type of \p comparator.
 * @param first,last The range of elements to examine.
 * @param comparator Comparison function object which returns <code>​true</code>
 *                   if the first argument is less than (i.e. is ordered before) the second.
 * @return Iterator to the largest element in the range \f$ [first, last) \f$.
 *         If several elements in the range are equivalent to the largest element, returns the iterator to the first such element.
 *         Returns \p last if the range is empty.
 */
template< typename TForwardIterator, typename TComparator >
BR_CONSTEXPR_AFTER_CXX11 auto max_element(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> TForwardIterator;

/**
 * @brief Returns the largest element in the range \f$ [first, last) \f$.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @param first,last The range of elements to examine.
 * @return Iterator to the largest element in the range \f$ [first, last) \f$.
 *         If several elements in the range are equivalent to the largest element, returns the iterator to the first such element.
 *         Returns \p last if the range is empty.
 */
template< typename TForwardIterator >
BR_CONSTEXPR_AFTER_CXX11 auto max_element(TForwardIterator first, TForwardIterator last) -> TForwardIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TComparator >
BR_CONSTEXPR_AFTER_CXX11 inline auto max_element(TForwardIterator first, TForwardIterator last, TComparator && comparator) -> TForwardIterator {
	if (first != last) {
		for (auto i = first; ++i != last;) {
			if (forward<TComparator>(comparator)(*first, *i)) {
				first = i;
			}
		}
	}
	return first;
}

template< typename TForwardIterator >
BR_CONSTEXPR_AFTER_CXX11 inline auto max_element(TForwardIterator first, TForwardIterator last) -> TForwardIterator {
	return max_element(first, last, Less<>());
}

} // namespace Algorithm

} // namespace BR
