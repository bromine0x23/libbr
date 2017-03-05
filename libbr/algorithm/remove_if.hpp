/**
 * @file
 * @brief remove_if
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/find_if.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Removes elements satisfying specific criteria.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TUnaryPredicate Type of \p predicate.
 * @param[in,out] first,last The range of elements to process.
 * @param[in] predicate Unary predicate which returns <code>​true</code> if the element should be removed.
 * @return Iterator to the end of new range.
 */
template< typename TForwardIterator, typename TUnaryPredicate >
auto remove_if(
	TForwardIterator first, TForwardIterator last,
	TUnaryPredicate && predicate
) -> TForwardIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TUnaryPredicate >
auto remove_if(TForwardIterator first, TForwardIterator last, TUnaryPredicate && predicate) -> TForwardIterator {
	first = find_if(first, last, predicate);
	if (first != last) {
		for (auto iterator = first; ++iterator != last; ) {
			if (!forward<TUnaryPredicate>(predicate)(*iterator)) {
				*first = move(*iterator);
				++first;
			}
		}
	}
	return first;
}

} // namespace Algorithm

} // namespace BR
