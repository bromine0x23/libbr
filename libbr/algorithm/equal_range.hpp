/**
 * @file
 * @brief equal_range
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/lower_bound.hpp>
#include <libbr/algorithm/upper_bound.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/iterator/next.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Returns range of elements matching a specific key.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TValue Type of \p value.
 * @tparam TComparator Type of \p comparator
 * @param first,last The range of elements to examine.
 * @param value Value to compare the elements to.
 * @param comparator Comparison function which returns <code>​true</code> if the first argument is less than the second.
 * @return Pair containing a pair of iterators defining the wanted range,
 *         the first pointing to the first element that is not less than value and
 *         the second pointing to the first element greater than value.
 */
template< typename TForwardIterator, typename TValue, typename TComparator >
auto equal_range(TForwardIterator first, TForwardIterator last, TValue const & value, TComparator && comparator) -> Pair< TForwardIterator, TForwardIterator >;

/**
 * @brief Returns range of elements matching a specific key.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TValue Type of \p value.
 * @param first,last The range of elements to examine.
 * @param value Value to compare the elements to.
 * @return Pair containing a pair of iterators defining the wanted range,
 *         the first pointing to the first element that is not less than value and
 *         the second pointing to the first element greater than value.
 */
template< typename TForwardIterator, typename TValue >
auto equal_range(TForwardIterator first, TForwardIterator last, TValue const & value) -> Pair< TForwardIterator, TForwardIterator >;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TValue, typename TComparator >
auto equal_range(TForwardIterator first, TForwardIterator last, TValue const & value, TComparator && comparator) -> Pair< TForwardIterator, TForwardIterator > {
	for (auto length = distance(first, last); length != 0; ) {
		auto half_length = length / 2;
		auto middle = next(first, half_length);
		if (forward<TComparator>(comparator)(*middle, value)) {
			first = ++middle;
			length -= half_length + 1;
		} else if (forward<TComparator>(comparator)(value, *middle)) {
			last = middle;
			length = half_length;
		} else {
			return {
				lower_bound(first, middle, value, forward<TComparator>(comparator)),
				upper_bound(next(middle), last, value, forward<TComparator>(comparator))
			};
		}
	}
	return {first, first};
}

template< typename TForwardIterator, typename TValue >
inline auto equal_range(TForwardIterator first, TForwardIterator last, TValue const & value) -> Pair< TForwardIterator, TForwardIterator > {
	return equal_range(first, last, value, Less<>());
}

} // namespace Algorithm

} // namespace BR
