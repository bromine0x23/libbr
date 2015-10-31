/**
 * @file
 * @brief adjacent_find
 * @author Bromine0x23
 * @since 2015/10/24
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/equal.hpp>

namespace BR {

template< typename TForwardIterator, typename TBinaryPredicate >
auto adjacent_find(TForwardIterator first, TForwardIterator last, TBinaryPredicate && predicate) -> TForwardIterator {
	if (first != last) {
		for (auto i = first; ++i != last; first = i) {
			if (predicate(*first, *i)) {
				return first;
			}
		}
	}
	return last;
}

template< typename TForwardIterator, typename TBinaryPredicate >
inline auto adjacent_find(TForwardIterator first, TForwardIterator last) -> TForwardIterator {
	return adjacent_find(first, last, Equal<void>());
}

} // namespace BR
