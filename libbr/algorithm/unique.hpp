/**
 * @file
 * @brief unique
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/adjacent_find.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

template< typename TForwardIterator, typename TBinaryPredicate >
auto unique(TForwardIterator first, TForwardIterator last, TBinaryPredicate && predicate) -> TForwardIterator {
	first = adjacent_find(first, last, predicate);
	if (first != last) {
		auto iterator = first;
		for (++iterator; ++iterator != last;) {
			if (!predicate(*first, *iterator))
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

} // namespace BR
