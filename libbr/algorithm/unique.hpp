/**
 * @file
 * @brief unique
 * @author Bromine0x23
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
 * @brief like std::unique
 * @tparam TForwardIterator
 * @tparam TBinaryPredicate
 * @param[in,out] first,last
 * @param[in] predicate
 * @return
 */
template< typename TForwardIterator, typename TBinaryPredicate >
auto unique(TForwardIterator first, TForwardIterator last, TBinaryPredicate && predicate) -> TForwardIterator;

/**
 * @brief like std::unique
 * @tparam TForwardIterator
 * @tparam TBinaryPredicate
 * @param[in,out] first,last
 * @return
 */
template< typename TForwardIterator, typename TBinaryPredicate >
auto unique(TForwardIterator first, TForwardIterator last) -> TForwardIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TBinaryPredicate >
auto unique(TForwardIterator first, TForwardIterator last, TBinaryPredicate && predicate) -> TForwardIterator {
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

template< typename TForwardIterator, typename TBinaryPredicate >
inline auto unique(TForwardIterator first, TForwardIterator last) -> TForwardIterator {
	return unique(first, last, Equal<>());
}

} // namespace Algorithm

} // namespace BR
