/**
 * @file
 * @brief uniquify
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/adjacent_find.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Removes consecutive duplicate elements in a range.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TBinaryPredicate Type of \p predicate.
 * @param[in,out] first,last The range of elements to process.
 * @param[in] predicate Binary predicate which returns <code>​true</code> if the elements should be treated as equal.
 * @return Forward iterator to the new end of the range.
 */
template< typename TForwardIterator, typename TBinaryPredicate >
auto uniquify(
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
auto uniquify(
	TForwardIterator first, TForwardIterator last
) -> TForwardIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TBinaryPredicate >
auto uniquify(TForwardIterator first, TForwardIterator last, TBinaryPredicate && predicate) -> TForwardIterator {
	first = adjacent_find(first, last, forward<TBinaryPredicate>(predicate));
	if (first != last) {
		auto iterator = first;
		for (++iterator; ++iterator != last;) {
			if (!forward<TBinaryPredicate>(predicate)(*first, *iterator))
				*++first = move(*iterator);
		}
		++first;
	}
	return first;
}

template< typename TForwardIterator >
inline auto uniquify(TForwardIterator first, TForwardIterator last) -> TForwardIterator {
	return uniquify(first, last, Equal<>());
}

} // namespace Algorithm

} // namespace BR
