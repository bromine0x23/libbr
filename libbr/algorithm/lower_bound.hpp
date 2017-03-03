/**
 * @file
 * @brief lower_bound
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/iterator/next.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Returns an iterator to the first element not less than the given value.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TValue Type of \p value.
 * @tparam TComparator Type of \p comparator
 * @param first,last The range of elements to examine.
 * @param value Value to compare the elements to.
 * @param comparator Comparison function object which returns <code>​true</code>
 *                   if the first argument is less than (i.e. is ordered before) the second.
 * @return Iterator pointing to the first element that is not less than \p value, or \p last if no such element is found.
 */
template< typename TForwardIterator, typename TValue, typename TComparator >
auto lower_bound(
	TForwardIterator first, TForwardIterator last,
	TValue const & value,
	TComparator && comparator
) -> TForwardIterator;

/**
 * @brief Returns an iterator to the first element not less than the given value.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TValue Type of \p value.
 * @param first,last The range of elements to examine.
 * @param value Value to compare the elements to.
 * @return Iterator pointing to the first element that is not less than \p value, or \p last if no such element is found.
 */
template< typename TForwardIterator, typename TValue >
auto lower_bound(
	TForwardIterator first, TForwardIterator last,
	TValue const & value
) -> TForwardIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TValue, typename TComparator >
auto lower_bound(TForwardIterator first, TForwardIterator last, TValue const & value, TComparator && comparator) -> TForwardIterator {
	for (auto length = distance(first, last); length > 0; ) {
		auto const half_length = length / 2;
		auto middle = next(first, half_length);
		if (forward<TComparator>(comparator)(*middle, value)) {
			first = ++middle;
			length -= half_length + 1;
		} else {
			length = half_length;
		}
	}
	return first;
}

template< typename TForwardIterator, typename TValue >
inline auto lower_bound(TForwardIterator first, TForwardIterator last, TValue const & value) -> TForwardIterator {
	return lower_bound(first, last, value, Less<>());
}

} // namespace Algorithm

} // namespace BR
