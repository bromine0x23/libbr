/**
 * @file
 * @brief adjacent_find
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Finds the first two adjacent items that satisfy a given predicate.
 * @tparam TForwardIterator ForwardIterator type of \p first & \p last.
 * @tparam TBinaryPredicate Type of \p predicate.
 * @param first,last The range of elements to examine.
 * @param predicate Binary predicate which returns <code>​true</code> if the elements should be treated as equal.
 * @return
 */
template< typename TForwardIterator, typename TBinaryPredicate >
auto adjacent_find(TForwardIterator first, TForwardIterator last, TBinaryPredicate && predicate) -> TForwardIterator;

/**
 * @brief Finds the first two adjacent items that are equal.
 * @tparam TForwardIterator ForwardIterator type of \p first & \p last.
 * @param first,last The range of elements to examine.
 * @return
 */
template< typename TForwardIterator >
auto adjacent_find(TForwardIterator first, TForwardIterator last) -> TForwardIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TBinaryPredicate >
auto adjacent_find(TForwardIterator first, TForwardIterator last, TBinaryPredicate && predicate) -> TForwardIterator {
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
inline auto adjacent_find(TForwardIterator first, TForwardIterator last) -> TForwardIterator {
	return adjacent_find(first, last, Equal<>());
}

} // namespace Algorithm

} // namespace BR
