/**
 * @file
 * @brief find_adjacent
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Finds the first two adjacent items that satisfy a given predicate.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TBinaryPredicate Type of \p predicate.
 * @param first,last The range of elements to examine.
 * @param predicate Binary predicate which returns <code>​true</code> if the elements should be treated as equal.
 * @return
 */
template< typename TForwardIterator, typename TBinaryPredicate >
auto find_adjacent(
	TForwardIterator first, TForwardIterator last,
	TBinaryPredicate && predicate
) -> TForwardIterator;

/**
 * @brief Finds the first two adjacent items that are equal.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies ForwardIterator.
 * @param first,last The range of elements to examine.
 * @return
 */
template< typename TForwardIterator >
auto find_adjacent(
	TForwardIterator first, TForwardIterator last
) -> TForwardIterator;

} // namespace Algorithms



inline namespace Algorithms {

template< typename TForwardIterator, typename TBinaryPredicate >
auto find_adjacent(TForwardIterator first, TForwardIterator last, TBinaryPredicate && predicate) -> TForwardIterator {
	if (first != last) {
		for (auto i = first; ++i != last; first = i) {
			if (forward<TBinaryPredicate>(predicate)(*first, *i)) {
				return first;
			}
		}
	}
	return last;
}

template< typename TForwardIterator >
inline auto find_adjacent(TForwardIterator first, TForwardIterator last) -> TForwardIterator {
	return find_adjacent(first, last, Equal<>{});
}

} // namespace Algorithms

} // namespace BR
