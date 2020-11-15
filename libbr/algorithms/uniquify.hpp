/**
 * @file
 * @brief uniquify
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithms/find_adjacent.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/transfer.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Removes consecutive duplicate elements in a range.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TBinaryPredicate Type of \p predicate.
 * @param[in,out] first,last The range of elements to process.
 * @param[in] predicate Binary predicate which returns <code>​true</code> if the elements should be treated as equal.
 * @return Forward iterator to the new end of the range.
 */
template< typename TForwardIterator, typename TBinaryPredicate >
constexpr auto uniquify(
	TForwardIterator first, TForwardIterator last,
	TBinaryPredicate && predicate
) -> TForwardIterator;

/**
 * @brief Removes consecutive duplicate elements in a range.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @param[in,out] first,last The range of elements to process.
 * @return Forward iterator to the new end of the range.
 */
template< typename TForwardIterator, typename TBinaryPredicate >
constexpr auto uniquify(
	TForwardIterator first, TForwardIterator last
) -> TForwardIterator;

} // namespace Algorithms



inline namespace Algorithms {

template< typename TForwardIterator, typename TBinaryPredicate >
constexpr auto uniquify(TForwardIterator first, TForwardIterator last, TBinaryPredicate && predicate) -> TForwardIterator {
	first = find_adjacent(first, last, forward<TBinaryPredicate>(predicate));
	if (first != last) {
		auto iterator = first;
		for (++iterator; ++iterator != last;) {
			if (!forward<TBinaryPredicate>(predicate)(*first, *iterator))
				*++first = transfer(*iterator);
		}
		++first;
	}
	return first;
}

template< typename TForwardIterator >
constexpr inline auto uniquify(TForwardIterator first, TForwardIterator last) -> TForwardIterator {
	return uniquify(first, last, Equal<>{});
}

} // namespace Algorithms

} // namespace BR
