/**
 * @file
 * @brief remove_if
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/find_if.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

template< typename TForwardIterator, typename TUnaryPredicate >
auto remove_if(TForwardIterator first, TForwardIterator last, TUnaryPredicate && predicate) -> TForwardIterator {
	first = find_if(first, last, predicate);
	if (first != last) {
		for (auto iterator = first; ++iterator != last; ) {
			if (!predicate(*iterator)) {
				*first = move(*iterator);
				++first;
			}
		}
	}
	return first;
}

} // namespace BR
