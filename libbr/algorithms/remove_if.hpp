/**
 * @file
 * @brief remove_if
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithms/find_if.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/transfer.hpp>

namespace BR {

inline namespace Algorithms {

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

} // namespace Algorithms



inline namespace Algorithms {

template< typename TForwardIterator, typename TUnaryPredicate >
auto remove_if(TForwardIterator first, TForwardIterator last, TUnaryPredicate && predicate) -> TForwardIterator {
	first = find_if(first, last, predicate);
	if (first != last) {
		for (auto iterator = first; ++iterator != last; ) {
			if (!forward<TUnaryPredicate>(predicate)(*iterator)) {
				*first = transfer(*iterator);
				++first;
			}
		}
	}
	return first;
}

} // namespace Algorithms

} // namespace BR
