/**
 * @file
 * @brief is_partitioned
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Determines if the range is partitioned by the given predicate.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TUnaryPredicate Type of \p predicate.
 * @param first,last The range of elements to examine.
 * @param predicate Unary predicate which returns ​<code>true</code> for the elements expected to be found in the beginning of the range.
 * @retval true The range \f$ [first, last) \f$ is empty or is partitioned by \p predicate.
 * @retval false Otherwise.
 */
template< typename TInputIterator, typename TUnaryPredicate >
auto is_partitioned(
	TInputIterator first, TInputIterator last,
	TUnaryPredicate && predicate
) -> Boolean;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TUnaryPredicate >
auto is_partitioned(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> Boolean {
	for (; first != last; ++first) {
		if (!forward<TUnaryPredicate>(predicate)(*first)) {
			break;
		}
	}
	for (; first != last; ++first) {
		if (forward<TUnaryPredicate>(predicate)(*first)) {
			return false;
		}
	}
	return true;
}

} // namespace Algorithm

} // namespace BR
