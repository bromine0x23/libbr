/**
 * @file
 * @brief all_of
 * @author Bromine0x23
 * @since 2015/10/24
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename TInputIterator, typename TUnaryPredicate >
inline auto all_of(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> bool {
	for (; first != last; ++first) {
		if (!predicate(*first)) {
			return false;
		}
	}
	return true;
}

} // namespace BR
