/**
 * @file
 * @brief any_of
 * @author Bromine0x23
 * @since 2015/10/24
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename TInputIterator, typename TUnaryPredicate >
inline auto any_of(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> bool {
	for (; first != last; ++first) {
		if (predicate(*first)) {
			return true;
		}
	}
	return false;
}

} // namespace BR
