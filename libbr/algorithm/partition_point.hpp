/**
 * @file
 * @brief partition_point
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/advance.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Locates the partition point of a partitioned range.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TUnaryPredicate Type of \p predicate.
 * @param first,last The partitioned range of elements to examine.
 * @param predicate Unary predicate which returns <code>​true</code> for the elements found in the beginning of the range.
 * @return The iterator past the end of the first partition within \f$ [first, last) \f$ or last if all elements satisfy \p predicate.
 */
template< typename TForwardIterator, typename TUnaryPredicate >
auto partition_point(
	TForwardIterator first, TForwardIterator last,
	TUnaryPredicate && predicate
) -> TForwardIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TUnaryPredicate >
auto partition_point(TForwardIterator first, TForwardIterator last, TUnaryPredicate && predicate) -> TForwardIterator {
	for (auto length = distance(first, last); length != 0;) {
		auto half_length = length / 2;
		auto middle = first;
		advance(middle, half_length);
		if (forward<TUnaryPredicate>(predicate)(*middle)) {
			first = ++middle;
			length -= half_length + 1;
		} else {
			length = half_length;
		}
	}
	return first;
}

} // namespace Algorithm

} // namespace BR
